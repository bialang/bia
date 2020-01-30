#pragma once

#include "identifier_token.hpp"

namespace bia {
namespace tokenizer {
namespace lexer_token {

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION calling_token(stream::input_stream& input, rule::parameter& param)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;
	auto succeeded         = false;

	while (identifier_token(input, param) == TOKEN_ACTION::SUCCEEDED) {
		succeeded = true;

		auto buffer                     = input.bufferless_read();
		string::encoding::code_point cp = 0;

		if (!param.encoder.next(buffer.first, buffer.second, cp) || cp != '.') {
			break;
		}
	}

	return succeeded ? success : error;
}

} // namespace lexer_token
} // namespace tokenizer
} // namespace bia