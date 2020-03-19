#ifndef BIA_TOKENIZER_TOKEN_PARSE_ANY_OF_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_ANY_OF_HPP_

#include "../parameter.hpp"

#include <exception/syntax_error.hpp>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline std::pair<std::size_t, exception::syntax_details>
    any_of(parameter& tp, util::czstring err_message, util::czstring token)
{
	while (*token) {
		const auto pos = tp.input.tellg();

		if (tp.encoder.read(tp.input) != *token++) {
			return { 0, { pos, err_message } };
		}
	}

	return { 0, {} };
}

template<typename... Ts>
inline std::pair<std::size_t, exception::syntax_details>
    any_of(parameter& tp, util::czstring err_message, util::czstring token, Ts&&... tokens)
{
	const auto old = tp.input.tellg();
	const auto t   = any_of(tp, err_message, token);

	if (!t.second) {
		return t;
	}

	tp.input.seekg(old);

	return any_of(tp, err_message, std::forward<Ts>(tokens)...);
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif