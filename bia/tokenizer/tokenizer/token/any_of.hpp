#ifndef BIA_TOKENIZER_TOKEN_ANY_OF_HPP_
#define BIA_TOKENIZER_TOKEN_ANY_OF_HPP_

#include "token_parameter.hpp"

#include <exception/syntax_error.hpp>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace tokenizer {
namespace token {

inline std::pair<std::size_t, exception::syntax_details>
    any_of(token_parameter& token_parameter, util::czstring err_message, util::czstring token)
{
	while (*token) {
		auto pos = token_parameter.input.tellg();

		if (token_parameter.encoder.read(token_parameter.input) != *token) {
			return { 0, { pos, err_message } };
		}
	}

	return { 0, {} };
}

template<typename... Ts>
inline std::pair<std::size_t, exception::syntax_details>
    any_of(token_parameter& token_parameter, util::czstring err_message, util::czstring token, Ts&&... tokens)
{
	auto t = any_of(token_parameter, err_message, token);

	if (!t.second) {
		return t;
	}

	return any_of(token_parameter, err_message, std::forward<Ts>(tokens)...);
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif