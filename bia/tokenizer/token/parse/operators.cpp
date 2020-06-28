#include "any_of.hpp"
#include "tokens.hpp"

#include <bia/util/gsl.hpp>

bia::exception::syntax_details bia::tokenizer::token::parse::operators(parameter& parameter)
{
	constexpr operator_ ops[] = { operator_::member_access,
		                          operator_::exponentation,
		                          operator_::multiplication,
		                          operator_::division,
		                          operator_::remainder,
		                          operator_::addition,
		                          operator_::subtraction,
		                          operator_::equal,
		                          operator_::not_equal,
		                          operator_::three_way_comparison,
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
	const auto x =
	    any_of(parameter, "invalid operator", ".", "**", "*", "/", "%", "+", "-", "==", "!=", "<=>",
	           "<=", ">=", "<", ">", "and", "&&", "or", "||", "in", "&", "|", "^");

	if (x.second) {
		return x.second;
	}

	BIA_EXPECTS(x.first < sizeof(ops) / sizeof(operator_));

	parameter.bundle.add({ static_cast<operator_>(ops[x.first]) });

	return {};
}
