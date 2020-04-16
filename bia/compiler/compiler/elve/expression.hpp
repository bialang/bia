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
inline util::not_null<const tokenizer::token::token*>
    expression(present present, util::not_null<const tokenizer::token::token*> first,
               util::not_null<const tokenizer::token::token*> last, T&& destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(first < last);

	// parse value
	switch (static_cast<token::type>(first->value.index())) {
	case token::type::identifier: return member(present, first, last, std::forward<T>(destination));
	case token::type::keyword: {
		int val = 0;

		switch (static_cast<token::keyword>(first->value.get<token::keyword>())) {
		case token::keyword::true_: val = 1;
		case token::keyword::false_: {
			present.writer.write<true, bytecode::oc_instantiate>(val, std::forward<T>(destination));

			return first + 1;
		}
		default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
		}
	}
	case token::type::constant_string: {
		// todo
		bytecode::member::resource src{ (std::uint16_t) present.resources.index_of(
			first->value.get<token::string>().memory) };

		present.writer.write<true, bytecode::oc_refer>(src, std::forward<T>(destination));

		return first + 1;
	}
	case token::type::constant_int: {
		present.writer.write<true, bytecode::oc_instantiate>(first->value.get<token::int_type>(),
		                                                     std::forward<T>(destination));

		return first + 1;
	}
	default: BIA_IMPLEMENTATION_ERROR("invalid token type");
	}
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif