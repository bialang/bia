#ifndef BIA_TOKENIZER_TOKEN_PARSE_ANY_OF_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_ANY_OF_HPP_

#include "../parameter.hpp"

#include <bia/util/gsl.hpp>
#include <utility>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline std::pair<std::size_t, bool> any_of(parameter& tp, util::czstring token)
{
	while (*token) {
		const auto pos = tp.input.tellg();

		if (tp.encoder.read(tp.input) != *token++) {
			return { 0, false };
		}
	}

	return { 0, true };
}

template<typename... Ts>
inline std::pair<std::size_t, bool> any_of(parameter& tp, util::czstring token, Ts&&... tokens)
{
	const auto old = tp.input.tellg();
	const auto t   = any_of(tp, token);

	if (t.second) {
		return t;
	}

	tp.input.seekg(old);

	const auto o = any_of(tp, std::forward<Ts>(tokens)...);

	return { o.first + 1, o.second };
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
