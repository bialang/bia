#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::spacer(Parameter& param)
{
	enum class state
	{
		whitespace,
		comment_start,
		comment_single,
		comment_single_ending,
		comment_multi,
		comment_multi_ending
	};

	auto state          = state::whitespace;
	auto seperator      = false;
	auto last_state     = param.reader.backup();
	const auto ranger = param.begin_range();

	while (true) {
		auto old      = param.reader.backup();
		const auto cp = param.reader.read();
		if (cp == string::encoding::Encoder::eof) {
			seperator = true;
			goto gt_return;
		}

		switch (state) {
		case state::whitespace: {
			switch (cp) {
			case '/': {
				seperator = true;
				state     = state::comment_start;
				break;
			}
			case '\r':
			case '\n':
			case ' ':
			case '\t':
			case '\v':
			case '\f': seperator = true; break;
			case '+':
			case '-':
			case '*':
			case '%':
			case '=':
			case '{':
			case '}':
			case '(':
			case ')':
			case ':':
			case ',':
			case '.': seperator = true;
			default: goto gt_return;
			}
			break;
		}
		case state::comment_start: {
			switch (cp) {
			case '/': state = state::comment_single; break;
			case '*': state = state::comment_multi; break;
			default: old = last_state; goto gt_return; // rollback one character more
			}
			break;
		}
		case state::comment_single: {
			if (cp == '\r' || cp == '\n') {
				state = state::comment_single_ending;
			}
			break;
		}
		case state::comment_single_ending: {
			switch (cp) {
			case '\r':
			case '\n': break;
			default: {
				param.reader.restore(old);
				state = state::whitespace;
				break;
			}
			}
			break;
		}
		case state::comment_multi: {
			if (cp == '*') {
				state = state::comment_multi_ending;
			}
			break;
		}
		case state::comment_multi_ending: {
			if (cp == '/') {
				state = state::whitespace;
			} else if (cp != '*') {
				state = state::comment_multi;
			}
			break;
		}
		}

		// consume
		last_state = old;
		continue;

	gt_return:;
		param.reader.restore(old);
		if (seperator) {
			return {};
		}
		return param.make_error(error::Code::expected_seperator, ranger.range());
	}
}
