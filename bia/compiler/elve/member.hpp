#ifndef BIA_COMPILER_ELVE_MEMBER_HPP_
#define BIA_COMPILER_ELVE_MEMBER_HPP_

#include "helpers.hpp"

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
inline tokens_type member_call(present present, tokens_type tokens, Source source, Destination destination)
{
	using tokenizer::token::token;

	if (!bytecode::member::is_same(source, destination)) {
		present.writer.write<true, bytecode::oc_refer>(source, destination);
	}

	if (tokens.empty() || static_cast<token::type>(tokens.data()->value.index()) != token::type::control) {
		return tokens;
	}

	while (true) {
		present.writer.write<true, bytecode::oc_prep_call>();

		tokens = parameter(present, tokens);

		present.writer.write<true, bytecode::oc_invoke>(destination, destination);

		if (tokens.empty() ||
		    static_cast<token::type>(tokens.data()->value.index()) != token::type::control) {
			break;
		}
	}

	return tokens;
}

template<typename Destination>
inline tokens_type member(present present, tokens_type tokens, Destination destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::identifier);

	const auto& identifier = tokens.data()->value.get<token::identifier>();

	if (identifier.is_builtin) {
		return member_call(present, tokens.subspan(1), identifier.builtin, destination);
	}

	const auto index = present.variables.find(identifier.memory);

	// local source
	if (index.second) {
		return member_call(present, tokens.subspan(1), bytecode::member::local{ index.first }, destination);
	}

	// global source
	return member_call(present, tokens.subspan(1),
	                   bytecode::member::global{ present.resources.index_of(identifier.memory) },
	                   destination);
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
