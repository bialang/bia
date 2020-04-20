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

	const auto is_control = [last](const tokenizer::token::token* ptr) {
		return ptr != last && static_cast<token::type>(ptr->value.index()) == token::type::control;
	};

	BIA_EXPECTS(first < last && static_cast<token::type>(first->value.index()) == token::type::identifier);

	const auto index = present.variable_manager.index_of(first->value.get<token::identifier>().memory);

	// call
	if (is_control(first + 1)) {
		auto pair            = parameter(present, first + 1, last);
		const auto tmp_index = std::is_same<typename std::decay<T>::type, bytecode::member::tos>::value
		                           ? present.variable_manager.latest_variable()
		                           : present.variable_manager.add_tmp();

		if (index.second) {
			present.writer.write<true, bytecode::oc_invoke>(
			    pair.second, bytecode::member::local{ index.first.id }, bytecode::member::tos{});
		} else {
			const auto id = present.resources.index_of(first->value.get<token::identifier>().memory);

			present.writer.write<true, bytecode::oc_invoke>(pair.second, bytecode::member::global{ id },
			                                                bytecode::member::tos{});
		}

		// chain calls
		while (is_control(pair.first)) {
			pair = parameter(present, pair.first, last);

			present.writer.write<true, bytecode::oc_invoke>(pair.second,
			                                                bytecode::member::local{ tmp_index.id },
			                                                bytecode::member::local{ tmp_index.id });
		}

		// drop tos
		if (!std::is_same<typename std::decay<T>::type, bytecode::member::tos>::value) {
			present.writer.write<true, bytecode::oc_refer>(bytecode::member::tos{},
			                                               std::forward<T>(destination));
			present.writer.write<true, bytecode::oc_drop>(1);
		}

		return pair.first;
	}

	// just clone to destination; local member
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