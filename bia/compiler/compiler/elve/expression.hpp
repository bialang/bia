#ifndef BIA_COMPILER_ELVE_EXPRESSION_HPP_
#define BIA_COMPILER_ELVE_EXPRESSION_HPP_

#include "member.hpp"
#include "present.hpp"

#include <bytecode/writer/instruction.hpp>
#include <exception/implementation_error.hpp>
#include <tokenizer/token/token.hpp>
#include <tuple>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename Destination>
inline const tokenizer::token::token* value(present present, util::span<const tokenizer::token::token> tokens,
                                            Destination&& destination)
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

	return tokens.data() + 1;
}

bool is_valid(util::span<const tokenizer::token::token> tokens)
{
	// todo:
	return tokens.size() > 1;
}

template<typename Destination>
inline const tokenizer::token::token*
    expression(present present, util::span<const tokenizer::token::token> tokens, Destination&& destination,
               tokenizer::token::precedence_type precedence)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty());

	// parse value single value
	if (tokens.size() == 1 ||
	    static_cast<token::type>(tokens.data()[1].value.index()) != token::type::operator_ ||
	    type_of(tokens.data()[1].value.get<operator_>()) == operator_type::prefix) {
		return value(present, tokens, std::forward<Destination>(destination));
	}

	BIA_EXPECTS(static_cast<token::type>(tokens.data()[1].value.index()) == token::type::operator_);

	const auto op = tokens.data()[1].value.get<operator_>();

	// only if we have higher precedence
	if (precedence_of(op) > precedence) {
		// left hand
		value(present, tokens.subspan(0, 1), bytecode::member::tos{});

		const bytecode::member::local left{ present.variable_manager.add_tmp().id };

		while (is_valid(tokens = tokens.subspan(2))) {
			// right hand
			tokens = tokens.subspan(expression(present, tokens, bytecode::member::tos{}, precedence_of(op)) -
			                        tokens.data());

			const bytecode::member::local right{ present.variable_manager.add_tmp().id };

			// call operator
			present.writer.write<true, bytecode::oc_operator>(left, right, unique_id_of(op), left);
			present.variable_manager.remove_tmp();
			present.writer.write<true, bytecode::oc_drop>(1);
		}

		present.variable_manager.remove_tmp();

		// destination was not tos
		if (!std::is_same<typename std::decay<Destination>::type, bytecode::member::tos>::value) {
			present.writer.write<true, bytecode::oc_refer>(left, std::forward<Destination>(destination));
			present.writer.write<true, bytecode::oc_drop>(1);
		}

		return tokens.data();
	}

	// caller has higher precedence
	return value(present, tokens.subspan(0, 1), std::forward<Destination>(destination));
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
