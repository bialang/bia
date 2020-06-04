#ifndef BIA_TOKENIZER_TOKEN_PARSE_OPERATORS_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_OPERATORS_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"

#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details operators(parameter& parameter)
{
	constexpr operator_ ops[] = { operator_::exponentation,
		                          operator_::multiplication,
		                          operator_::division,
		                          operator_::remainder,
		                          operator_::addition,
		                          operator_::subtraction,
		                          operator_::equal,
		                          operator_::not_equal,
		                          operator_::less_equal,
		                          operator_::greater_equal,
		                          operator_::less,
		                          operator_::greater,
		                          operator_::logical_and,
		                          operator_::logical_and,
		                          operator_::logical_or,
		                          operator_::logical_or,
		                          operator_::in,
		                          operator_::bitwise_and,
		                          operator_::bitwise_or,
		                          operator_::bitwise_xor };
	const auto x              = any_of(parameter, "invalid operator", "**", "*", "/", "%", "+", "-",
                          "==", "!=", "<=", ">=", "<", ">", "and", "&&", "or", "||", "in", "&", "|", "^");

	if (x.second) {
		return x.second;
	}

	BIA_EXPECTS(x.first < sizeof(ops) / sizeof(operator_));

	parameter.bundle.add({ static_cast<operator_>(ops[x.first]) });

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
