#ifndef BIA_COMPILER_ELVE_EXPRESSION_HPP_
#define BIA_COMPILER_ELVE_EXPRESSION_HPP_

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
    expression(bytecode::writer::instruction& writer, util::not_null<const tokenizer::token::token*> first,
               util::not_null<const tokenizer::token::token*> last, T&& destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(first + 2 <= last && static_cast<token::type>(first[1].value.index()) == token::type::cmd_end);

	// parse value
	switch (static_cast<token::type>(first->value.index())) {
	case token::type::constant_int: {
		writer.write<true, bytecode::oc_instantiate>(std::forward<T>(destination),
		                                             first->value.get<token::int_type>());

		break;
	}
	default: BIA_IMPLEMENTATION_ERROR("invalid token type");
	}

	return first + 2;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif