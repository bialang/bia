#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::spacer(parameter& param)
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

	auto state     = state::whitespace;
	auto seperator = false;
	auto last_pos  = param.input.tellg();

	while (true) {
		auto pos      = param.input.tellg();
		const auto cp = param.encoder.read(param.input);
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
			default: goto gt_return;
			}
			break;
		}
		case state::comment_start: {
			switch (cp) {
			case '/': state = state::comment_single; break;
			case '*': state = state::comment_multi; break;
			default: pos = last_pos; goto gt_return; // rollback one character more
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
				param.input.seekg(pos);
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
		last_pos = pos;
		continue;

	gt_return:;
		param.input.seekg(pos);
		if (seperator) {
			return {};
		}
		return param.make_error(error::Code::expected_seperator, -1);
	}
}
