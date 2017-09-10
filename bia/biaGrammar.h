#pragma once

#include "biaInterpreter.h"
#include "biaInterpreterTokens.h"
#include "biaInterpreterStringSet.h"


namespace bia
{
namespace api
{
namespace grammar
{

enum BIA_GRAMMAR_RULE
{
	BGR_ROOT,
	BGR_VARIABLE_DECLARATION,
	BGR_VALUE,
	BGR_STRING
};

enum BIA_VALUE
{
	BV_NUMBER,
	BV_STRING,
	BV_TRUE,
	BV_FALSE,
	BV_NULL
};


inline BiaInterpreter<4> & InitializeRules()
{
   static BiaInterpreter<4> interpreter;
	BiaInterpreterRule tmp;

	//Root
	tmp.Reset(1, true);
	
	tmp.SetToken(0, RulePointerToken<BGR_VARIABLE_DECLARATION, NONE>);

	interpreter.SetRule(BGR_ROOT, std::move(tmp));

	//Variable declaration
	tmp.Reset(9);

	tmp.SetToken(0, KeywordToken<Keyword_var, FILLER_TOKEN>)
		.SetToken(1, CharsetToken<Charset_whitespace, FILLER_TOKEN, 1>)
		.SetToken(2, IdentifierToken<NONE>)
		.SetToken(3, CharsetToken<Charset_whitespace, FILLER_TOKEN | OPTIONAL_TOKEN>)
		.SetToken(4, KeywordToken<Operator_equals, FILLER_TOKEN>)
		.SetToken(5, CharsetToken<Charset_whitespace, FILLER_TOKEN | OPTIONAL_TOKEN>)
		.SetToken(6, RulePointerToken<BGR_VALUE, FILLER_TOKEN>)
		.SetToken(7, CharsetToken<Charset_whitespace, FILLER_TOKEN | OPTIONAL_TOKEN>)
		.SetToken(8, KeywordToken<Operator_semicolon, FILLER_TOKEN>);

	interpreter.SetRule(BGR_VARIABLE_DECLARATION, std::move(tmp));

	//Value
	tmp.Reset(5, true);

	tmp.SetToken(BV_NUMBER, NumberValueToken<NONE>)
		.SetToken(BV_STRING, RulePointerToken<BGR_STRING, FILLER_TOKEN>)
		.SetToken(BV_TRUE, KeywordToken<Keyword_true, NONE>)
		.SetToken(BV_FALSE, KeywordToken<Keyword_false, NONE>)
		.SetToken(BV_NULL, KeywordToken<Keyword_null, NONE>);

	interpreter.SetRule(BGR_VALUE, std::move(tmp));

	//String
	tmp.Reset(3);

	tmp.SetToken(0, KeywordToken<Operator_quote, FILLER_TOKEN>)
		.SetToken(1, StringValueToken<NONE>)
		.SetToken(2, KeywordToken<Operator_quote, FILLER_TOKEN>);

	interpreter.SetRule(BGR_STRING, std::move(tmp));

	return interpreter;
}

enum BIA_GRAMMAR_IDENTIFIER
{
	BGI_R_ROOT,
	BGI_R_VALUE,
	BGI_R_MATH_EXPRESSION,

	BGI_OPERATOR,
	BGI_DOT_OPERATOR,
	BGI_ASSIGN_OPERATOR,
	BGI_CONDITIONAL_AND,
	BGI_CONDITIONAL_OR,
	BGI_QUOTE,
	BGI_EXCLAMATION_MARK,

	BGI_KEY_ELSE,
	BGI_KEY_TRUE,
	BGI_KEY_FALSE,
	BGI_KEY_NULL,
	BGI_COPYOF,
	BGI_IDENTIFIER,
	BGI_NUMBER,
	BGI_STRING,
	BGI_VALUE,
	BGI_PARAMETER_LIST,
	BGI_MEMBER_CALL,
	BGI_NUMBER_LITERAL,
	BGI_CONDITION,
	BGI_VARIABLE_DECLARATION,
	BGI_VARIABLE_ASSIGNMENT,
	BGI_FOR_LOOP_RIGHT,
	BGI_LOOP_REGISTERS,
	BGI_INSTANTIATION,
	BGI_ITEM_ACCESS,
	BGI_IMPORT_MODULE,

	BGI_MATH_TERM,
	BGI_MATH_EXPRESSION,
	BGI_MATH_PLUS,
	BGI_MATH_MINUS,

	BGI_TERM_VARIABLE_DECLARATION,
	BGI_TERM_VARIABLE_ASSIGNEMENT,
	BGI_TERM_CALL,
	BGI_TERM_WHILE,
	BGI_TERM_IF,
	BGI_TERM_EMPTY,
	BGI_TERM_FOR,
	BGI_TERM_RANGE_LOOP,
	BGI_TERM_PRINT,
	BGI_TERM_RETURN,
	BGI_TERM_DELETE,
	BGI_TERM_IMPORT,
	BGI_TERM_FUNCTION_DEFINITION
};

class BiaGrammar
{
public:
//	static void InitializeGrammar();

	//static yinterpreter sBiaGrammar;
};

}
}
}