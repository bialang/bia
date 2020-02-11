#ifndef BIA_TOKENIZER_TOKEN_KEYWORD_HPP_
#define BIA_TOKENIZER_TOKEN_KEYWORD_HPP_

#include "token_parameter.hpp"

#include <exception/syntax_error.hpp>
#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details keyword(util::czstring token, token_parameter& token_parameter)
{
	while (*keyword) {
		auto pos = input.tellg();

		if (encoder.read(input) != *keyword) {
			return { pos, "invalid keyword" };
		}
	}

	return {};
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif