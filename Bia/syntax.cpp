#include "syntax.hpp"
#include "interpreter_token.hpp"
#include "interpreter_ids.hpp"
#include "interpreter_strings.hpp"


namespace bia
{
namespace grammar
{

interpreter syntax::_interpreter = syntax::init_rules();


const interpreter & syntax::get_interpreter() noexcept
{
	return _interpreter;
}

interpreter syntax::init_rules()
{
	interpreter _interpreter;

	// Root
	_interpreter.set_rule(interpreter_rule(BGR_ROOT, interpreter_rule::F_OR, {
		token_rule<BGR_ROOT_HELPER_1, FILLER_TOKEN>,
		token_rule<BGR_ROOT_HELPER_0, FILLER_TOKEN> 
		}));

	// Root helper 0
	_interpreter.set_rule(interpreter_rule(BGR_ROOT_HELPER_0, interpreter_rule::F_WRAP_UP, {
		token_keyword<operator_scope_open, FILLER_TOKEN>,
		token_rule<BGR_ROOT_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN | STARTING_PADDING_OPTIONAL_TOKEN>,
		token_keyword<operator_scope_close, FILLER_TOKEN>
		}));

	// Root helper 1
	_interpreter.set_rule(BGR_ROOT_HELPER_1, interpreter_rule(interpreter_rule::F_OR, {
		token_rule<BGR_VARIABLE_DECLARATION, FILLER_TOKEN>,
		token_rule<BGR_IF, FILLER_TOKEN>,
		token_rule<BGR_PRINT, FILLER_TOKEN>,
		token_rule<BGR_TEST_LOOP, FILLER_TOKEN>,
		token_rule<BGR_IMPORT, FILLER_TOKEN>,
		interpreter_token::comment,
		token_rule<BGR_ROOT_HELPER_2, FILLER_TOKEN>
		}));

	// Root helper 2
	_interpreter.set_rule(BGR_ROOT_HELPER_2, interpreter_rule(interpreter_rule::F_NONE, {
		token_rule<BGR_VALUE, FILLER_TOKEN>,
		interpreter_token::command_end
		}));

	// Statement
	_interpreter.set_rule(BGR_NORMAL_STATEMENT, interpreter_rule(interpreter_rule::F_OR, {
		token_rule<BGR_ROOT_HELPER_1, FILLER_TOKEN | STARTING_PADDING_TOKEN>,
		token_rule<BGR_ROOT_HELPER_0, FILLER_TOKEN | STARTING_PADDING_OPTIONAL_TOKEN> }));

	// Variable declaration
	_interpreter.set_rule(BGR_VARIABLE_DECLARATION, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_global, FILLER_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_TOKEN>,
		token_rule<BGR_VARIABLE_DECLARATION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		token_keyword<operator_equals, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		interpreter_token::command_end
		}));

