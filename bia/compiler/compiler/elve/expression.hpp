#ifndef BIA_COMPILER_ELVE_EXPRESSION_HPP_
#define BIA_COMPILER_ELVE_EXPRESSION_HPP_

#include "member.hpp"
#include "present.hpp"

#include <bytecode/writer/instruction.hpp>
#include <exception/implementation_error.hpp>
#include <tokenizer/token/token.hpp>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename T>
inline const tokenizer::token::token*
    expression(present present, util::span<const tokenizer::token::token> tokens, T&& destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty());

	// parse value
	switch (static_cast<token::type>(tokens.data()->value.index())) {
	case token::type::identifier: return member(present, tokens, std::forward<T>(destination));
	case token::type::keyword: {
		int val = 0;

		switch (static_cast<token::keyword>(tokens.data()->value.get<token::keyword>())) {
		case token::keyword::true_: val = 1;
		case token::keyword::false_: {
			present.writer.write<true, bytecode::oc_instantiate>(val, std::forward<T>(destination));

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

		present.writer.write<true, bytecode::oc_refer>(src, std::forward<T>(destination));

		break;
	}
	case token::type::constant_int: {
		present.writer.write<true, bytecode::oc_instantiate>(tokens.data()->value.get<token::int_type>(),
		                                                     std::forward<T>(destination));

		break;
	}
	default: BIA_IMPLEMENTATION_ERROR("invalid token type");
	}

	return tokens.data() + 1;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif