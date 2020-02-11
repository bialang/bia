#ifndef BIA_TOKENIZER_TOKEN_WHITESPACE_EATER_HPP_
#define BIA_TOKENIZER_TOKEN_WHITESPACE_EATER_HPP_

#include "token_parameter.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details eat_whitespaces(token_parameter& token_parameter)
{
	auto eaten = false;

	while (true) {
		auto pos = token_parameter.input.tellg();
		auto cp  = token_parameter.encoder.read(token_paramter.input);

		switch (cp) {
		case ' ':
		case '\t': {
			eaten = true;

			break;
		}
		default: {
			input.seekg(pos);

			// expected whitespaces
			if (!eaten) {
				return { pos, "expected whitespaces" };
			}

			// no error
			return {};
		}
		}
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif