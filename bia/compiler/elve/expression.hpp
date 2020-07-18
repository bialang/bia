#ifndef BIA_COMPILER_ELVE_EXPRESSION_HPP_
#define BIA_COMPILER_ELVE_EXPRESSION_HPP_

#include "../jump_manager.hpp"
#include "member.hpp"
#include "present.hpp"

#include <bia/bytecode/writer/instruction.hpp>
#include <bia/exception/implementation_error.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <tuple>
#include <type_traits>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {
namespace detail {

inline bool is_test_operator(tokenizer::token::operator_ op)
{
	using namespace tokenizer::token;

	return op == operator_::equal || op == operator_::not_equal || op == operator_::less ||
	       op == operator_::less_equal || op == operator_::greater || op == operator_::greater_equal ||
	       op == operator_::in || op == operator_::three_way_comparison;
}

template<typename Destination>
inline tokens_type value(present present, tokens_type tokens, Destination destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty());

	switch (static_cast<token::type>(tokens.data()->value.index())) {
	case token::type::identifier: return member(present, tokens, destination);
	case token::type::keyword: {
		int val = 0;

		switch (tokens.data()->value.get<token::keyword>()) {
		case token::keyword::true_: val = 1;
		case token::keyword::false_: {
			present.writer.write<true, bytecode::oc_instantiate>(val, destination);

			break;
		}
		case token::keyword::null: {
			present.writer.write<true, bytecode::oc_instantiate>(nullptr, destination);

			break;
		}
		default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
		}

		break;
	}
	case token::type::constant_string: {
		// todo
		bytecode::member::resource src{ (std::uint16_t) present.resources.index_of(
			tokens.data()->value.get<token::string>().memory) };

		present.writer.write<true, bytecode::oc_refer>(src, std::forward<Destination>(destination));

		break;
	}
	case token::type::constant_regex: {
		// todo
		bytecode::member::resource src{ (std::uint16_t) present.resources.index_of(
			tokens.data()->value.get<token::regex>().memory) };

		present.writer.write<true, bytecode::oc_refer>(src, std::forward<Destination>(destination));

		break;
	}
	case token::type::constant_int: {
		present.writer.write<true, bytecode::oc_instantiate>(tokens.data()->value.get<token::int_type>(),
		                                                     std::forward<Destination>(destination));

		break;
	}
	case token::type::constant_float: {
		present.writer.write<true, bytecode::oc_instantiate>(tokens.data()->value.get<double>(),
		                                                     std::forward<Destination>(destination));

		break;
	}
	default: BIA_IMPLEMENTATION_ERROR("invalid token type");
	}

	return tokens.subspan(1);
}

inline bool valid_right_hand(tokens_type tokens)
{
	using namespace tokenizer::token;

	// todo:
	return tokens.size() > 1 &&
	       static_cast<token::type>(tokens.data()->value.index()) == token::type::operator_;
}

template<typename Member>
inline void apply_self_operator(present present, tokenizer::token::operator_ op, Member mem)
{
	using namespace tokenizer::token;

	if (op == operator_::logical_not) {
		present.writer.write<true, bytecode::oc_test>(
		    static_cast<typename std::underlying_type<member::test_operator>::type>(
		        member::test_operator::self),
		    mem, mem);
		present.writer.write<true, bytecode::oc_invert>();
		present.writer.write<true, bytecode::oc_instantiate>(bytecode::test_register{}, mem);
	} else {
		present.writer.write<true, bytecode::oc_self_operator>(
		    static_cast<typename std::underlying_type<member::infix_operator>::type>(to_self_operator(op)),
		    mem, mem);
	}
}

template<typename Destination>
inline tokens_type expression_impl(present present, tokens_type tokens, Destination destination,
                                   tokenizer::token::precedence_type precedence, jump_manager& jumper)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty());

	std::pair<bool, operator_> self_operator{ false, operator_::unary_minus };

	// has self operator
	if (static_cast<token::type>(tokens.data()->value.index()) == token::type::operator_) {
		self_operator.first  = true;
		self_operator.second = tokens.data()->value.get<operator_>();
		tokens               = tokens.subspan(1);

		BIA_EXPECTS(!tokens.empty());
	}

	auto last_logical_and = false;

	tokens = value(present, tokens, destination);

	while (valid_right_hand(tokens)) {
		const auto op            = tokens.data()->value.get<operator_>();
		const auto op_precedence = precedence_of(op);

		// only if we have higher precedence
		if (op_precedence <= precedence) {
			break;
		}

		// prefix operator is stronger
		if (self_operator.first && op_precedence <= precedence_of(self_operator.second)) {
			apply_self_operator(present, self_operator.second, destination);

			self_operator.first = false;
		}

		// logical chaining
		if (op == operator_::logical_and || op == operator_::logical_or) {
			if (last_logical_and && op == operator_::logical_or) {
				jumper.mark(jump_manager::destination::end);
				jumper.clear(jump_manager::destination::end);

				last_logical_and = false;
			} else if (op == operator_::logical_and) {
				last_logical_and = true;
			}

			present.writer.write<true, bytecode::oc_test>(
			    static_cast<typename std::underlying_type<member::test_operator>::type>(
			        member::test_operator::self),
			    destination, destination);
			jumper.jump(op == operator_::logical_and ? jump_manager::type::if_false
			                                         : jump_manager::type::if_true,
			            jump_manager::destination::end);

			tokens = expression_impl(present, tokens.subspan(1), destination, op_precedence, jumper);

			continue;
		}

		if (op == operator_::member_access) {
			present.writer.write<true, bytecode::oc_get>(
			    destination,
			    bytecode::member::resource{
			        present.resources.index_of(tokens.data()[1].value.get<token::identifier>().memory) },
			    destination);

			tokens = member_call(present, tokens.subspan(2), destination, destination);
		} else {
			// right hand
			const bytecode::member::local right{ present.variables.add_tmp() };

			tokens = expression_impl(present, tokens.subspan(1), right, op_precedence, jumper);

			// call operator
			if (detail::is_test_operator(op)) {
				present.writer.write<true, bytecode::oc_test>(
				    static_cast<typename std::underlying_type<member::test_operator>::type>(
				        to_test_operator(op)),
				    destination, right);
				present.writer.write<true, bytecode::oc_instantiate>(bytecode::test_register{}, destination);
			} else {
				present.writer.write<true, bytecode::oc_operator>(
				    destination, right,
				    static_cast<typename std::underlying_type<member::infix_operator>::type>(
				        to_infix_operator(op)),
				    destination);
			}

			present.variables.remove_tmp(right.index);
		}
	}

	// apply self operator
	if (self_operator.first) {
		apply_self_operator(present, self_operator.second, destination);
	}

	jumper.mark(jump_manager::destination::end);

	return tokens;
}

} // namespace detail

template<typename Destination>
inline tokens_type expression(present present, tokens_type tokens, Destination destination)
{
	jump_manager jumper{ &present.writer.output() };

	return detail::expression_impl(present, tokens, destination, -1, jumper);
}

inline tokens_type expression(present present, tokens_type tokens, bytecode::member::push destination)
{
	bytecode::member::local tmp{ present.variables.add_tmp() };

	tokens = expression(present, tokens, tmp);

	present.writer.write<true, bytecode::oc_refer>(tmp, destination);
	present.variables.remove_tmp(tmp.index);

	return tokens;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
