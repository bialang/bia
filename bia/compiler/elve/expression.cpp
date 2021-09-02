#include "../jumper.hpp"
#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
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

inline util::Optional<symbol::Local_variable>
  apply_self_operator(Parameter& param, Operator optor, Tokens optor_tokens, symbol::Local_variable variable)
{
	if (optor == Operator::logical_not) {
		const auto bool_type = param.symbols.symbol(util::from_cstring("bool"));
		BIA_ASSERT(bool_type.is_type<const type::Definition_base*>());
		// TODO test size
		BIA_ASSERT(false);
		// param.instructor.write<bytecode::Op_code::falsey, std::int8_t>(variable.location.offset);
		// param.symbols.free_temporary(variable);
		// variable = param.symbols.create_temporary(bool_type.get<const type::Definition*>());
		// param.instructor.write<bytecode::Op_code::booleanize>(variable.location.offset);
		return variable;
	}
	param.errors.add_error(error::Code::bad_operator, optor_tokens);
	return {};
}

/// Handles the given operation between the left-hand and the right-hand side. If the operator is of a testing
/// type, both lhs and rhs will be freed and a new result will be returned.
inline symbol::Local_variable handle_operation(Parameter& param, const symbol::Local_variable& lhs,
                                               const symbol::Local_variable& rhs, Operator optor,
                                               Tokens optor_tokens)
{
	using namespace bytecode;
	// TODO improve test depending on situation
	if (!lhs.definition->is_assignable(rhs.definition)) {
		param.errors.add_error(error::Code::type_mismatch, optor_tokens);
		return lhs;
	}
	bool is_test = false;
	switch (optor) {
	// case Operator::assign: break;
	// case Operator::logical_or: break;
	// case Operator::logical_and: break;
	// case Operator::logical_not: break;
	case Operator::equal:
		param.instructor.write<Op_code::equal>(Size::bit_32, lhs.offset, rhs.offset);
		is_test = true;
		break;
	case Operator::not_equal:
		param.instructor.write<Op_code::not_equal>(Size::bit_32, lhs.offset, rhs.offset);
		is_test = true;
		break;
	case Operator::less: {
		if (lhs.definition->flags() & type::Definition_base::flag_unsigned) {
			param.instructor.write<Op_code::sless_than>(Size::bit_32, lhs.offset, rhs.offset);
		} else {
			param.instructor.write<Op_code::sless_than>(Size::bit_32, lhs.offset, rhs.offset);
		}
		is_test = true;
		break;
	}
	case Operator::less_equal: {
		if (lhs.definition->flags() & type::Definition_base::flag_unsigned) {
			param.instructor.write<Op_code::sless_equal_than>(Size::bit_32, lhs.offset, rhs.offset);
		} else {
			param.instructor.write<Op_code::sless_equal_than>(Size::bit_32, lhs.offset, rhs.offset);
		}
		is_test = true;
		break;
	}
	case Operator::greater: {
		if (lhs.definition->flags() & type::Definition_base::flag_unsigned) {
			param.instructor.write<Op_code::sgreater_than>(Size::bit_32, lhs.offset, rhs.offset);
		} else {
			param.instructor.write<Op_code::sgreater_than>(Size::bit_32, lhs.offset, rhs.offset);
		}
		is_test = true;
		break;
	}
	case Operator::greater_equal: {
		if (lhs.definition->flags() & type::Definition_base::flag_unsigned) {
			param.instructor.write<Op_code::sgreater_equal_than>(Size::bit_32, lhs.offset, rhs.offset);
		} else {
			param.instructor.write<Op_code::sgreater_equal_than>(Size::bit_32, lhs.offset, rhs.offset);
		}
		is_test = true;
		break;
	}
	// case Operator::in: break;
	// case Operator::three_way_comparison: break;
	case Operator::bitwise_or:
		param.instructor.write<Op_code::bitwise_or>(Size::bit_32, lhs.offset, rhs.offset);
		break;
	case Operator::bitwise_xor:
		param.instructor.write<Op_code::bitwise_xor>(Size::bit_32, lhs.offset, rhs.offset);
		break;
	case Operator::bitwise_and:
		param.instructor.write<Op_code::bitwise_and>(Size::bit_32, lhs.offset, rhs.offset);
		break;
	// case Operator::bitwise_left_shift: break;
	// case Operator::bitwise_right_shift: break;
	case Operator::plus: param.instructor.write<Op_code::add>(Size::bit_32, lhs.offset, rhs.offset); break;
	case Operator::minus: param.instructor.write<Op_code::sub>(Size::bit_32, lhs.offset, rhs.offset); break;
	case Operator::multiply: param.instructor.write<Op_code::mul>(Size::bit_32, lhs.offset, rhs.offset); break;
	case Operator::divide: {
		if (lhs.definition->flags() & type::Definition_base::flag_unsigned) {
			param.instructor.write<Op_code::udiv>(Size::bit_32, lhs.offset, rhs.offset);
		} else {
			param.instructor.write<Op_code::sdiv>(Size::bit_32, lhs.offset, rhs.offset);
		}
		break;
	}
	case Operator::modulus: {
		if (lhs.definition->flags() & type::Definition_base::flag_unsigned) {
			param.instructor.write<Op_code::urem>(Size::bit_32, lhs.offset, rhs.offset);
		} else {
			param.instructor.write<Op_code::srem>(Size::bit_32, lhs.offset, rhs.offset);
		}
		break;
	}
	// case Operator::unary_minus: break;
	// case Operator::bitwise_not: break;
	// case Operator::exponentation: break;
	// case Operator::member_access: break;
	// case Operator::nullable_member_access: break;
	// case Operator::function_call_open: break;
	// case Operator::nullable_function_call_open: break;
	// case Operator::function_call_close: break;
	default: param.errors.add_error(error::Code::unsupported_operator, optor_tokens); break;
	}

	if (is_test) {
		const auto bool_type = param.symbols.symbol(util::from_cstring("bool"));
		BIA_ASSERT(bool_type.is_type<const type::Definition_base*>());
		param.symbols.free_temporary(rhs);
		param.symbols.free_temporary(lhs);
		return param.symbols.create_temporary(bool_type.get<const type::Definition_base*>());
	}
	return lhs;
}

