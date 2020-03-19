#ifndef BIA_TOKENIZER_TOKEN_PARSE_WHITESPACE_EATER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_WHITESPACE_EATER_HPP_

#include "../parameter.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details eat_whitespaces(parameter& tp)
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

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif