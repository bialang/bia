#ifndef BIA_TOKENIZER_TOKEN_EXPRESSION_HPP_
#define BIA_TOKENIZER_TOKEN_EXPRESSION_HPP_

#include "any_of.hpp"
#include "identifier.hpp"
#include "member.hpp"
#include "operators.hpp"
#include "token_parameter.hpp"

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details value(token_parameter& tp)
{
	// constant
	const auto old = tp.backup();
	auto t         = any_of(tp, nullptr, "true", "false", "null");

	if (!t.second) {
		return {};
	}

	tp.restore(old);

	// member
	if (auto err = member(tp)) {
		return err;
	}

	return {};
}

inline exception::syntax_details term(token_parameter& token_parameter)
{
	// match optional self operator
	auto t = any_of(token_parameter, nullptr, "not", "~", "-");

	// match value
	return value(token_parameter);
}

inline exception::syntax_details expression(token_parameter& token_parameter)
{
	if (auto err = term(token_parameter)) {
		return err;
	}

	// end of expression
	if (auto err = operators(token_parameter)) {
		return {};
	}

	if (auto err = term(token_parameter)) {
		return {};
	}

	return {};
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif