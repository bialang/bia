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

	const auto index = present.variable_manager.index_of(first->value.get<token::identifier>().memory);

	if (first + 1 < last && static_cast<token::type>(first[1].value.index()) == token::type::control) {
		auto pair = parameter(present, first + 1, last);

		// local member
		if (index.second) {
			BIA_EXPECTS(index.first.scope_id == 0);

			present.writer.write<true, bytecode::oc_invoke>(
			    pair.second, bytecode::member::local{ index.first.id }, std::forward<T>(destination));
		} // global member
		else {
			const auto id = present.resources.index_of(first->value.get<token::identifier>().memory);

			present.writer.write<true, bytecode::oc_invoke>(pair.second, bytecode::member::global{ id },
			                                                std::forward<T>(destination));
		}

		return pair.first;
	}

	// local member
	if (index.second) {
		BIA_EXPECTS(index.first.scope_id == 0);

		present.writer.write<true, bytecode::oc_clone>(bytecode::member::local{ index.first.id },
		                                               std::forward<T>(destination));
	} // global member
	else {
		const auto id = present.resources.index_of(first->value.get<token::identifier>().memory);

		present.writer.write<true, bytecode::oc_clone>(bytecode::member::global{ id },
		                                               std::forward<T>(destination));
	}

	return first + 1;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif