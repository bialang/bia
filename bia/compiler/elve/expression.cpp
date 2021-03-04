#include "../jumper.hpp"
#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/integer.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;

namespace bia {
namespace compiler {
namespace elve {

inline bool is_test_operator(Operator optor) noexcept
{
	switch (optor) {
	case Operator::equal:
	case Operator::not_equal:
	case Operator::less:
	case Operator::less_equal:
	case Operator::greater:
	case Operator::greater_equal:
	case Operator::in: return true;
	default: return false;
	}
}

inline bool has_right_hand_size(const Tokens& tokens) noexcept
{
	return tokens.size() > 1 && tokens[0].value.is_type<Operator>() &&
	       tokens[0].value != Operator::function_call_close;
}

std::pair<Tokens, symbol::Variable> single_expression_impl(Parameter& param, Tokens tokens, Jumper& jumper,
                                                           int precedence);

inline std::pair<Tokens, symbol::Variable> number_value(Parameter& param, Tokens tokens)
{
	using Type = Token::Number::Type;

	// get number type
	const auto& number = tokens.front().value.get<Token::Number>();

	symbol::Symbol right_type;
	switch (number.type) {
	case Type::i: right_type = param.symbols.symbol(util::from_cstring("int")); break;
	case Type::i32: right_type = param.symbols.symbol(util::from_cstring("int32")); break;
	case Type::f32: right_type = param.symbols.symbol(util::from_cstring("float32")); break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
	BIA_ASSERT(right_type.is_type<type::Definition*>());

	auto variable = param.symbols.create_temporary(right_type.get<type::Definition*>());
	switch (number.type) {
	case Type::i: {
		// TODO check size with default int size
		param.instructor.write<bytecode::Op_code::load>(variable.location.offset, number.value.i64);
		break;
	}
	case Type::i32:
	case Type::u32:
	case Type::f32:
		param.instructor.write<bytecode::Op_code::load>(variable.location.offset, number.value.i32);
		break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}

	return { tokens.subspan(1), variable };
}

inline std::pair<Tokens, symbol::Variable> value(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty());
	if (tokens.front().value.is_type<Token::Keyword>()) {
		const auto right = param.symbols.symbol(util::from_cstring("bool"));
		BIA_ASSERT(right.is_type<type::Definition*>());

		auto variable = param.symbols.create_temporary(right.get<type::Definition*>());
		switch (tokens.front().value.get<Token::Keyword>()) {
		case Token::Keyword::true_:
			param.instructor.write<bytecode::Op_code::load>(variable.location.offset, std::int8_t{ 1 });
			break;
		case Token::Keyword::false_:
			param.instructor.write<bytecode::Op_code::load>(variable.location.offset, std::int8_t{ 0 });
			break;
		default:
			// TODO
			BIA_ASSERT(false);
		}
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value.is_type<Token::Number>()) {
		return number_value(param, tokens);
	} else if (tokens.front().value.is_type<Token::Identifier>()) {
		symbol::Variable variable{};
		const auto right = param.symbols.symbol(tokens.front().value.get<Token::Identifier>().memory);
		if (right.empty()) {
			param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(+0, 1));
		} else if (!right.is_type<symbol::Variable>()) {
			param.errors.add_error(error::Code::symbol_not_a_variable, tokens.subspan(+0, 1));
		} else {
			variable = param.symbols.create_temporary(right.get<symbol::Variable>().definition);
			param.instructor.write<bytecode::Op_code::copy, std::int64_t>(
			  variable.location.offset, right.get<symbol::Variable>().location.offset);
		}
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value.is_type<Token::String>()) {
		const auto right = param.symbols.symbol(util::from_cstring("string"));
		BIA_ASSERT(right.is_type<type::Definition*>());

		const auto variable = param.symbols.create_temporary(right.get<type::Definition*>());
		const auto index    = param.serializer.index_of(tokens.front().value.get<Token::String>().memory);
		param.instructor.write<bytecode::Op_code::load_resource, memory::gc::String>(variable.location.offset,
		                                                                             index);
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value.is_type<Token::Regex>()) {
		const auto right = param.symbols.symbol(util::from_cstring("regex"));
		BIA_ASSERT(right.is_type<type::Definition*>());

		const auto variable = param.symbols.create_temporary(right.get<type::Definition*>());
		const auto index    = param.serializer.index_of(tokens.front().value.get<Token::Regex>().memory);
		param.instructor.write<bytecode::Op_code::load_resource, memory::gc::Regex>(variable.location.offset,
		                                                                            index);
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value == Token::Control::bracket_open) {
		Jumper jumper{ param.instructor };
		symbol::Variable variable;
		std::tie(tokens, variable) = single_expression_impl(param, tokens.subspan(1), jumper, -1);
		BIA_ASSERT(!tokens.empty() && tokens.front().value == Token::Control::bracket_close);
		return { tokens.subspan(1), variable };
	}

