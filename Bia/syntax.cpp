#include "syntax.hpp"
#include "interpreter_token.hpp"
#include "interpreter_id.hpp"
#include "interpreter_string.hpp"


namespace bia
{
namespace grammar
{

interpreter syntax::_interpreter = syntax::init_rules();


const interpreter & syntax::interpreter() noexcept
{
	return _interpreter;
}

interpreter syntax::init_rules()
{
	grammar::interpreter _interpreter;

	// Root
	_interpreter.set_rule(interpreter_rule(BGR_ROOT, interpreter_rule::F_OR, {
		interpreter_token::rule_pointer<BGR_ROOT_HELPER_1>,
		interpreter_token::rule_pointer<BGR_ROOT_HELPER_0>
		}));

	// Root helper 0
	_interpreter.set_rule(interpreter_rule(BGR_ROOT_HELPER_0, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<operator_scope_open, flags::filler_token>,
		interpreter_token::rule_pointer<BGR_ROOT_HELPER_1, flags::filler_token | flags::looping_token | flags::starting_padding_opt_token>,
		interpreter_token::keyword<operator_scope_close, flags::filler_token>
		}));

	// Root helper 1
	_interpreter.set_rule(interpreter_rule(BGR_ROOT_HELPER_1, interpreter_rule::F_OR, {
		interpreter_token::rule_pointer<BGR_VARIABLE_DECLARATION>,
		interpreter_token::rule_pointer<BGR_IF>,
		interpreter_token::rule_pointer<BGR_PRINT>,
		interpreter_token::rule_pointer<BGR_TEST_LOOP>,
		interpreter_token::rule_pointer<BGR_IMPORT>,
		interpreter_token::rule_pointer<BGR_ROOT_HELPER_2>
		}));

	// Root helper 2
	_interpreter.set_rule(interpreter_rule(BGR_ROOT_HELPER_2, interpreter_rule::F_NONE, {
		interpreter_token::rule_pointer<BGR_VALUE>,
		interpreter_token::command_end
		}));

	// Statement
	_interpreter.set_rule(interpreter_rule(BGR_NORMAL_STATEMENT, interpreter_rule::F_OR, {
		interpreter_token::rule_pointer<BGR_ROOT_HELPER_1, flags::filler_token | flags::starting_ws_token>,
		interpreter_token::rule_pointer<BGR_ROOT_HELPER_0, flags::filler_token | flags::starting_ws_opt_token> }));

	// Variable declaration
	_interpreter.set_rule(interpreter_rule(BGR_VARIABLE_DECLARATION, interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_VARIABLE_DECLARATION_HELPER_0, flags::filler_token | flags::ending_ws_token>,
		interpreter_token::identifier,
		interpreter_token::keyword<operator_assign, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::command_end
		}));

	// Variable declaration inline
	_interpreter.set_rule(interpreter_rule(BGR_VARIABLE_DECLARATION_INLINE, interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_VARIABLE_DECLARATION_HELPER_0, flags::filler_token | flags::ending_ws_token>,
		interpreter_token::identifier,
		interpreter_token::keyword<operator_assign, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Variable declaration helper 0
	_interpreter.set_rule(interpreter_rule(BGR_VARIABLE_DECLARATION_HELPER_0, interpreter_rule::F_OR, {
		interpreter_token::keyword<keyword_var>,
		interpreter_token::keyword<keyword_global>,
		}));

	// If
	_interpreter.set_rule(interpreter_rule(BGR_IF, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<keyword_if, flags::filler_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		interpreter_token::rule_pointer<BGR_NORMAL_STATEMENT>,
		interpreter_token::rule_pointer<BGR_IF_HELPER_0, flags::filler_token | flags::looping_token>,
		interpreter_token::rule_pointer<BGR_IF_HELPER_1, flags::filler_token | flags::opt_token>
		}));

	// If helper 0
	_interpreter.set_rule(interpreter_rule(BGR_IF_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::keyword<keyword_else, flags::filler_token | flags::starting_padding_opt_token>,
		interpreter_token::keyword<keyword_if, flags::filler_token | flags::starting_ws_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		interpreter_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// If helper 1
	_interpreter.set_rule(interpreter_rule(BGR_IF_HELPER_1, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<keyword_else, flags::filler_token | flags::starting_padding_opt_token>,
		interpreter_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// Print
	_interpreter.set_rule(interpreter_rule(BGR_PRINT, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<keyword_print, flags::filler_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		interpreter_token::command_end
		}));

	// Test loop
	_interpreter.set_rule(interpreter_rule(BGR_TEST_LOOP, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<keyword_do, flags::opt_token | flags::ending_ws_token>,
		interpreter_token::rule_pointer<BGR_TEST_LOOP_HELPER_0>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		interpreter_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// Test loop helper 0
	_interpreter.set_rule(interpreter_rule(BGR_TEST_LOOP_HELPER_0, interpreter_rule::F_OR, {
		interpreter_token::keyword<keyword_while>,
		interpreter_token::keyword<keyword_until>
		}));

	// Import
	_interpreter.set_rule(interpreter_rule(BGR_IMPORT, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<keyword_import, flags::filler_token | flags::ending_ws_token>,
		interpreter_token::identifier,
		interpreter_token::command_end
		}));

	// Value raw (must be wrapped because of math factor)
	_interpreter.set_rule(interpreter_rule(BGR_VALUE_RAW, interpreter_rule::F_OR | interpreter_rule::F_WRAP_UP, {
		interpreter_token::number, // BV_NUMBER
		interpreter_token::keyword<keyword_true>, // BV_TRUE
		interpreter_token::keyword<keyword_false>, // BV_FALSE
		interpreter_token::rule_pointer<BGR_MEMBER> // BV_MEMBER
		}));

	// Parameter
	_interpreter.set_rule(interpreter_rule(BGR_PARAMETER, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<operator_bracket_open, flags::filler_token>,
		interpreter_token::rule_pointer<BGR_PARAMETER_HELPER_0, flags::filler_token | flags::opt_token>,
		interpreter_token::keyword<operator_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Parameter item access
	_interpreter.set_rule(interpreter_rule(BGR_PARAMETER_ITEM_ACCESS, interpreter_rule::F_WRAP_UP, {
		interpreter_token::keyword<operator_square_bracket_open, flags::filler_token>,
		interpreter_token::rule_pointer<BGR_PARAMETER_HELPER_0, flags::filler_token | flags::opt_token>,
		interpreter_token::keyword<operator_square_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Parameter list helper 0
	_interpreter.set_rule(interpreter_rule(BGR_PARAMETER_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_PARAMETER_HELPER_1, flags::filler_token | flags::looping_token>
		}));

	// Parameter list helper 1
	_interpreter.set_rule(interpreter_rule(BGR_PARAMETER_HELPER_1, interpreter_rule::F_NONE, {
		interpreter_token::keyword<operator_comma, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Math factor
	_interpreter.set_rule(interpreter_rule(BGR_MATH_FACTOR, interpreter_rule::F_OR | interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_VALUE_RAW>,
		interpreter_token::rule_pointer<BGR_MATH_FACTOR_HELPER_0>
		}));

	// Math factor helper 0
	_interpreter.set_rule(interpreter_rule(BGR_MATH_FACTOR_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::keyword<operator_bracket_open, flags::filler_token>,
		interpreter_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::keyword<operator_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Math term
	_interpreter.set_rule(interpreter_rule(BGR_MATH_TERM, interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_MATH_FACTOR>,
		interpreter_token::rule_pointer<BGR_MATH_TERM_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	// Math term helper 0
	_interpreter.set_rule(interpreter_rule(BGR_MATH_TERM_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::dot_operator,
		interpreter_token::rule_pointer<BGR_MATH_FACTOR, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Math expression (must be wrapped because of math factor)
	_interpreter.set_rule(interpreter_rule(BGR_MATH_EXPRESSION, interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_MATH_TERM>,
		interpreter_token::rule_pointer<BGR_MATH_EXPRESSION_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	// Math expression helper 0
	_interpreter.set_rule(interpreter_rule(BGR_MATH_EXPRESSION_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::custom_operator<flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_MATH_TERM, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Condition expression
	_interpreter.set_rule(interpreter_rule(BGR_CONDITION_EXPRESSION, interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_MATH_EXPRESSION>,
		interpreter_token::rule_pointer<BGR_CONDITION_EXPRESSION_HELPER_0, flags::filler_token | flags::opt_token>
		}));

	// Condition expression helper 0
	_interpreter.set_rule(interpreter_rule(BGR_CONDITION_EXPRESSION_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::compare_operator,
		interpreter_token::rule_pointer<BGR_MATH_EXPRESSION, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Value expression
	_interpreter.set_rule(interpreter_rule(BGR_VALUE_EXPRESSION, interpreter_rule::F_WRAP_UP, {
		interpreter_token::rule_pointer<BGR_CONDITION_EXPRESSION>,
		interpreter_token::rule_pointer<BGR_VALUE_EXPRESSION_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	// Value expression helper 0
	_interpreter.set_rule(interpreter_rule(BGR_VALUE_EXPRESSION_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::rule_pointer<BGR_VALUE_EXPRESSION_HELPER_1, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_CONDITION_EXPRESSION, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Value expression helper 1
	_interpreter.set_rule(interpreter_rule(BGR_VALUE_EXPRESSION_HELPER_1, interpreter_rule::F_OR, {
		interpreter_token::keyword<operator_logical_and>, // BVO_LOGICAL_AND
		interpreter_token::keyword<operator_logical_or> // BVO_LOGICAL_OR
		}));

	// Value
	_interpreter.set_rule(interpreter_rule(BGR_VALUE, interpreter_rule::F_WRAP_UP | interpreter_rule::F_OR, {
		interpreter_token::rule_pointer<BGR_VARIABLE_DECLARATION_INLINE>,
		interpreter_token::rule_pointer<BGR_VALUE_HELPER_0>,
		interpreter_token::rule_pointer<BGR_VALUE_EXPRESSION>
		}));

	// Value helper 0
	_interpreter.set_rule(interpreter_rule(BGR_VALUE_HELPER_0, interpreter_rule::F_NONE, {
		interpreter_token::identifier,
		interpreter_token::assign_operator,
		interpreter_token::rule_pointer<BGR_VALUE_EXPRESSION, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Member
	_interpreter.set_rule(interpreter_rule(BGR_MEMBER, interpreter_rule::F_WRAP_UP, {
		//interpreter_token::custom_operator<flags::opt_token>,
		interpreter_token::first_member,
		interpreter_token::rule_pointer<BGR_MEMBER_HELPER_0, flags::filler_token | flags::looping_token>,
		interpreter_token::rule_pointer<BGR_MEMBER_HELPER_1, flags::filler_token | flags::looping_token>
		}));

	// Member helper 0
	_interpreter.set_rule(interpreter_rule(BGR_MEMBER_HELPER_0, interpreter_rule::F_OR, {
		interpreter_token::rule_pointer<BGR_PARAMETER, flags::filler_token | flags::starting_ws_opt_token>,
		interpreter_token::rule_pointer<BGR_PARAMETER_ITEM_ACCESS, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Member helper 1
	_interpreter.set_rule(interpreter_rule(BGR_MEMBER_HELPER_1, interpreter_rule::F_NONE, {
		interpreter_token::keyword<operator_dot, flags::filler_token | flags::starting_ws_opt_token | flags::ending_ws_opt_token>,
		interpreter_token::identifier,
		interpreter_token::rule_pointer<BGR_MEMBER_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	return _interpreter;
}

}
}
