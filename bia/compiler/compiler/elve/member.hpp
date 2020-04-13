#ifndef BIA_COMPILER_ELVE_MEMBER_HPP_
#define BIA_COMPILER_ELVE_MEMBER_HPP_

#include "parameter.hpp"
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
    member(present present, util::not_null<const tokenizer::token::token*> first,
           util::not_null<const tokenizer::token::token*> last, T&& destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(first < last && static_cast<token::type>(first->value.index()) == token::type::identifier);

	auto variable = present.variable_manager.index_of(first->value.get<token::identifier>().memory);

	//BIA_EXPECTS(variable.second != present.variable_manager.latest_variable());

	if (first + 1 < last && static_cast<token::type>(first[1].value.index()) == token::type::control) {
		auto pair = parameter(present, first + 1, last);

		present.writer.write<true, bytecode::oc_invoke>(
		    pair.second, bytecode::member::local{ (std::uint16_t) variable.second },
		    std::forward<T>(destination));

		return pair.first;
	}

	// todo
	present.writer.write<true, bytecode::oc_clone>(bytecode::member::local{ (std::uint16_t) variable.second },
	                                               std::forward<T>(destination));

	return first + 1;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif