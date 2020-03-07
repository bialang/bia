#ifndef BIA_TOKENIZER_TOKEN_OPERATORS_HPP_
#define BIA_TOKENIZER_TOKEN_OPERATORS_HPP_

#include "any_of.hpp"
#include "token_parameter.hpp"

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details operators(token_parameter& token_parameter)
{
	auto t = any_of(token_parameter, "invalid operator", "*", "/", "%", "+", "-", "==", "!=", "<", ">",
	                "<=", ">=", "and", "or", "&", "|", "^");

	return t.second;
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif