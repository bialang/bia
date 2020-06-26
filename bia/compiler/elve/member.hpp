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
inline tokens_type member_call(present present, tokens_type tokens, Source source, Destination destination)
{
	using tokenizer::token::token;

	if (tokens.empty() || static_cast<token::type>(tokens.data()->value.index()) != token::type::control) {
		present.writer.write<true, bytecode::oc_refer>(source, destination);

		return tokens;
	}

	present.writer.write<true, bytecode::oc_refer>(source, bytecode::member::tos{});

	bytecode::member::local tmp{ present.variables.add_tmp().id };

	while (true) {
		const auto tuple = parameter(present, tokens);

		present.writer.write<true, bytecode::oc_invoke>(std::get<1>(tuple), std::get<2>(tuple), tmp, tmp);

		for (auto i = std::get<1>(tuple); i--;) {
			present.variables.remove_tmp();
		}

		tokens = std::get<0>(tuple);

		if (tokens.empty() ||
		    static_cast<token::type>(tokens.data()->value.index()) != token::type::control) {
			break;
		}
	}

	present.variables.remove_tmp();

	if (!std::is_same<Destination, bytecode::member::tos>::value) {
		present.writer.write<true, bytecode::oc_refer>(tmp, destination);
		present.writer.write<true, bytecode::oc_drop>(1);
	}

	return tokens;
}

template<typename Destination>
inline tokens_type member(present present, tokens_type tokens, Destination destination)
{
	using tokenizer::token::token;

	BIA_EXPECTS(!tokens.empty());

	switch (static_cast<token::type>(tokens.data()->value.index())) {
	case token::type::identifier: {
		const auto index = present.variables.index_of(tokens.data()->value.get<token::identifier>().memory);

		// local source
		if (index.second) {
			BIA_EXPECTS(index.first.scope_id == 0);

			return member_call(present, tokens.subspan(1), bytecode::member::local{ index.first.id },
			                   destination);
		} // global source
		else {
			return member_call(present, tokens.subspan(1), bytecode::member::global{ index.first.id },
			                   destination);
		}
	}
	case token::type::builtin:
		return member_call(present, tokens.subspan(1), tokens.data()->value.get<bytecode::member::builtin>(),
		                   destination);
	default: BIA_IMPLEMENTATION_ERROR("invalid token type");
	}
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
