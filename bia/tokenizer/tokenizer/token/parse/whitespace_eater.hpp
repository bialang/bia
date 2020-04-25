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
	enum class s
	{
		whitespace,
		comment_start,
		comment_single,
		comment_single_ending,
		comment_multi,
		comment_multi_ending
	};

	auto state = s::whitespace;
	auto eaten = false;
	auto cmd   = false;

	while (true) {
		const auto pos = parameter.input.tellg();
		const auto cp  = parameter.encoder.read(parameter.input);

		if (cp == string::encoding::encoder::eof) {
			eaten = true;
			cmd   = true;

			goto gt_return;
		}

		switch (state) {
		case s::whitespace: {
			switch (cp) {
			case '/': state = s::comment_start; break;
			case '\r':
			case '\n': cmd = true;
			case ' ':
			case '\t':
			case '\v':
			case '\f': eaten = true; break;
			default: goto gt_return;
			}

			break;
		}
		case s::comment_start: {
			switch (cp) {
			case '/': state = s::comment_single; break;
			case '*': state = s::comment_multi; break;
			default: goto gt_return;
			}

			break;
		}
		case s::comment_single: {
			if (cp == '\r' || cp == '\n') {
				cmd   = true;
				state = s::comment_single_ending;
			}

			break;
		}
		case s::comment_single_ending: {
			switch (cp) {
			case '\r':
			case '\n': break;
			default: {
				parameter.input.seekg(pos);

				state = s::whitespace;

				break;
			}
			}

			break;
		}
		case s::comment_multi: {
			if (cp == '*') {
				state = s::comment_multi_ending;
			}

			break;
		}
		case s::comment_multi_ending: {
			if (cp == '/') {
				state = s::whitespace;
			} else if (cp != '*') {
				state = s::comment_multi;
			}

			break;
		}
		}

		continue;

	gt_return:;
		parameter.input.seekg(pos);

		if (!eaten) {
			return { pos, "expected whitespace" };
		} else if (RequireCmd && !cmd) {
			return { pos, "expected cmd whitespace, like a line feed" };
		}

		return {};
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif