#ifndef BIA_TOKENIZER_TOKEN_EXPRESSION_HPP_
#define BIA_TOKENIZER_TOKEN_EXPRESSION_HPP_

#include "any_of.hpp"
#include "token_parameter.hpp"

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details value(token_parameter& token_parameter)
{
	// constant
	auto t = any_of(token_parameter, nullptr, "true", "false", "null");

	if (!t.second) {
		
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
	return {};
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif