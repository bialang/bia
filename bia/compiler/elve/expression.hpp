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

template<typename Destination>
inline tokens_type value(present present, tokens_type tokens, Destination&& destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty());

	switch (static_cast<token::type>(tokens.data()->value.index())) {
	case token::type::identifier: return member(present, tokens, std::forward<Destination>(destination));
	case token::type::keyword: {
		int val = 0;

		switch (static_cast<token::keyword>(tokens.data()->value.get<token::keyword>())) {
		case token::keyword::true_: val = 1;
		case token::keyword::false_: {
			present.writer.write<true, bytecode::oc_instantiate>(val, std::forward<Destination>(destination));

			break;
		}
		case token::keyword::null: {
			present.writer.write<true, bytecode::oc_instantiate>(nullptr, std::forward<Destination>(destination));

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
	case token::type::constant_int: {
		present.writer.write<true, bytecode::oc_instantiate>(tokens.data()->value.get<token::int_type>(),
		                                                     std::forward<Destination>(destination));

		break;
	}
	default: BIA_IMPLEMENTATION_ERROR("invalid token type");
	}

	return tokens.subspan(1);
}

inline bool valid_right_hand(util::span<const tokenizer::token::token> tokens)
{
	using namespace tokenizer::token;

	// todo:
	return tokens.size() > 1 &&
	       static_cast<token::type>(tokens.data()->value.index()) == token::type::operator_;
}

template<typename Member>
inline void apply_self_operator(present present, tokenizer::token::operator_ op, Member&& mem)
{
	using namespace tokenizer::token;

	if (op == operator_::logical_not) {
		present.writer.write<true, bytecode::oc_test>(std::forward<Member>(mem));
		present.writer.write<true, bytecode::oc_invert>();
		present.writer.write<true, bytecode::oc_instantiate>(bytecode::test_register{},
		                                                     std::forward<Member>(mem));
	} else {
		present.writer.write<true, bytecode::oc_self_operator>(
		    static_cast<typename std::underlying_type<member::infix_operator>::type>(to_self_operator(op)),
		    std::forward<Member>(mem), std::forward<Member>(mem));
	}
}

template<typename Destination>
inline tokens_type expression_impl(present present, tokens_type tokens, Destination&& destination,
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

	tokens = value(present, tokens, bytecode::member::tos{});

	const bytecode::member::local left{ present.variable_manager.add_tmp().id };
	auto last_logical_and = false;

	while (valid_right_hand(tokens)) {
		const auto op            = tokens.data()->value.get<operator_>();
		const auto op_precedence = precedence_of(op);

		// only if we have higher precedence
		if (op_precedence <= precedence) {
			break;
		}

		// prefix operator is stronger
		if (self_operator.first && op_precedence <= precedence_of(self_operator.second)) {
			apply_self_operator(present, self_operator.second, left);

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

			present.writer.write<true, bytecode::oc_test>(left);
			jumper.jump(op == operator_::logical_and ? jump_manager::type::if_false
			                                         : jump_manager::type::if_true,
			            jump_manager::destination::end);

			tokens = expression_impl(present, tokens.subspan(1), left, op_precedence, jumper);

			continue;
		}

		// right hand
		tokens = expression_impl(present, tokens.subspan(1), bytecode::member::tos{}, op_precedence, jumper);

		const bytecode::member::local right{ present.variable_manager.add_tmp().id };

		// call operator
		present.writer.write<true, bytecode::oc_operator>(
		    left, right,
		    static_cast<typename std::underlying_type<member::infix_operator>::type>(to_infix_operator(op)),
		    left);
		present.writer.write<true, bytecode::oc_drop>(1);
		present.variable_manager.remove_tmp();
	}

	// apply self operator
	if (self_operator.first) {
		apply_self_operator(present, self_operator.second, left);
	}

	jumper.mark(jump_manager::destination::end);

	// destination was not tos
	if (!std::is_same<typename std::decay<Destination>::type, bytecode::member::tos>::value) {
		present.writer.write<true, bytecode::oc_refer>(left, std::forward<Destination>(destination));
		present.writer.write<true, bytecode::oc_drop>(1);
	}

	present.variable_manager.remove_tmp();

	return tokens;
}

} // namespace detail

template<typename Destination>
inline tokens_type expression(present present, tokens_type tokens, Destination&& destination)
{
	jump_manager jumper{ &present.writer.output() };

	return detail::expression_impl(present, tokens, std::forward<Destination>(destination), -1, jumper);
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
