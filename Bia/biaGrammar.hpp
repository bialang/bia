#pragma once

#include "biaInterpreter.hpp"
#include "biaInterpreterTokens.hpp"
#include "biaInterpreterStringSet.hpp"
#include "biaInterpreterIdentifiers.hpp"


namespace bia
{
namespace grammar
{

inline BiaInterpreter<BGR_RULE_COUNT> & InitializeRules()
{
	static BiaInterpreter<BGR_RULE_COUNT> interpreter;

	constexpr auto WHITESPACE_OPTIONAL = CharsetToken<Charset_whitespace, FILLER_TOKEN | OPTIONAL_TOKEN>;
	constexpr auto WHITESPACE_REQUIRED = CharsetToken<Charset_whitespace, FILLER_TOKEN, 1>;

	//Root
	interpreter.SetRule(BGR_ROOT, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_ROOT_HELPER_SINGLE_STATEMENT, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT_HELPER_0, FILLER_TOKEN> }));

	//Root helper 0
	interpreter.SetRule(BGR_ROOT_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Operator_scope_open, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT_HELPER_SINGLE_STATEMENT, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_scope_close, FILLER_TOKEN>
		}));

	//Root helper single statement
	interpreter.SetRule(BGR_ROOT_HELPER_SINGLE_STATEMENT, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_VARIABLE_DECLARATION, FILLER_TOKEN>,
		RulePointerToken<BGR_IF, FILLER_TOKEN>,
		RulePointerToken<BGR_WHILE, FILLER_TOKEN>,
		RulePointerToken<BGR_PRINT, FILLER_TOKEN>
		}));

	//Variable declaration
	interpreter.SetRule(BGR_VARIABLE_DECLARATION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_global, FILLER_TOKEN>,
		WHITESPACE_REQUIRED,
		IdentifierToken<NONE>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VARIABLE_DECLARATION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		KeywordToken<Operator_equals, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_semicolon, FILLER_TOKEN>
		}));

	//Variable declaration helper 0
	interpreter.SetRule(BGR_VARIABLE_DECLARATION_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Operator_comma, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		IdentifierToken<NONE>,
		WHITESPACE_OPTIONAL 
		}));

	//If
	interpreter.SetRule(BGR_IF, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_if, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN>,
		RulePointerToken<BGR_IF_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		RulePointerToken<BGR_IF_HELPER_1, FILLER_TOKEN | OPTIONAL_TOKEN>
		}));

	//If helper 0
	interpreter.SetRule(BGR_IF_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Keyword_else, FILLER_TOKEN>,
		WHITESPACE_REQUIRED,
		KeywordToken<Keyword_if, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN> 
		}));

	//If helper 1
	interpreter.SetRule(BGR_IF_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_else, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN>
		}));

	//Print
	interpreter.SetRule(BGR_PRINT, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Keyword_print, FILLER_TOKEN>,
		WHITESPACE_REQUIRED,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_semicolon, FILLER_TOKEN>
		}));

	//While
	interpreter.SetRule(BGR_WHILE, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_while, FILLER_TOKEN>,
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN>
		}));

	//While helper 0
	interpreter.SetRule(BGR_WHILE_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Keyword_while, NONE>,
		KeywordToken<Keyword_until, NONE>
		}));

	//Value raw (must be wrapped because of math factor)
	interpreter.SetRule(BGR_VALUE_RAW, BiaInterpreterRule(BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP, {
		NumberValueToken<NONE, BV_NUMBER>,
		KeywordToken<Keyword_true, NONE, BV_TRUE>,
		KeywordToken<Keyword_false, NONE, BV_FALSE>,
		RulePointerToken<BGR_MEMBER, FILLER_TOKEN, 0, BV_MEMBER>
		}));

	//Instantiation
	interpreter.SetRule(BGR_INSTANTIATION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_new, FILLER_TOKEN>,
		WHITESPACE_REQUIRED,
		IdentifierToken<NONE>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_PARAMETER, FILLER_TOKEN>
		}));

	//Parameter
	interpreter.SetRule(BGR_PARAMETER, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN>
		}));

	//Parameter item access
	interpreter.SetRule(BGR_PARAMETER_ITEM_ACCESS, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Operator_square_bracket_open, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>,
		KeywordToken<Operator_square_bracket_close, FILLER_TOKEN> 
		}));

	//Parameter list helper 0
	interpreter.SetRule(BGR_PARAMETER_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_PARAMETER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>,
		WHITESPACE_OPTIONAL
		}));

	//Parameter list helper 1
	interpreter.SetRule(BGR_PARAMETER_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Operator_comma, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>
		}));

	//Math factor
	interpreter.SetRule(BGR_MATH_FACTOR, BiaInterpreterRule(BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_VALUE_RAW, FILLER_TOKEN>,
		RulePointerToken<BGR_MATH_FACTOR_HELPER_0, FILLER_TOKEN>
		}));

	//Math factor helper 0
	interpreter.SetRule(BGR_MATH_FACTOR_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN>
		}));

	//Math term
	interpreter.SetRule(BGR_MATH_TERM, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_MATH_FACTOR, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_MATH_TERM_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Math term helper 0
	interpreter.SetRule(BGR_MATH_TERM_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_MATH_TERM_HELPER_1, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_MATH_FACTOR, FILLER_TOKEN>
		}));

	//Math term helper 1
	interpreter.SetRule(BGR_MATH_TERM_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		KeywordToken<Operator_times, NONE>,
		KeywordToken<Operator_divide, NONE>,
		KeywordToken<Operator_double_divide, NONE>,
		KeywordToken<Operator_modulus, NONE>
		}));

	//Math expression (must be wrapped because of math factor)
	interpreter.SetRule(BGR_MATH_EXPRESSION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_MATH_TERM, FILLER_TOKEN>,
		RulePointerToken<BGR_MATH_EXPRESSION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Math expression helper 0
	interpreter.SetRule(BGR_MATH_EXPRESSION_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		WHITESPACE_OPTIONAL,
		CustomOperatorToken<NONE>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_MATH_TERM, FILLER_TOKEN> 
		}));

	//Value
	interpreter.SetRule(BGR_VALUE, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_MATH_EXPRESSION, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN> 
		}));

	//Value helper 0
	interpreter.SetRule(BGR_VALUE_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_VALUE_HELPER_1, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_MATH_EXPRESSION, FILLER_TOKEN>
		}));

	//Value helper 1
	interpreter.SetRule(BGR_VALUE_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		KeywordToken<Operator_logical_and, NONE, BVO_LOGICAL_AND>,
		KeywordToken<Operator_logical_or, NONE, BVO_LOGICAL_OR>
		}));

	//Member
	interpreter.SetRule(BGR_MEMBER, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		CustomOperatorToken<OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MEMBER_HELPER_2, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_MEMBER_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		RulePointerToken<BGR_MEMBER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Member helper 0
	interpreter.SetRule(BGR_MEMBER_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_PARAMETER, FILLER_TOKEN>,
		RulePointerToken<BGR_PARAMETER_ITEM_ACCESS, FILLER_TOKEN>
		}));

	//Member helper 1
	interpreter.SetRule(BGR_MEMBER_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		WHITESPACE_OPTIONAL,
		KeywordToken<Operator_dot, FILLER_TOKEN>,
		WHITESPACE_OPTIONAL,
		IdentifierToken<NONE>,
		WHITESPACE_OPTIONAL,
		RulePointerToken<BGR_MEMBER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>
		}));

	//Member helper 2
	interpreter.SetRule(BGR_MEMBER_HELPER_2, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_INSTANTIATION, FILLER_TOKEN, 0, BM_INSTANTIATION>,
		StringValueToken<NONE, BM_STRING>,
		IdentifierToken<NONE, BM_IDENTIFIER>
		}));

	return interpreter;
}

}
}