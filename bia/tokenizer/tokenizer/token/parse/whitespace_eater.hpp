#ifndef BIA_TOKENIZER_TOKEN_PARSE_WHITESPACE_EATER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_WHITESPACE_EATER_HPP_

#include "../parameter.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

/**
 * Eats all the whitespaces this function encounters.
 *
 * @note this function always consumes all whitespaces, even if an error is returned
 *
 * @param[in,out] parameter the required parameters
 * @returns an error if no whitespaces are found
 * @tparam RequireCmd if `true`, this function fails if no whitespace cmd_end character is found
 */
template<bool RequireCmd = false>
inline exception::syntax_details eat_whitespaces(parameter& parameter)
{
	auto eaten = false;
	auto cmd   = false;

	while (true) {
		const auto pos = parameter.input.tellg();

		switch (parameter.encoder.read(parameter.input)) {
		case '\r':
		case '\n': cmd = true;
		case ' ':
		case '\t':
		case '\v':
		case '\f': eaten = true; break;
		case string::encoding::encoder::eof: cmd = true; eaten = true;
		default: {
			parameter.input.seekg(pos);

			if (!eaten) {
				return { pos, "expected whitespace" };
			} else if (RequireCmd && !cmd) {
				return { pos, "expected cmd whitespace, like a line feed" };
			}

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