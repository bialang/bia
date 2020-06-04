#ifndef BIA_COMPILER_ELVE_EXPRESSION_HPP_
#define BIA_COMPILER_ELVE_EXPRESSION_HPP_

#include "../jump_manager.hpp"
#include "member.hpp"
#include "present.hpp"

#include <bytecode/writer/instruction.hpp>
#include <exception/implementation_error.hpp>
#include <tokenizer/token/token.hpp>
#include <tuple>
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
	// todo:
	return tokens.size() > 1;
}

template<typename Destination>
inline tokens_type expression_impl(present present, tokens_type tokens, Destination&& destination,
                                   tokenizer::token::precedence_type precedence, jump_manager& jumper)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty());

	// parse value single value
	if (tokens.size() == 1 ||
	    static_cast<token::type>(tokens.data()[1].value.index()) != token::type::operator_ ||
	    type_of(tokens.data()[1].value.get<operator_>()) == operator_type::prefix) {
		return value(present, tokens, std::forward<Destination>(destination));
	}

	tokens = value(present, tokens, bytecode::member::tos{});

	const bytecode::member::local left{ present.variable_manager.add_tmp().id };
	auto last_logical_and = false;

	while (valid_right_hand(tokens)) {
		const auto op = tokens.data()->value.get<operator_>();

		// only if we have higher precedence
		if (precedence_of(op) <= precedence) {
			break;
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

			tokens = expression_impl(present, tokens.subspan(1), left, precedence_of(op), jumper);

			continue;
		}

		// right hand
		tokens =
		    expression_impl(present, tokens.subspan(1), bytecode::member::tos{}, precedence_of(op), jumper);

		const bytecode::member::local right{ present.variable_manager.add_tmp().id };

		// call operator
		present.writer.write<true, bytecode::oc_operator>(left, right, unique_id_of(op), left);
		present.writer.write<true, bytecode::oc_drop>(1);
		present.variable_manager.remove_tmp();
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
