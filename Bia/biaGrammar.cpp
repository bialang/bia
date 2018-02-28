#include "biaGrammar.hpp"


namespace bia
{
namespace grammar
{

BiaInterpreter<BGR_RULE_COUNT> BiaGrammar::m_interpreter(BiaGrammar::InitializeRules);


const BiaInterpreter<BGR_RULE_COUNT>& BiaGrammar::GetGrammar()
{
	return m_interpreter;
}

void BiaGrammar::InitializeRules()
{
	//constexpr auto WHITESPACE_OPTIONAL = CharsetToken<Charset_whitespace, FILLER_TOKEN | OPTIONAL_TOKEN>;
	//constexpr auto WHITESPACE_REQUIRED = CharsetToken<Charset_whitespace, FILLER_TOKEN, 1>;

	//Root
	m_interpreter.SetRule(BGR_ROOT, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_ROOT_HELPER_1, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT_HELPER_0, FILLER_TOKEN> }));

	//Root helper 0
	m_interpreter.SetRule(BGR_ROOT_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Operator_scope_open, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_scope_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Root helper 1
	m_interpreter.SetRule(BGR_ROOT_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_VARIABLE_DECLARATION, FILLER_TOKEN>,
		RulePointerToken<BGR_IF, FILLER_TOKEN>,
		RulePointerToken<BGR_PRE_TEST_LOOP, FILLER_TOKEN>,
		RulePointerToken<BGR_PRINT, FILLER_TOKEN>,
		RulePointerToken<BGR_ROOT_HELPER_2, FILLER_TOKEN>
		}));

	//Root helper 2
	m_interpreter.SetRule(BGR_ROOT_HELPER_2, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		KeywordToken<Operator_semicolon, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Variable declaration
	m_interpreter.SetRule(BGR_VARIABLE_DECLARATION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_global, FILLER_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_TOKEN>,
		RulePointerToken<BGR_VARIABLE_DECLARATION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		KeywordToken<Operator_equals, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_semicolon, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Variable declaration helper 0
	m_interpreter.SetRule(BGR_VARIABLE_DECLARATION_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Operator_comma, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//If
	m_interpreter.SetRule(BGR_IF, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_if, FILLER_TOKEN>,
		KeywordToken<Operator_bracket_open, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_IF_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		RulePointerToken<BGR_IF_HELPER_1, FILLER_TOKEN | OPTIONAL_TOKEN>
		}));

	//If helper 0
	m_interpreter.SetRule(BGR_IF_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Keyword_else, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Keyword_if, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		KeywordToken<Operator_bracket_open, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//If helper 1
	m_interpreter.SetRule(BGR_IF_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_else, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Print
	m_interpreter.SetRule(BGR_PRINT, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_print, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		KeywordToken<Operator_semicolon, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Pre test loop
	m_interpreter.SetRule(BGR_PRE_TEST_LOOP, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_PRE_TEST_LOOP_HELPER_0, FILLER_TOKEN>,
		KeywordToken<Operator_bracket_open, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_ROOT, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Pre test loop helper 0
	m_interpreter.SetRule(BGR_PRE_TEST_LOOP_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		KeywordToken<Keyword_while, NONE, LT_WHILE>,
		KeywordToken<Keyword_until, NONE, LT_UNTIL>
		}));

	//Value raw (must be wrapped because of math factor)
	m_interpreter.SetRule(BGR_VALUE_RAW, BiaInterpreterRule(BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP, {
		NumberValueToken<NONE, BV_NUMBER>,
		KeywordToken<Keyword_true, NONE, BV_TRUE>,
		KeywordToken<Keyword_false, NONE, BV_FALSE>,
		RulePointerToken<BGR_MEMBER, FILLER_TOKEN, 0, BV_MEMBER>
		}));

	//Instantiation
	m_interpreter.SetRule(BGR_INSTANTIATION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Keyword_new, FILLER_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_TOKEN>,
		RulePointerToken<BGR_PARAMETER, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Parameter
	m_interpreter.SetRule(BGR_PARAMETER, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		RulePointerToken<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Parameter item access
	m_interpreter.SetRule(BGR_PARAMETER_ITEM_ACCESS, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		KeywordToken<Operator_square_bracket_open, FILLER_TOKEN>,
		RulePointerToken<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_square_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Parameter list helper 0
	m_interpreter.SetRule(BGR_PARAMETER_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_VALUE, FILLER_TOKEN>,
		RulePointerToken<BGR_PARAMETER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Parameter list helper 1
	m_interpreter.SetRule(BGR_PARAMETER_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Operator_comma, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Math factor
	m_interpreter.SetRule(BGR_MATH_FACTOR, BiaInterpreterRule(BiaInterpreterRule::F_OR | BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_VALUE_RAW, FILLER_TOKEN>,
		RulePointerToken<BGR_MATH_FACTOR_HELPER_0, FILLER_TOKEN>
		}));

	//Math factor helper 0
	m_interpreter.SetRule(BGR_MATH_FACTOR_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		KeywordToken<Operator_bracket_open, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		KeywordToken<Operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Math term
	m_interpreter.SetRule(BGR_MATH_TERM, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_MATH_FACTOR, FILLER_TOKEN>,
		RulePointerToken<BGR_MATH_TERM_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Math term helper 0
	m_interpreter.SetRule(BGR_MATH_TERM_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_MATH_TERM_HELPER_1, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MATH_FACTOR, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Math term helper 1
	m_interpreter.SetRule(BGR_MATH_TERM_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		KeywordToken<Operator_times, NONE>,
		KeywordToken<Operator_divide, NONE>,
		KeywordToken<Operator_double_divide, NONE>,
		KeywordToken<Operator_modulus, NONE>
		}));

	//Math expression (must be wrapped because of math factor)
	m_interpreter.SetRule(BGR_MATH_EXPRESSION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_MATH_TERM, FILLER_TOKEN>,
		RulePointerToken<BGR_MATH_EXPRESSION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Math expression helper 0
	m_interpreter.SetRule(BGR_MATH_EXPRESSION_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		CustomOperatorToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MATH_TERM, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Value expression
	m_interpreter.SetRule(BGR_VALUE_EXPRESSION, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		RulePointerToken<BGR_MATH_EXPRESSION, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE_EXPRESSION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Value expression helper 0
	m_interpreter.SetRule(BGR_VALUE_EXPRESSION_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_VALUE_EXPRESSION_HELPER_1, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MATH_EXPRESSION, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Value expression helper 1
	m_interpreter.SetRule(BGR_VALUE_EXPRESSION_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		KeywordToken<Operator_logical_and, NONE, BVO_LOGICAL_AND>,
		KeywordToken<Operator_logical_or, NONE, BVO_LOGICAL_OR>
		}));

	//Value
	m_interpreter.SetRule(BGR_VALUE, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP | BiaInterpreterRule::F_OR, {
		//RulePointerToken<BGR_VARIABLE_DECLARATION, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE_HELPER_0, FILLER_TOKEN>,
		RulePointerToken<BGR_VALUE_EXPRESSION, FILLER_TOKEN>
		}));

	//Value helper 0
	m_interpreter.SetRule(BGR_VALUE_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		IdentifierToken<NONE>,
		AssignOperatorToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_VALUE_EXPRESSION, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Member
	m_interpreter.SetRule(BGR_MEMBER, BiaInterpreterRule(BiaInterpreterRule::F_WRAP_UP, {
		CustomOperatorToken<OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MEMBER_HELPER_2, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MEMBER_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		RulePointerToken<BGR_MEMBER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Member helper 0
	m_interpreter.SetRule(BGR_MEMBER_HELPER_0, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_PARAMETER, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_PARAMETER_ITEM_ACCESS, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	//Member helper 1
	m_interpreter.SetRule(BGR_MEMBER_HELPER_1, BiaInterpreterRule(BiaInterpreterRule::F_NONE, {
		RulePointerToken<BGR_MEMBER_HELPER_3, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		RulePointerToken<BGR_MEMBER_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	//Member helper 2
	m_interpreter.SetRule(BGR_MEMBER_HELPER_2, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		RulePointerToken<BGR_INSTANTIATION, FILLER_TOKEN, 0, BM_INSTANTIATION>,
		StringValueToken<NONE, BM_STRING>,
		IdentifierToken<NONE, BM_IDENTIFIER>
		}));

	//Member helper 3
	m_interpreter.SetRule(BGR_MEMBER_HELPER_3, BiaInterpreterRule(BiaInterpreterRule::F_OR, {
		KeywordToken<Operator_arrow_access, NONE, BAO_ARROW_ACCESS>,
		KeywordToken<Operator_dot, FILLER_TOKEN, BAO_DOT>
		}));
}

}
}