	// TODO
	BIA_ASSERT(false);
}

inline std::pair<Tokens, symbol::Variable> single_expression_impl(Parameter& param, Tokens tokens,
                                                                  Jumper& jumper, int precedence)
{
	BIA_EXPECTS(!tokens.empty());

	bool last_cond_was_and = false;
	// handle left hand side
	symbol::Variable lhs;
	auto lhs_tokens       = tokens;
	std::tie(tokens, lhs) = value(param, tokens);
	lhs_tokens            = lhs_tokens.subspan(+0, lhs_tokens.size() - tokens.size());

	while (has_right_hand_size(tokens)) {
		const auto optor           = tokens.front().value.get<Operator>();
		const int optor_precedence = precedence_of(optor);

		// only if we have higher precedence
		if (optor_precedence <= precedence) {
			break;
		}

		// logical chaining
		if (optor == Operator::logical_and || optor == Operator::logical_or) {
			if (last_cond_was_and && optor == Operator::logical_or) {
				jumper.mark(Jumper::Destination::end);
				jumper.clear(Jumper::Destination::end);
				last_cond_was_and = false;
			} else if (optor == Operator::logical_and) {
				last_cond_was_and = true;
			}

			param.instructor.write<bytecode::Op_code::truthy, std::int32_t>(lhs.location.offset);
			param.symbols.free_temporary(lhs);
			jumper.jump(optor == Operator::logical_and ? Jumper::Type::if_false : Jumper::Type::if_true,
			            Jumper::Destination::end);
			std::tie(tokens, lhs) = single_expression_impl(param, tokens.subspan(1), jumper, optor_precedence);
			continue;
		}

		// function call
		if (optor == Operator::function_call_open) {
			bool dont_check = false;
			if (!dynamic_cast<const type::Function*>(lhs.definition)) {
				param.errors.add_error(error::Code::not_a_function, lhs_tokens);
				dont_check = true;
			}

			// TODO support return types
			if (!dont_check) {
				type::Void v;
				BIA_ASSERT(!static_cast<const type::Function*>(lhs.definition)->return_type()->compare(&v));
			}

			tokens = tokens.subspan(1);
			// TODO stack offset for functions
			const auto stack_offset = param.symbols.stack_position();
			std::vector<symbol::Variable> arguments;
			// TODO check argument types
			while (tokens.front().value != Operator::function_call_close) {
				symbol::Variable arg;
				BIA_ASSERT(tokens.front().value.is_type<Token::Number>());
				std::tie(tokens, arg) = single_expression(param, tokens);
				arguments.push_back(param.symbols.push(arg));
				if (arguments.back().location.offset != arg.location.offset) {
					// TODO type
					if (!dont_check) {
					}
					param.instructor.write<bytecode::Op_code::copy, std::int64_t>(arguments.back().location.offset,
					                                                              arg.location.offset);
					param.symbols.free_temporary(arg);
				}
				// TODO push
				BIA_ASSERT(tokens.front().value == Operator::function_call_close ||
				           tokens.front().value == Token::Control::comma);
				if (tokens.front().value == Token::Control::comma) {
					tokens = tokens.subspan(1);
				}
			}
			param.instructor.write<bytecode::Op_code::invoke>(lhs.location.offset, stack_offset);
			tokens = tokens.subspan(1);
			for (const auto& arg : arguments) {
				param.symbols.pop(arg);
			}
			continue;
		}

		// TODO add member access
		BIA_EXPECTS(optor != Operator::member_access);

		// right hand side
		symbol::Variable rhs;
		auto rhs_tokens       = tokens.subspan(1);
		std::tie(tokens, rhs) = single_expression_impl(param, rhs_tokens, jumper, optor_precedence);
		rhs_tokens            = rhs_tokens.subspan(+0, rhs_tokens.size() - tokens.size());

		// TODO
		if (lhs.definition->compare(rhs.definition) &&
		    !(dynamic_cast<type::Regex*>(lhs.definition) && dynamic_cast<type::String*>(rhs.definition))) {
			param.errors.add_error(error::Code::type_mismatch, rhs_tokens);
		}

		if (is_test_operator(optor)) {
			// TODO
			const auto bool_type = param.symbols.symbol(util::from_cstring("bool"));
			BIA_ASSERT(bool_type.is_type<type::Definition*>());

			if (dynamic_cast<type::Integer*>(lhs.definition)) {
				param.instructor.write<bytecode::Op_code::unsigned_raw_operation, std::int32_t>(
				  to_operation(optor), lhs.location.offset, rhs.location.offset);
			} else if (dynamic_cast<type::String*>(lhs.definition)) {
				param.instructor.write<bytecode::Op_code::resource_operation, memory::gc::String>(
				  to_operation(optor), lhs.location.offset, rhs.location.offset);
			} else if (dynamic_cast<type::Regex*>(lhs.definition)) {
				param.instructor.write<bytecode::Op_code::resource_operation, memory::gc::Regex>(
				  to_operation(optor), lhs.location.offset, rhs.location.offset);
			} else {
				// TODO
				BIA_ASSERT(false);
			}
			param.symbols.free_temporary(rhs);
			param.symbols.free_temporary(lhs);
			lhs = param.symbols.create_temporary(bool_type.get<type::Definition*>());
			param.instructor.write<bytecode::Op_code::booleanize>(lhs.location.offset);
		} else {
			if (!dynamic_cast<type::Integer*>(lhs.definition)) {
				param.errors.add_error(error::Code::not_an_integral, lhs_tokens);
			} else {
				param.instructor.write<bytecode::Op_code::unsigned_raw_operation, std::int32_t>(
				  to_operation(optor), lhs.location.offset, rhs.location.offset);
			}
			param.symbols.free_temporary(rhs);
		}
	}

	jumper.mark(Jumper::Destination::end);
	return { tokens, lhs };
}

std::pair<Tokens, symbol::Variable> single_expression(Parameter& param, Tokens tokens)
{
	Jumper jumper{ param.instructor };
	return single_expression_impl(param, tokens, jumper, -1);
}

} // namespace elve
} // namespace compiler
} // namespace bia
