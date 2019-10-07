#pragma once

#include "../rule.hpp"

namespace bia {
namespace tokenizer {

template<typename Keyword, rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION keyword_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();
	auto begin  = Keyword::name();
	auto end	= begin + Keyword::length();

	while (begin < end) {
		// cannot yield eof, because bufferless_read() has to return at least BIA_MIN_TOKENIZER_BUFFER
		if (parameter.encoder.next(buffer.first, buffer.second) != *begin++) {
			return error;
		}
	}

	input.skip(buffer.first);

	return success;
}

} // namespace tokenizer
} // namespace bia