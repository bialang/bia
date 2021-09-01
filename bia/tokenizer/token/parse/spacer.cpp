#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::spacer(Parameter& param)
{
	enum class State
	{
		whitespace,
		comment_start,
		comment_single,
		comment_single_ending,
		comment_multi,
		comment_multi_ending
	};

	State state       = State::whitespace;
	bool seperator    = false;
	auto last_state   = param.reader.backup();
	const auto ranger = param.begin_range();

	while (true) {
		auto old      = param.reader.backup();
		const auto cp = param.reader.read();
		if (cp == string::encoding::Encoder::eof) {
			seperator = true;
			goto gt_return;
		}

		switch (state) {
		case State::whitespace: {
			switch (cp) {
			case '/': {
				seperator = true;
				state     = State::comment_start;
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
		case State::comment_start: {
			switch (cp) {
			case '/': state = State::comment_single; break;
			case '*': state = State::comment_multi; break;
			default: old = last_state; goto gt_return; // rollback one character more
			}
			break;
		}
		case State::comment_single: {
			if (cp == '\r' || cp == '\n') {
				state = State::comment_single_ending;
			}
			break;
		}
		case State::comment_single_ending: {
			switch (cp) {
			case '\r':
			case '\n': break;
			default: {
				param.reader.restore(old);
				state = State::whitespace;
				break;
			}
			}
			break;
		}
		case State::comment_multi: {
			if (cp == '*') {
				state = State::comment_multi_ending;
			}
			break;
		}
		case State::comment_multi_ending: {
			if (cp == '/') {
				state = State::whitespace;
			} else if (cp != '*') {
				state = State::comment_multi;
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

bool parse::is_spacing_character(string::encoding::code_point_type cp) noexcept
{
	switch (cp) {
	case '/':
	case '\r':
	case '\n':
	case ' ':
	case '\t':
	case '\v':
	case '\f':
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
	case '.': return true;
	default: return false;
	}
}
