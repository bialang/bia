#pragma once

#include "../rule.hpp"

#include <string/encoding/iterator.hpp>
#include <util/iterator_equals.hpp>
#include <util/cstring_iterator.hpp>
#include <iostream>
#include <exception/throwable.hpp>
namespace bia {
namespace tokenizer {
namespace lexer_token {

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION bool_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error	 = TOKEN_ACTION::FAILED;
	constexpr auto success   = TOKEN_ACTION::SUCCEEDED;
		auto buffer		 = input.bufferless_read();
		const auto begin = buffer.first;
	try {
		auto result		 = util::iterator_starts_with(
			 string::encoding::input_iterator(&parameter.encoder, buffer.first, buffer.second),
			 util::cstring_iterator<char>("true"), util::cstring_iterator<char>("false"));

		if (result.first != 2) {
			token tk{};

			tk.type			   = token::TYPE::KEYWORD;
			tk.content.keyword = result.first ? KEYWORD::FALSE : KEYWORD::TRUE;

			parameter.bundle.add(tk);
			input.skip(result.second.cursor() - begin);

			return success;
		}
	}catch(const bia::exception::throwable& e) {
		std::cout << e.debug_message();

		throw;	
	}

	return error;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION constant_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

} // namespace lexer_token
} // namespace tokenizer
} // namespace bia