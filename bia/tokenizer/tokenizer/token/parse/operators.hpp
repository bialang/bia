#ifndef BIA_TOKENIZER_TOKEN_PARSE_OPERATORS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_OPERATORS_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details operators(parameter& parameter)
{
	auto t = any_of(parameter, "invalid operator", "*", "/", "%", "+", "-", "==", "!=", "<", ">",
	                "<=", ">=", "and", "or", "&", "|", "^");

	return t.second;
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif