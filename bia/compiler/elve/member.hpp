#ifndef BIA_COMPILER_ELVE_MEMBER_HPP_
#define BIA_COMPILER_ELVE_MEMBER_HPP_

#include "parameter.hpp"
#include "present.hpp"

#include <bia/bytecode/writer/instruction.hpp>
#include <bia/exception/implementation_error.hpp>
#include <bia/log/log.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/gsl.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename Source, typename Destination>
inline tokens_type member_step(present present, tokens_type tokens, Source&& source,
                               Destination&& destination)
{
	using tokenizer::token::token;

	if (tokens.empty()) {
		return tokens;
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

		return tokens.subspan(1);
	}
	default: return tokens;
	}
}

template<typename T>
inline tokens_type member(present present, tokens_type tokens, T&& destination)
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
		if (tokens.size() == x.size()) {
			present.writer.write<true, bytecode::oc_clone>(bytecode::member::local{ index.first.id },
			                                               std::forward<T>(destination));

			return tokens;
		}

		tokens = x;
	} // global source
	else {
		const auto id = present.resources.index_of(tokens.data()[-1].value.get<token::identifier>().memory);
		const auto x  = member_step(present, tokens, bytecode::member::global{ id }, bytecode::member::tos{});

		// just one
		if (tokens.size() == x.size()) {
			present.writer.write<true, bytecode::oc_clone>(bytecode::member::global{ id },
			                                               std::forward<T>(destination));

			return tokens;
		}

		tokens = x;
	}

	const bytecode::member::local tmp_source{ present.variable_manager.add_tmp().id };
	const auto finally = util::make_finally([&present, &destination] {
		// remove tmp variable
		present.variable_manager.remove_tmp();
		present.writer.write<true, bytecode::oc_refer>(bytecode::member::tos{}, std::forward<T>(destination));
		present.writer.write<true, bytecode::oc_drop>(1);
	});

	// chain
	while (!tokens.empty()) {
		BIA_LOG(INFO, "processing member chain");

		const auto x = member_step(present, tokens, tmp_source, tmp_source);

		if (tokens.size() == x.size()) {
			return tokens;
		}

		tokens = x;
	}

	return tokens.subspan(tokens.end());
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
