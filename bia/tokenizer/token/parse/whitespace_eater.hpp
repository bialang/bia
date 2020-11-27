#ifndef BIA_TOKENIZER_TOKEN_PARSE_WHITESPACE_EATER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_WHITESPACE_EATER_HPP_

#include "../error_info.hpp"
#include "../parameter.hpp"

#include <bia/error/exception.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

/**
 * Eats all the whitespaces this function encounters.
 *
 * @note this function always consumes all whitespaces, even if an error is returned
 *
 * @param[in,out] param the required parameters
 * @returns an error if no whitespaces are found
 * @tparam RequireCmd if `true`, this function fails if no whitespace cmd_end character is found
 */
template<bool RequireCmd = false>
inline error_info eat_whitespaces(parameter& param)
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

	auto state    = s::whitespace;
	auto eaten    = false;
	auto cmd      = false;
	auto last_pos = param.input.tellg();

	while (true) {
		auto pos      = param.input.tellg();
		const auto cp = param.encoder.read(param.input);
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
			default: pos = last_pos; goto gt_return; // rollback one character more
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
				param.input.seekg(pos);
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

		// consume
		last_pos = pos;
		continue;

	gt_return:;
		param.input.seekg(pos);
		if (!eaten || (RequireCmd && !cmd)) {
			return param.make_error(error::code::expected_whitespace, -1);
		}
		return {};
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
