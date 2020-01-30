#pragma once

#include "../rule.hpp"

#include <string/encoding/iterator.hpp>
#include <util/iterator_equals.hpp>

namespace bia {
namespace tokenizer {

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION dot_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error       = TOKEN_ACTION::FAILED;
	constexpr auto success     = TOKEN_ACTION::SUCCEEDED;
	constexpr auto multiply    = "*";
	constexpr auto power       = "**";
	constexpr auto divide      = "/";
	constexpr auto true_divide = "//";
	constexpr auto modulus     = "%";

	auto buffer = input.bufferless_read();
	auto result =
	    util::iterator_starts_with(string::encoding::input_iterator(&parameter.encoder, buffer.first, buffer.second),
	                               string::encoding::input_iterator(), power, power + 2, true_divide, true_divide + 2,
	                               multiply, multiply + 1, divide, divide + 1, modulus, modulus + 1);

	if (result.first != 5) {
		token tk{};

		tk.type = token::TYPE::OPERATOR;
		tk.content
		    .

		    parameter.bundle.add(tk);
		input.skip(result.second.cursor());

		return success;
	}

	return error;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION custom_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION weak_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION self_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION condition_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	switch (parameter.encoder.next(buffer.first, buffer.second)) {
	case '<':
	case '>':
	case '=':
	case '!':
	}

	return success;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION bit_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

template<rule::flag_type Flags = rule::F_NONE>
inline TOKEN_ACTION condition_chain_operator_token(stream::input_stream& input, rule_parameter& parameter)
{
	constexpr auto error   = TOKEN_ACTION::FAILED;
	constexpr auto success = TOKEN_ACTION::SUCCEEDED;

	auto buffer = input.bufferless_read();

	return success;
}

} // namespace tokenizer
} // namespace bia