inline std::pair<Tokens, util::Optional<symbol::Local_variable>>
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
	util::Optional<symbol::Local_variable> lhs;
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
		const auto optor_tokens    = tokens.subspan(+0, 1);
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
			BIA_ASSERT(false);
			// if (last_cond_was_and && optor == Operator::logical_or) {
			// 	jumper.mark(Jumper::Destination::end);
			// 	jumper.clear(Jumper::Destination::end);
			// 	last_cond_was_and = false;
			// } else if (optor == Operator::logical_and) {
			// 	last_cond_was_and = true;
			// }

			// param.instructor.write<bytecode::Op_code::truthy, std::int32_t>(lhs->location.offset);
			// param.symbols.free_temporary(*lhs);
			// jumper.jump(optor == Operator::logical_and ? Jumper::Type::if_false : Jumper::Type::if_true,
			//             Jumper::Destination::end);
			// std::tie(tokens, lhs) = single_expression_impl(param, tokens.subspan(1), jumper, optor_precedence);
			// continue;
		} // function call
		else if (optor == Operator::function_call_open || optor == Operator::nullable_function_call_open) {
			util::Optional<symbol::Local_variable> result;
			std::tie(tokens, result) = member_invocation(param, tokens, lhs, lhs_tokens);
			if (result) {
				lhs = result;
			}
			continue;
		} // member access
		else if (optor == Operator::member_access || optor == Operator::nullable_member_access) {
			util::Optional<symbol::Local_variable> result;
			std::tie(tokens, result) = member_access(param, tokens, *lhs, lhs_tokens);
			if (result) {
				lhs = result;
			}
			continue;
		}

		// right hand side
		util::Optional<symbol::Local_variable> rhs;
		auto rhs_tokens       = tokens.subspan(1);
		std::tie(tokens, rhs) = single_expression_impl(param, rhs_tokens, jumper, optor_precedence);
		rhs_tokens            = rhs_tokens.left(tokens.begin());

		if (lhs.has_value()) {
			// TODO
			// if (lhs->definition->compare(rhs->definition) &&
			//     !(dynamic_cast<const type::Regex*>(lhs->definition) &&
			//       dynamic_cast<const type::String*>(rhs->definition))) {
			// 	param.errors.add_error(error::Code::type_mismatch, rhs_tokens);
			// }

			if (!(lhs->definition->flags() & internal::type::Definition_base::flag_arithmetic)) {
				param.errors.add_error(error::Code::not_an_integral, lhs_tokens);
			} else {
				lhs = handle_operation(param, *lhs, *rhs, optor, optor_tokens);
			}
		}
		param.symbols.free_temporary(*rhs);

		// if (is_test_operator(optor)) {
		// 	// TODO
		// 	const auto bool_type = param.symbols.symbol(util::from_cstring("bool"));
		// 	BIA_ASSERT(bool_type.is_type<const type::Definition*>());

		// 	if (dynamic_cast<const type::Integer*>(lhs->definition)) {
		// 		param.instructor.write<bytecode::Op_code::unsigned_raw_operation, std::int32_t>(
		// 		  to_operation(optor), lhs->location.offset, rhs->location.offset);
		// 	} else if (dynamic_cast<const type::String*>(lhs->definition)) {
		// 		param.instructor.write<bytecode::Op_code::resource_operation, memory::gc::String>(
		// 		  to_operation(optor), lhs->location.offset, rhs->location.offset);
		// 	} else if (dynamic_cast<const type::Regex*>(lhs->definition)) {
		// 		param.instructor.write<bytecode::Op_code::resource_operation, memory::gc::Regex>(
		// 		  to_operation(optor), lhs->location.offset, rhs->location.offset);
		// 	} else {
		// 		// TODO
		// 		BIA_ASSERT(false);
		// 	}
		// 	param.symbols.free_temporary(*rhs);
		// 	param.symbols.free_temporary(*lhs);
		// 	lhs = param.symbols.create_temporary(bool_type.get<const type::Definition*>());
		// 	param.instructor.write<bytecode::Op_code::booleanize>(lhs->location.offset);
		// } else {
		// 	if (!dynamic_cast<const type::Integer*>(lhs->definition)) {
		// 		param.errors.add_error(error::Code::not_an_integral, lhs_tokens);
		// 	} else {
		// 		param.instructor.write<bytecode::Op_code::unsigned_raw_operation, std::int32_t>(
		// 		  to_operation(optor), lhs->location.offset, rhs->location.offset);
		// 	}
		// 	param.symbols.free_temporary(*rhs);
		// }
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

std::pair<Tokens, util::Optional<symbol::Local_variable>> single_expression(Parameter& param, Tokens tokens)
{
	Jumper jumper{ param.instructor };
	return single_expression_impl(param, tokens, jumper, -1);
}

} // namespace elve
} // namespace compiler
} // namespace bia