	// Variable declaration helper 0
	_interpreter.set_rule(BGR_VARIABLE_DECLARATION_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		token_keyword<operator_comma, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// If
	_interpreter.set_rule(BGR_IF, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_if, FILLER_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		token_rule<BGR_NORMAL_STATEMENT, FILLER_TOKEN>,
		token_rule<BGR_IF_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		token_rule<BGR_IF_HELPER_1, FILLER_TOKEN | OPTIONAL_TOKEN>
		}));

	// If helper 0
	_interpreter.set_rule(BGR_IF_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		token_keyword<keyword_else, FILLER_TOKEN | STARTING_PADDING_OPTIONAL_TOKEN>,
		token_keyword<keyword_if, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		token_rule<BGR_NORMAL_STATEMENT, FILLER_TOKEN>
		}));

	// If helper 1
	_interpreter.set_rule(BGR_IF_HELPER_1, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_else, FILLER_TOKEN | STARTING_PADDING_OPTIONAL_TOKEN>,
		token_rule<BGR_NORMAL_STATEMENT, FILLER_TOKEN>
		}));

	// Print
	_interpreter.set_rule(BGR_PRINT, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_print, FILLER_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		interpreter_token::command_end
		}));

	// Test loop
	_interpreter.set_rule(BGR_TEST_LOOP, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_do, OPTIONAL_TOKEN | ENDING_WHITESPACE_TOKEN>,
		token_rule<BGR_TEST_LOOP_HELPER_0, FILLER_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_TOKEN>,
		token_rule<BGR_NORMAL_STATEMENT, FILLER_TOKEN>
		}));

	// Test loop helper 0
	_interpreter.set_rule(BGR_TEST_LOOP_HELPER_0, interpreter_rule(interpreter_rule::F_OR, {
		token_keyword<keyword_while, NONE, LT_WHILE>,
		token_keyword<keyword_until, NONE, LT_UNTIL>
		}));

	// Import
	_interpreter.set_rule(BGR_IMPORT, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_import, FILLER_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_TOKEN>,
		interpreter_token::command_end
		}));

	// Value raw (must be wrapped because of math factor)
	_interpreter.set_rule(BGR_VALUE_RAW, interpreter_rule(interpreter_rule::F_OR | interpreter_rule::F_WRAP_UP, {
		interpreter_token::number, // BV_NUMBER
		interpreter_token::keyword<keyword_true, NONE, BV_TRUE>,
		token_keyword<keyword_false, NONE, BV_FALSE>,
		token_rule<BGR_MEMBER, FILLER_TOKEN, 0, BV_MEMBER>
		}));

	// Instantiation
	_interpreter.set_rule(BGR_INSTANTIATION, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<keyword_new, FILLER_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_TOKEN>,
		token_rule<BGR_PARAMETER, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Parameter
	_interpreter.set_rule(BGR_PARAMETER, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<operator_bracket_open, FILLER_TOKEN>,
		token_rule<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>,
		token_keyword<operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Parameter item access
	_interpreter.set_rule(BGR_PARAMETER_ITEM_ACCESS, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_keyword<operator_square_bracket_open, FILLER_TOKEN>,
		token_rule<BGR_PARAMETER_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>,
		token_keyword<operator_square_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Parameter list helper 0
	_interpreter.set_rule(BGR_PARAMETER_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_PARAMETER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	// Parameter list helper 1
	_interpreter.set_rule(BGR_PARAMETER_HELPER_1, interpreter_rule(interpreter_rule::F_NONE, {
		token_keyword<operator_comma, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Math factor
	_interpreter.set_rule(BGR_MATH_FACTOR, interpreter_rule(interpreter_rule::F_OR | interpreter_rule::F_WRAP_UP, {
		token_rule<BGR_VALUE_RAW, FILLER_TOKEN>,
		token_rule<BGR_MATH_FACTOR_HELPER_0, FILLER_TOKEN>
		}));

	// Math factor helper 0
	_interpreter.set_rule(BGR_MATH_FACTOR_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		token_keyword<operator_bracket_open, FILLER_TOKEN>,
		token_rule<BGR_VALUE, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_keyword<operator_bracket_close, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Math term
	_interpreter.set_rule(BGR_MATH_TERM, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_rule<BGR_MATH_FACTOR, FILLER_TOKEN>,
		token_rule<BGR_MATH_TERM_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	// Math term helper 0
	_interpreter.set_rule(BGR_MATH_TERM_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		token_rule<BGR_MATH_TERM_HELPER_1, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_MATH_FACTOR, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Math term helper 1
	_interpreter.set_rule(BGR_MATH_TERM_HELPER_1, interpreter_rule(interpreter_rule::F_OR, {
		token_keyword<operator_times, NONE>,
		token_keyword<operator_divide, NONE>,
		token_keyword<operator_double_divide, NONE>,
		token_keyword<operator_modulus, NONE>
		}));

	// Math expression (must be wrapped because of math factor)
	_interpreter.set_rule(BGR_MATH_EXPRESSION, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_rule<BGR_MATH_TERM, FILLER_TOKEN>,
		token_rule<BGR_MATH_EXPRESSION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	// Math expression helper 0
	_interpreter.set_rule(BGR_MATH_EXPRESSION_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		CustomOperatorToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_MATH_TERM, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Condition expression
	_interpreter.set_rule(BGR_CONDITION_EXPRESSION, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_rule<BGR_MATH_EXPRESSION, FILLER_TOKEN>,
		token_rule<BGR_CONDITION_EXPRESSION_HELPER_0, FILLER_TOKEN | OPTIONAL_TOKEN>
		}));

	// Condition expression helper 0
	_interpreter.set_rule(BGR_CONDITION_EXPRESSION_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		CompareOperatorToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_MATH_EXPRESSION, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Value expression
	_interpreter.set_rule(BGR_VALUE_EXPRESSION, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		token_rule<BGR_CONDITION_EXPRESSION, FILLER_TOKEN>,
		token_rule<BGR_VALUE_EXPRESSION_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	// Value expression helper 0
	_interpreter.set_rule(BGR_VALUE_EXPRESSION_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		token_rule<BGR_VALUE_EXPRESSION_HELPER_1, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_CONDITION_EXPRESSION, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Value expression helper 1
	_interpreter.set_rule(BGR_VALUE_EXPRESSION_HELPER_1, interpreter_rule(interpreter_rule::F_OR, {
		token_keyword<operator_logical_and, NONE, BVO_LOGICAL_AND>,
		token_keyword<operator_logical_or, NONE, BVO_LOGICAL_OR>
		}));

	// Value
	_interpreter.set_rule(BGR_VALUE, interpreter_rule(interpreter_rule::F_WRAP_UP | interpreter_rule::F_OR, {
		// token_rule<BGR_VARIABLE_DECLARATION, FILLER_TOKEN>,
		token_rule<BGR_VALUE_HELPER_0, FILLER_TOKEN>,
		token_rule<BGR_VALUE_EXPRESSION, FILLER_TOKEN>
		}));

	// Value helper 0
	_interpreter.set_rule(BGR_VALUE_HELPER_0, interpreter_rule(interpreter_rule::F_NONE, {
		IdentifierToken<NONE>,
		AssignOperatorToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_VALUE_EXPRESSION, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Member
	_interpreter.set_rule(BGR_MEMBER, interpreter_rule(interpreter_rule::F_WRAP_UP, {
		CustomOperatorToken<OPTIONAL_TOKEN>,
		token_rule<BGR_MEMBER_HELPER_2, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_MEMBER_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>,
		token_rule<BGR_MEMBER_HELPER_1, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	// Member helper 0
	_interpreter.set_rule(BGR_MEMBER_HELPER_0, interpreter_rule(interpreter_rule::F_OR, {
		token_rule<BGR_PARAMETER, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_PARAMETER_ITEM_ACCESS, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>
		}));

	// Member helper 1
	_interpreter.set_rule(BGR_MEMBER_HELPER_1, interpreter_rule(interpreter_rule::F_NONE, {
		token_rule<BGR_MEMBER_HELPER_3, FILLER_TOKEN | STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		IdentifierToken<STARTING_WHITESPACE_OPTIONAL_TOKEN>,
		token_rule<BGR_MEMBER_HELPER_0, FILLER_TOKEN | LOOPING_TOKEN>
		}));

	// Member helper 2
	_interpreter.set_rule(BGR_MEMBER_HELPER_2, interpreter_rule(interpreter_rule::F_OR, {
		token_rule<BGR_INSTANTIATION, FILLER_TOKEN, 0, BM_INSTANTIATION>,
		StringValueToken<NONE, BM_STRING>,
		IdentifierToken<NONE, BM_IDENTIFIER>
		}));

	// Member helper 3
	_interpreter.set_rule(BGR_MEMBER_HELPER_3, interpreter_rule(interpreter_rule::F_OR, {
		token_keyword<operator_arrow_access, NONE, BAO_ARROW_ACCESS>,
		token_keyword<operator_dot, FILLER_TOKEN, BAO_DOT>
		}));

	return _interpreter;
}

}
}