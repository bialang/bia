#ifndef BIA_COMPILER_ELVE_PARAMETER_HPP_
#define BIA_COMPILER_ELVE_PARAMETER_HPP_

#include "present.hpp"

#include <bia/log/log.hpp>
#include <cstdint>
#include <limits>
#include <map>
#include <tuple>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

template<typename Destination>
tokens_type expression(present present, tokens_type tokens, Destination&& destination);

inline std::tuple<tokens_type, std::uint8_t, std::uint8_t> parameter(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::control);

	BIA_LOG(INFO, "processing parameters {} - {}", static_cast<const void*>(first),
	        static_cast<const void*>(last));

	std::map<resource::view, tokens_type> kwargs;
	std::uint8_t count = 0;

	while (true) {
		BIA_EXPECTS(!tokens.empty() &&
		            static_cast<token::type>(tokens.data()->value.index()) == token::type::control);

		const auto offset = tokens.data()->value.get<token::control>().value;

		if (offset <= 1) {
			tokens = tokens.subspan(offset + 1);

			break;
		}

		const auto expr = tokens.subspan(1, offset - 1);

		// limit is 254
		if (++count == std::numeric_limits<std::uint8_t>::max()) {
			throw;
		}
		// kwarg
		if (static_cast<token::type>(expr.data()->value.index()) == token::type::control) {
			const auto& name = expr.data()[1].value.get<token::identifier>().memory;

			// redeclaration of same name
			if (kwargs.find(name) != kwargs.end()) {
				throw;
			}

			kwargs.insert({ name, expr.subspan(2) });
		} else {
			expression(present, expr, bytecode::member::tos{});
			present.variables.add_tmp();
		}

		tokens = tokens.subspan(expr.end());
	}

	// push kwargs
	for (const auto& i : kwargs) {
		expression(present, i.second, bytecode::member::tos{});

		present.variables.add_tmp();
		present.writer.write<true, bytecode::oc_name>(
		    bytecode::member::resource{ present.resources.index_of(i.first) });
	}

	return { tokens, count, static_cast<std::uint8_t>(kwargs.size()) };
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
