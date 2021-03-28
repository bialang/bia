#include "../jumper.hpp"
#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/integer.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>
#include <bia/util/optional.hpp>

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

inline std::pair<Tokens, util::Optional<symbol::Variable>>
  member_invocation(Parameter& param, Tokens tokens, symbol::Variable function, Tokens function_tokens)
{
	BIA_EXPECTS(tokens.front().value == Operator::function_call_open);
	BIA_EXPECTS(param.symbols.is_tos(function));

	const std::vector<type::Argument>* argument_definitions = nullptr;
	if (const auto ptr = dynamic_cast<const type::Function*>(function.definition)) {
		argument_definitions = &ptr->arguments();
	} else {
		param.errors.add_error(error::Code::not_a_function, function_tokens);
	}

	std::vector<symbol::Variable> pushed;
	tokens = tokens.subspan(1);
	while (tokens.front().value != Operator::function_call_close) {
		util::Optional<symbol::Variable> argument;
		auto argument_tokens       = tokens;
		std::tie(tokens, argument) = single_expression(param, argument_tokens);
		argument_tokens            = argument_tokens.left(tokens.begin());
		if (argument) {
			pushed.push_back(param.symbols.push(*argument));
			// check type
			if (argument_definitions && pushed.size() <= argument_definitions->size() &&
			    !argument_definitions->at(pushed.size() - 1).definition->is_assignable(argument->definition)) {
				param.errors.add_error(error::Code::type_mismatch, argument_tokens);
			}

			// TODO
			BIA_ASSERT(pushed.back().location.offset == argument->location.offset);
		}
		// remove comma
		if (tokens.front().value == Token::Control::comma) {
			tokens = tokens.subspan(1);
		}
	}
	// check argument count
	if (argument_definitions && pushed.size() < argument_definitions->size()) {
		param.errors.add_error(error::Code::too_few_arguments, function_tokens);
	} else if (argument_definitions && pushed.size() > argument_definitions->size()) {
		param.errors.add_error(error::Code::too_many_arguments, function_tokens);
	}
	// invoke
	param.instructor.write<bytecode::Op_code::invoke>(function.location.offset);
	tokens = tokens.subspan(1);
	for (const auto& arg : pushed) {
		param.symbols.pop(arg);
	}
	// result
	if (const auto ptr = dynamic_cast<const type::Function*>(function.definition)) {
		param.symbols.free_temporary(function);
		return { tokens, param.symbols.create_temporary(ptr->return_type()) };
	}
	return { tokens, {} };
}

inline util::Optional<symbol::Variable> apply_self_operator(Parameter& param, Operator optor,
                                                            Tokens optor_tokens, symbol::Variable variable)
{
	if (optor == Operator::logical_not) {
		const auto bool_type = param.symbols.symbol(util::from_cstring("bool"));
		BIA_ASSERT(bool_type.is_type<const type::Definition*>());
		// TODO test size
		param.instructor.write<bytecode::Op_code::falsey, std::int8_t>(variable.location.offset);
		param.symbols.free_temporary(variable);
		variable = param.symbols.create_temporary(bool_type.get<const type::Definition*>());
		param.instructor.write<bytecode::Op_code::booleanize>(variable.location.offset);
		return variable;
	}
	param.errors.add_error(error::Code::bad_operator, optor_tokens);
	return {};
}

