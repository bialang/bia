#pragma once

#include "../config.hpp"
#include "../rule.hpp"

#include <exception/syntax_limitation_exception.hpp>
#include <string/encoding/unicode.hpp>

namespace bia {
namespace tokenizer {
namespace lexer_token {

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION identifier_token(stream::input_stream& input, rule::parameter& param)
{
	using namespace bia::string::encoding;

	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;
	auto buffer            = input.bufferless_read();
	auto begin             = buffer.first;
	code_point cp          = 0;
	std::size_t length     = 1;

	// match first
	if (!param.encoder.next(buffer.first, buffer.second, cp)) {
		return error;
	}

	auto category = category_of(cp);

	// first character cannot be a number
	if (category != CATEGORY::Lu && category != CATEGORY::Ll && category != CATEGORY::Lt && category != CATEGORY::Lo &&
	    category != CATEGORY::Pc && category != CATEGORY::Nl) {
		return error;
	}

	auto nextSucceeded = false;

	while (true) {
		auto tmp = buffer.first;

		// skip and read again
		if (!param.encoder.next(buffer.first, buffer.second, cp)) {
			if (!nextSucceeded) {
				break;
			}

			input.skip(buffer.first - begin);

			buffer        = input.bufferless_read();
			begin         = buffer.first;
			nextSucceeded = false;

			continue;
		}

		nextSucceeded = true;

		// reset
		if (category != CATEGORY::Lu && category != CATEGORY::Ll && category != CATEGORY::Lt &&
		    category != CATEGORY::Lo && category != CATEGORY::Pc && category != CATEGORY::Nl &&
		    category != CATEGORY::Nd && category != CATEGORY::No) {
			buffer.first = tmp;

			break;
		}

		++length;

		// limitation error
		if (length > BIA_TOKENIZER_MAX_IDENTIFIER_LENGTH) {
			BIA_THROW(exception::syntax_limitation_exception, u"identifier length limit exceeded");
		}
	}

	// skip
	input.skip(buffer.first - begin);

	token tk{};

	tk.type = token::TYPE::IDENTIFIER;

	param.bundle.add(tk);

	return success;
}

} // namespace lexer_token
} // namespace tokenizer
} // namespace bia