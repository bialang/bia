#pragma once

#include "biaInterpreter.h"
#include "biaInterpreterTokens.h"
#include "biaInterpreterStringSet.h"
#include "biaInterpreterIdentifiers.h"


namespace bia
{
namespace api
{
namespace grammar
{


inline BiaInterpreter<BGR_RULE_COUNT> & InitializeRules()
{
   static BiaInterpreter<BGR_RULE_COUNT> interpreter;
	BiaInterpreterRule tmp;

	constexpr auto WHITESPACE_OPTIONAL = CharsetToken<Charset_whitespace, FILLER_TOKEN | OPTIONAL_TOKEN>;
	constexpr auto WHITESPACE_REQUIRED = CharsetToken<Charset_whitespace, FILLER_TOKEN, 1>;

	//Root
	tmp.Reset(1, BiaInterpreterRule::F_OR);
	
	tmp.SetToken(1, RulePointerToken<BGR_VARIABLE_DECLARATION, FILLER_TOKEN>);

	interpreter.SetRule(BGR_ROOT, std::move(tmp));

	//Variable declaration
	tmp.Reset(9, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, KeywordToken<Keyword_var, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_REQUIRED)
		.SetToken(3, IdentifierToken<NONE>)
		.SetToken(4, WHITESPACE_OPTIONAL)
		.SetToken(5, KeywordToken<Operator_equals, FILLER_TOKEN>)
		.SetToken(6, WHITESPACE_OPTIONAL)
		.SetToken(7, RulePointerToken<BGR_VALUE, FILLER_TOKEN>)
		.SetToken(8, WHITESPACE_OPTIONAL)
		.SetToken(9, KeywordToken<Operator_semicolon, FILLER_TOKEN>);

	interpreter.SetRule(BGR_VARIABLE_DECLARATION, std::move(tmp));

	//Value raw (must be wrapped becaus of math factor)
	tmp.Reset(7, BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(BV_NUMBER, NumberValueToken<NONE>)
		.SetToken(BV_STRING, StringValueToken<NONE>)
		.SetToken(BV_TRUE, KeywordToken<Keyword_true, NONE>)
		.SetToken(BV_FALSE, KeywordToken<Keyword_false, NONE>)
		.SetToken(BV_NULL, KeywordToken<Keyword_null, NONE>)
		.SetToken(BV_INSTANTIATION, RulePointerToken<BGR_INSTANTIATION, FILLER_TOKEN>)
		.SetToken(BV_MEMBER, RulePointerToken<BGR_MEMBER, FILLER_TOKEN>);

	interpreter.SetRule(BGR_VALUE_RAW, std::move(tmp));

	//Instantiation
	tmp.Reset(5, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, KeywordToken<Keyword_new, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_REQUIRED)
		.SetToken(3, IdentifierToken<NONE>)
		.SetToken(4, WHITESPACE_OPTIONAL)
		.SetToken(5, RulePointerToken<BGR_PARAMETER, FILLER_TOKEN>);

	interpreter.SetRule(BGR_INSTANTIATION, std::move(tmp));

	//Parameter
	tmp.Reset(4, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, KeywordToken<Operator_bracket_open, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>)
		.SetToken(4, KeywordToken<Operator_bracket_close, FILLER_TOKEN>);

	interpreter.SetRule(BGR_PARAMETER, std::move(tmp));

	//Parameter item access
	tmp.Reset(4, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, KeywordToken<Operator_square_bracket_open, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>)
		.SetToken(4, KeywordToken<Operator_square_bracket_close, FILLER_TOKEN>);

	interpreter.SetRule(BGR_PARAMETER_ITEM_ACCESS, std::move(tmp));

	//Parameter list helper 0
	tmp.Reset(4);

	tmp.SetToken(1, RulePointerToken<BGR_VALUE, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_PARAMETER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>)
		.SetToken(4, WHITESPACE_OPTIONAL);

	interpreter.SetRule(BGR_PARAMETER_HELPER_0, std::move(tmp));

	//Parameter list helper 1
	tmp.Reset(3);

	tmp.SetToken(1, KeywordToken<Operator_comma, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_VALUE, FILLER_TOKEN>);

	interpreter.SetRule(BGR_PARAMETER_HELPER_1, std::move(tmp));

	//Math factor
	tmp.Reset(2, BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, RulePointerToken<BGR_MATH_FACTOR_HELPER_0, FILLER_TOKEN>)
		.SetToken(2, RulePointerToken<BGR_VALUE_RAW, FILLER_TOKEN>);

	interpreter.SetRule(BGR_MATH_FACTOR, std::move(tmp));

	//Math factor helper 0
	tmp.Reset(5);

	tmp.SetToken(1, KeywordToken<Operator_bracket_open, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_MATH_EXPRESSION, FILLER_TOKEN>)
		.SetToken(4, WHITESPACE_OPTIONAL)
		.SetToken(5, KeywordToken<Operator_bracket_close, FILLER_TOKEN>);

	interpreter.SetRule(BGR_MATH_FACTOR_HELPER_0, std::move(tmp));

	//Math term
	tmp.Reset(3, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, RulePointerToken<BGR_MATH_FACTOR, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_MATH_TERM_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>);

	interpreter.SetRule(BGR_MATH_TERM, std::move(tmp));

	//Math term helper 0
	tmp.Reset(3);

	tmp.SetToken(1, RulePointerToken<BGR_MATH_TERM_HELPER_1, FILLER_TOKEN>)
		.SetToken(2, WHITESPACE_OPTIONAL)
		.SetToken(3, RulePointerToken<BGR_MATH_FACTOR, FILLER_TOKEN>);

	interpreter.SetRule(BGR_MATH_TERM_HELPER_0, std::move(tmp));

	//Math term helper 1
	tmp.Reset(4, BiaInterpreterRule::F_OR);

	tmp.SetToken(1, KeywordToken<Operator_times, NONE>)
		.SetToken(2, KeywordToken<Operator_divide, NONE>)
		.SetToken(3, KeywordToken<Operator_double_divide, NONE>)
		.SetToken(4, KeywordToken<Operator_modulus, NONE>);

	interpreter.SetRule(BGR_MATH_TERM_HELPER_1, std::move(tmp));

	//Math expression (must be wrapped becaus of math factor)
	tmp.Reset(2, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, RulePointerToken<BGR_MATH_TERM, FILLER_TOKEN>)
		.SetToken(2, RulePointerToken<BGR_MATH_EXPRESSION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>);

	interpreter.SetRule(BGR_MATH_EXPRESSION, std::move(tmp));

	//Math expression helper 0
	tmp.Reset(4);

	tmp.SetToken(1, WHITESPACE_OPTIONAL)
		.SetToken(2, CustomOperatorToken<NONE>)
		.SetToken(3, WHITESPACE_OPTIONAL)
		.SetToken(4, RulePointerToken<BGR_MATH_TERM, FILLER_TOKEN>);

	interpreter.SetRule(BGR_MATH_EXPRESSION_HELPER_0, std::move(tmp));
	
	//Value
	tmp.Reset(1, BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, RulePointerToken<BGR_MATH_EXPRESSION, FILLER_TOKEN>);

	interpreter.SetRule(BGR_VALUE, std::move(tmp));

	//Member
	tmp.Reset(5, BiaInterpreterRule::F_WRAP_UP);

	tmp.SetToken(1, CustomOperatorToken<OPTIONAL_TOKEN>)
		.SetToken(2, IdentifierToken<NONE>)
		.SetToken(3, WHITESPACE_OPTIONAL)
		.SetToken(4, RulePointerToken<BGR_MEMBER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>)
		.SetToken(5, RulePointerToken<BGR_MEMBER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>);

	interpreter.SetRule(BGR_MEMBER, std::move(tmp));

	//Member helper 0
	tmp.Reset(2, BiaInterpreterRule::F_OR);

	tmp.SetToken(1, RulePointerToken<BGR_PARAMETER, FILLER_TOKEN>)
		.SetToken(2, RulePointerToken<BGR_PARAMETER_ITEM_ACCESS, FILLER_TOKEN>);

	interpreter.SetRule(BGR_MEMBER_HELPER_0, std::move(tmp));

	//Member helper 1
	tmp.Reset(6);

	tmp.SetToken(1, WHITESPACE_OPTIONAL)
		.SetToken(2, KeywordToken<Operator_dot, FILLER_TOKEN>)
		.SetToken(3, WHITESPACE_OPTIONAL)
		.SetToken(4, IdentifierToken<NONE>)
		.SetToken(5, WHITESPACE_OPTIONAL)
		.SetToken(6, RulePointerToken<BGR_MEMBER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>);

	interpreter.SetRule(BGR_MEMBER_HELPER_1, std::move(tmp));

	return interpreter;
}

}
}
}