inline std::pair<Tokens, util::Optional<symbol::Variable>>
  single_expression_impl(Parameter& param, Tokens tokens, Jumper& jumper, int precedence)
{
	BIA_EXPECTS(!tokens.empty());

	bool last_cond_was_and = false;

	// has self operator
	util::Optional<std::pair<Operator, Tokens>> self_operator;
	if (tokens.front().value.is_type<Operator>()) {
		self_operator = std::make_pair(tokens.front().value.get<Operator>(), tokens.subspan(+0, 1));
		tokens        = tokens.subspan(1);
		BIA_ASSERT(!tokens.empty());
	}

	// handle left hand side
	util::Optional<symbol::Variable> lhs;
	auto lhs_tokens = tokens;
	// in parentheses
	if (tokens.front().value == Token::Control::bracket_open) {
		Jumper jumper{ param.instructor };
		std::tie(tokens, lhs) = single_expression_impl(param, tokens.subspan(1), jumper, -1);
		BIA_ASSERT(!tokens.empty() && tokens.front().value == Token::Control::bracket_close);
		tokens = tokens.subspan(1);
	} else {
		std::tie(tokens, lhs) = value(param, tokens);
	}
	lhs_tokens = lhs_tokens.left(tokens.begin());

	while (has_right_hand_size(tokens)) {
		const auto optor           = tokens.front().value.get<Operator>();
		const int optor_precedence = precedence_of(optor);

		// only if we have higher precedence
		if (optor_precedence <= precedence) {
			break;
		}

		// prefix is stronger
		if (self_operator && optor_precedence <= precedence_of(self_operator->first)) {
			const auto result = apply_self_operator(param, self_operator->first, self_operator->second, *lhs);
			if (result) {
				lhs = result;
			}
			self_operator.clear();
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

			param.instructor.write<bytecode::Op_code::truthy, std::int32_t>(lhs->location.offset);
			param.symbols.free_temporary(*lhs);
			jumper.jump(optor == Operator::logical_and ? Jumper::Type::if_false : Jumper::Type::if_true,
			            Jumper::Destination::end);
			std::tie(tokens, lhs) = single_expression_impl(param, tokens.subspan(1), jumper, optor_precedence);
			continue;
		}

		// function call
		if (optor == Operator::function_call_open || optor == Operator::nullable_function_call_open) {
			util::Optional<symbol::Variable> result;
			std::tie(tokens, result) = member_invocation(param, tokens, *lhs, lhs_tokens);
			if (result) {
				lhs = result;
			}
			continue;
		}

		// TODO add member access
		if (optor == Operator::member_access || optor == Operator::nullable_member_access) {
			BIA_ASSERT(false);
		}

		// right hand side
		util::Optional<symbol::Variable> rhs;
		auto rhs_tokens       = tokens.subspan(1);
		std::tie(tokens, rhs) = single_expression_impl(param, rhs_tokens, jumper, optor_precedence);
		rhs_tokens            = rhs_tokens.left(tokens.begin());

		// TODO
		if (lhs->definition->compare(rhs->definition) && !(dynamic_cast<const type::Regex*>(lhs->definition) &&
		                                                   dynamic_cast<const type::String*>(rhs->definition))) {
			param.errors.add_error(error::Code::type_mismatch, rhs_tokens);
		}

		if (is_test_operator(optor)) {
			// TODO
			const auto bool_type = param.symbols.symbol(util::from_cstring("bool"));
			BIA_ASSERT(bool_type.is_type<const type::Definition*>());

			if (dynamic_cast<const type::Integer*>(lhs->definition)) {
				param.instructor.write<bytecode::Op_code::unsigned_raw_operation, std::int32_t>(
				  to_operation(optor), lhs->location.offset, rhs->location.offset);
			} else if (dynamic_cast<const type::String*>(lhs->definition)) {
				param.instructor.write<bytecode::Op_code::resource_operation, memory::gc::String>(
				  to_operation(optor), lhs->location.offset, rhs->location.offset);
			} else if (dynamic_cast<const type::Regex*>(lhs->definition)) {
				param.instructor.write<bytecode::Op_code::resource_operation, memory::gc::Regex>(
				  to_operation(optor), lhs->location.offset, rhs->location.offset);
			} else {
				// TODO
				BIA_ASSERT(false);
			}
			param.symbols.free_temporary(*rhs);
			param.symbols.free_temporary(*lhs);
			lhs = param.symbols.create_temporary(bool_type.get<const type::Definition*>());
			param.instructor.write<bytecode::Op_code::booleanize>(lhs->location.offset);
		} else {
			if (!dynamic_cast<const type::Integer*>(lhs->definition)) {
				param.errors.add_error(error::Code::not_an_integral, lhs_tokens);
			} else {
				param.instructor.write<bytecode::Op_code::unsigned_raw_operation, std::int32_t>(
				  to_operation(optor), lhs->location.offset, rhs->location.offset);
			}
			param.symbols.free_temporary(*rhs);
		}
	}

	// apply self operator
	if (self_operator) {
		const auto result = apply_self_operator(param, self_operator->first, self_operator->second, *lhs);
		if (result) {
			lhs = result;
		}
	}

	jumper.mark(Jumper::Destination::end);
	return { tokens, lhs };
}

std::pair<Tokens, util::Optional<symbol::Variable>> single_expression(Parameter& param, Tokens tokens)
{
	Jumper jumper{ param.instructor };
	return single_expression_impl(param, tokens, jumper, -1);
}

} // namespace elve
} // namespace compiler
} // namespace bia
