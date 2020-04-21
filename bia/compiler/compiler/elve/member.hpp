#ifndef BIA_COMPILER_ELVE_MEMBER_HPP_
#define BIA_COMPILER_ELVE_MEMBER_HPP_

#include "parameter.hpp"
#include "present.hpp"

#include <bytecode/writer/instruction.hpp>
#include <exception/implementation_error.hpp>
#include <log/log.hpp>
#include <tokenizer/token/token.hpp>
#include <util/finally.hpp>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename Source, typename Destination>
inline const tokenizer::token::token* member_step(present present,
                                                  util::span<const tokenizer::token::token> tokens,
                                                  Source&& source, Destination&& destination)
{
	using tokenizer::token::token;

	if (tokens.empty()) {
		return tokens.data();
	}

	switch (static_cast<token::type>(tokens.data()->value.index())) {
	case token::type::control: { // function call
		const auto pair = parameter(present, tokens);

		present.writer.write<true, bytecode::oc_invoke>(pair.second, std::forward<Source>(source),
		                                                std::forward<Destination>(destination));

		return pair.first;
	}
	case token::type::identifier: { // member access
		const bytecode::member::resource name{ present.resources.index_of(
			tokens.data()->value.get<token::identifier>().memory) };

		BIA_LOG(INFO, "retrieving member");

		present.writer.write<true, bytecode::oc_get>(std::forward<Source>(source), name,
		                                             std::forward<Destination>(destination));

		return tokens.data() + 1;
	}
	default: return tokens.data();
	}
}

template<typename T>
inline const tokenizer::token::token*
    member(present present, util::span<const tokenizer::token::token> tokens, T&& destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::identifier);

	const auto index =
	    present.variable_manager.index_of(tokens.data()->value.get<token::identifier>().memory);

	tokens = tokens.subspan(1);

	// local source
	if (index.second) {
		BIA_EXPECTS(index.first.scope_id == 0);

		const auto x =
		    member_step(present, tokens, bytecode::member::local{ index.first.id }, bytecode::member::tos{});

		// just one
		if (x == tokens.data()) {
			present.writer.write<true, bytecode::oc_clone>(bytecode::member::local{ index.first.id },
			                                               std::forward<T>(destination));

			return tokens.data();
		}

		tokens = tokens.subspan(x - tokens.data());
	} // global source
	else {
		const auto id = present.resources.index_of(tokens.data()[-1].value.get<token::identifier>().memory);
		const auto x  = member_step(present, tokens, bytecode::member::global{ id }, bytecode::member::tos{});

		// just one
		if (x == tokens.data()) {
			present.writer.write<true, bytecode::oc_clone>(bytecode::member::global{ id },
			                                               std::forward<T>(destination));

			return tokens.data();
		}

		tokens = tokens.subspan(x - tokens.data());
	}

	const bytecode::member::local tmp_source{
		std::is_same<typename std::decay<T>::type, bytecode::member::tos>::value
		    ? present.variable_manager.latest_variable().id
		    : present.variable_manager.add_tmp().id
	};
	const auto finally = util::make_finally([&present, &destination] {
		// remove tmp variable
		if (!std::is_same<typename std::decay<T>::type, bytecode::member::tos>::value) {
			present.variable_manager.remove_tmp();
			present.writer.write<true, bytecode::oc_refer>(bytecode::member::tos{},
			                                               std::forward<T>(destination));
			present.writer.write<true, bytecode::oc_drop>(1);
		}
	});

	// chain
	for (auto i = tokens.begin(); i != tokens.end();) {
		BIA_LOG(INFO, "processing member chain");

		const auto x = member_step(present, { i, tokens.end() }, tmp_source, tmp_source);

		if (x == i) {
			return i;
		}

		i = x;
	}

	return tokens.end();
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif