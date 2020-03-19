#ifndef BIA_TOKENIZER_TOKEN_PARSE_EXPRESSION_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_EXPRESSION_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "identifier.hpp"
#include "member.hpp"
#include "operators.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details value(parameter& tp)
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

inline exception::syntax_details term(parameter& parameter)
{
	// match optional self operator
	auto t = any_of(parameter, nullptr, "not", "~", "-");

	// match value
	return value(parameter);
}

inline exception::syntax_details expression(parameter& parameter)
{
	if (auto err = term(parameter)) {
		return err;
	}

	// end of expression
	if (auto err = operators(parameter)) {
		return {};
	}

	if (auto err = term(parameter)) {
		return {};
	}

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif