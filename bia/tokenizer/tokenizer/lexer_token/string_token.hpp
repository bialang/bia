#pragma once

#include "../rule.hpp"

namespace bia {
namespace tokenizer {
namespace lexer_token {

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION string_token(stream::input_stream& input, rule::parameter& param)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

} // namespace lexer_token
} // namespace tokenizer
} // namespace bia