#pragma once

#include "../rule.hpp"

namespace bia {
namespace tokenizer {
namespace lexer_token {

inline TOKEN_ACTION whitespace_consumer(stream::input_stream& input, rule::parameter& param)
{
	enum class STATE
	{
		START,
		END,
		COMMENT_0,
		COMMENT_1,
		COMMENT_2,
		COMMENT_CONTENT
	};

	STATE state                     = STATE::START;
	auto buffer                     = input.bufferless_read();
	string::encoding::code_point cp = 0;

	while (true) {
		// failed to read
		if (!param.encoder.next(buffer.first, buffer.second, cp)) {
		}

		// automaton see docs
		switch (state) {
		case STATE::START: {
			if (cp == '#') {
				state = STATE::COMMENT_0;
			}

			break;
		}
		case STATE::END: {
			if (cp == '#') {
				state = STATE::COMMENT_0;
			}

			break;
		}
		case STATE::COMMENT_0: {
			if (cp == '*') {
				state = STATE::COMMENT_1;
			} else if (cp == '#' || cp == '\n') {
				state = STATE::END;
			} else {
				state = STATE::COMMENT_CONTENT;
			}

			break;
		}
		case STATE::COMMENT_1: {
			if (cp == '*') {
				state = STATE::COMMENT_2;
			}

			break;
		}
		case STATE::COMMENT_2: {
			if (cp == '#') {
				state = STATE::END;
			} else if (cp != '*') {
				state = STATE::COMMENT_1;
			}

			break;
		}
		case STATE::COMMENT_CONTENT: {
			if (cp == '#' || cp == '\n') {
				state = STATE::END;
			}

			break;
		}
		}
	}
}

} // namespace lexer_token
} // namespace tokenizer
} // namespace bia