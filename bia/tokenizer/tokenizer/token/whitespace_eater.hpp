#ifndef BIA_TOKENIZER_TOKEN_WHITESPACE_EATER_HPP_
#define BIA_TOKENIZER_TOKEN_WHITESPACE_EATER_HPP_

#include "token_parameter.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details eat_whitespaces(token_parameter& tp)
{
	auto eaten = false;

	while (true) {
		const auto pos = tp.input.tellg();
		const auto cp  = tp.encoder.read(tp.input);

		switch (cp) {
		case ' ':
		case '\t': {
			eaten = true;

			break;
		}
		default: {
			tp.input.seekg(pos);

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