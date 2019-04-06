#include "syntax.hpp"
#include "lexer_token.hpp"
#include "keyword.hpp"
#include "grammar_id.hpp"


namespace bia
{
namespace grammar
{

lexer syntax::_lexer = syntax::init_rules();


const lexer & syntax::lexer() noexcept
{
	return _lexer;
}

lexer syntax::init_rules()
{
	grammar::lexer _lexer;

	// Root
	_lexer.set_rule(grammar_rule(BGR_ROOT, grammar_rule::F_OR, {
		lexer_token::rule_pointer<BGR_ROOT_HELPER_1>,
		lexer_token::rule_pointer<BGR_ROOT_HELPER_0, flags::none, BS_SCOPE>
		}));

	// Root helper 0
	_lexer.set_rule(grammar_rule(BGR_ROOT_HELPER_0, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<operator_scope_open, flags::filler_token>,
		lexer_token::rule_pointer<BGR_ROOT, flags::filler_token | flags::looping_token | flags::starting_padding_opt_token>,
		lexer_token::keyword<operator_scope_close, flags::filler_token>
		}));

	// Root helper 1
	_lexer.set_rule(grammar_rule(BGR_ROOT_HELPER_1, grammar_rule::F_OR, {
		lexer_token::rule_pointer<BGR_VARIABLE_DECLARATION>,
		lexer_token::rule_pointer<BGR_IF>,
		lexer_token::rule_pointer<BGR_TEST_LOOP>,
		lexer_token::rule_pointer<BGR_FLOW_CONTROL>,
		lexer_token::rule_pointer<BGR_FUNCTION>,
		lexer_token::rule_pointer<BGR_IMPORT>,
		lexer_token::rule_pointer<BGR_ROOT_HELPER_2>
		}));

	// Root helper 2
	_lexer.set_rule(grammar_rule(BGR_ROOT_HELPER_2, grammar_rule::F_NONE, {
		lexer_token::rule_pointer<BGR_VALUE>,
		lexer_token::command_end
		}));

	// Statement
	_lexer.set_rule(grammar_rule(BGR_NORMAL_STATEMENT, grammar_rule::F_OR, {
		lexer_token::rule_pointer<BGR_ROOT_HELPER_1, flags::filler_token | flags::starting_ws_token>,
		lexer_token::rule_pointer<BGR_ROOT_HELPER_0, flags::filler_token | flags::starting_ws_opt_token> }));

	// Flow control
	_lexer.set_rule(grammar_rule(BGR_FLOW_CONTROL, grammar_rule::F_WRAP_UP | grammar_rule::F_OR, {
		lexer_token::rule_pointer<BGR_FLOW_CONTROL_HELPER_0>,
		lexer_token::rule_pointer<BGR_FLOW_CONTROL_HELPER_2>
		}));

	// Flow control helper: return
	_lexer.set_rule(grammar_rule(BGR_FLOW_CONTROL_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::keyword<keyword_return>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token | flags::opt_token>,
		lexer_token::command_end
		}));

	// Flow control helper: single commands
	_lexer.set_rule(grammar_rule(BGR_FLOW_CONTROL_HELPER_1, grammar_rule::F_OR, {
		lexer_token::keyword<keyword_break>,
		lexer_token::keyword<keyword_continue>
		}));

	// Flow control helper: single command
	_lexer.set_rule(grammar_rule(BGR_FLOW_CONTROL_HELPER_2, grammar_rule::F_NONE, {
		lexer_token::rule_pointer<BGR_FLOW_CONTROL_HELPER_1>,
		lexer_token::command_end
		}));

	// Variable declaration
	_lexer.set_rule(grammar_rule(BGR_VARIABLE_DECLARATION, grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_VARIABLE_DECLARATION_HELPER_0, flags::filler_token | flags::ending_ws_token>,
		lexer_token::identifier,
		lexer_token::keyword<operator_assign, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::command_end
		}));

	// Variable declaration inline
	_lexer.set_rule(grammar_rule(BGR_VARIABLE_DECLARATION_INLINE, grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_VARIABLE_DECLARATION_HELPER_0, flags::filler_token | flags::ending_ws_token>,
		lexer_token::identifier,
		lexer_token::keyword<operator_assign, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Variable declaration helper 0
	_lexer.set_rule(grammar_rule(BGR_VARIABLE_DECLARATION_HELPER_0, grammar_rule::F_OR, {
		lexer_token::keyword<keyword_var>,
		lexer_token::keyword<keyword_global>,
		}));

	// If
	_lexer.set_rule(grammar_rule(BGR_IF, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<keyword_if, flags::filler_token>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		lexer_token::rule_pointer<BGR_NORMAL_STATEMENT>,
		lexer_token::rule_pointer<BGR_IF_HELPER_0, flags::filler_token | flags::looping_token>,
		lexer_token::rule_pointer<BGR_IF_HELPER_1, flags::filler_token | flags::opt_token>
		}));

	// If helper 0
	_lexer.set_rule(grammar_rule(BGR_IF_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::keyword<keyword_else, flags::filler_token | flags::starting_padding_opt_token>,
		lexer_token::keyword<keyword_if, flags::filler_token | flags::starting_ws_token>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		lexer_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// If helper 1
	_lexer.set_rule(grammar_rule(BGR_IF_HELPER_1, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<keyword_else, flags::filler_token | flags::starting_padding_opt_token>,
		lexer_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// Test loop
	_lexer.set_rule(grammar_rule(BGR_TEST_LOOP, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<keyword_do, flags::opt_token | flags::ending_ws_token>,
		lexer_token::rule_pointer<BGR_TEST_LOOP_HELPER_0>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_token>,
		lexer_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// Test loop helper 0
	_lexer.set_rule(grammar_rule(BGR_TEST_LOOP_HELPER_0, grammar_rule::F_OR, {
		lexer_token::keyword<keyword_while>,
		lexer_token::keyword<keyword_until>
		}));

	// Function
	_lexer.set_rule(grammar_rule(BGR_FUNCTION, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<keyword_function, flags::filler_token | flags::ending_ws_token>,
		lexer_token::identifier,
		lexer_token::rule_pointer<BGR_PARAMETER_SIGNATURE, flags::filler_token | flags::starting_ws_opt_token | flags::opt_token>,
		lexer_token::rule_pointer<BGR_NORMAL_STATEMENT>
		}));

	// Parameter signature
	_lexer.set_rule(grammar_rule(BGR_PARAMETER_SIGNATURE, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<operator_bracket_open, flags::filler_token>,
		lexer_token::rule_pointer<BGR_PARAMETER_SIGNATURE_HELPER_0, flags::filler_token | flags::opt_token | flags::starting_ws_opt_token>,
		lexer_token::keyword<operator_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Parameter signature helper 0
	_lexer.set_rule(grammar_rule(BGR_PARAMETER_SIGNATURE_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::identifier,
		lexer_token::rule_pointer<BGR_PARAMETER_SIGNATURE_HELPER_1, flags::filler_token | flags::looping_token>
		}));

	// Parameter signature helper 1
	_lexer.set_rule(grammar_rule(BGR_PARAMETER_SIGNATURE_HELPER_1, grammar_rule::F_NONE, {
		lexer_token::keyword<operator_comma, flags::filler_token | flags::starting_ws_opt_token | flags::ending_ws_opt_token>,
		lexer_token::identifier
		}));

	// Import
	_lexer.set_rule(grammar_rule(BGR_IMPORT, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<keyword_import, flags::filler_token | flags::ending_ws_token>,
		lexer_token::identifier,
		lexer_token::command_end
		}));

	// Value raw (must be wrapped because of math factor)
	_lexer.set_rule(grammar_rule(BGR_VALUE_RAW, grammar_rule::F_OR | grammar_rule::F_WRAP_UP, {
		lexer_token::number, // BV_NUMBER
		lexer_token::keyword<keyword_true>, // BV_TRUE
		lexer_token::keyword<keyword_false>, // BV_FALSE
		lexer_token::rule_pointer<BGR_MEMBER> // BV_MEMBER
		}));

	// Parameter
	_lexer.set_rule(grammar_rule(BGR_PARAMETER, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<operator_bracket_open, flags::filler_token>,
		lexer_token::rule_pointer<BGR_PARAMETER_HELPER_0, flags::filler_token | flags::opt_token>,
		lexer_token::keyword<operator_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Parameter item access
	_lexer.set_rule(grammar_rule(BGR_PARAMETER_ITEM_ACCESS, grammar_rule::F_WRAP_UP, {
		lexer_token::keyword<operator_square_bracket_open, flags::filler_token>,
		lexer_token::rule_pointer<BGR_PARAMETER_HELPER_0, flags::filler_token | flags::opt_token>,
		lexer_token::keyword<operator_square_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Parameter list helper 0
	_lexer.set_rule(grammar_rule(BGR_PARAMETER_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_PARAMETER_HELPER_1, flags::filler_token | flags::looping_token>
		}));

	// Parameter list helper 1
	_lexer.set_rule(grammar_rule(BGR_PARAMETER_HELPER_1, grammar_rule::F_NONE, {
		lexer_token::keyword<operator_comma, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Math factor
	_lexer.set_rule(grammar_rule(BGR_MATH_FACTOR, grammar_rule::F_OR | grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_VALUE_RAW>,
		lexer_token::rule_pointer<BGR_MATH_FACTOR_HELPER_0>
		}));

	// Math factor helper 0
	_lexer.set_rule(grammar_rule(BGR_MATH_FACTOR_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::keyword<operator_bracket_open, flags::filler_token>,
		lexer_token::rule_pointer<BGR_VALUE, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::keyword<operator_bracket_close, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Math term
	_lexer.set_rule(grammar_rule(BGR_MATH_TERM, grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_MATH_FACTOR>,
		lexer_token::rule_pointer<BGR_MATH_TERM_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	// Math term helper 0
	_lexer.set_rule(grammar_rule(BGR_MATH_TERM_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::dot_operator,
		lexer_token::rule_pointer<BGR_MATH_FACTOR, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Math expression (must be wrapped because of math factor)
	_lexer.set_rule(grammar_rule(BGR_MATH_EXPRESSION, grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_MATH_TERM>,
		lexer_token::rule_pointer<BGR_MATH_EXPRESSION_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	// Math expression helper 0
	_lexer.set_rule(grammar_rule(BGR_MATH_EXPRESSION_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::custom_operator<flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_MATH_TERM, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Condition expression
	_lexer.set_rule(grammar_rule(BGR_CONDITION_EXPRESSION, grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_MATH_EXPRESSION>,
		lexer_token::rule_pointer<BGR_CONDITION_EXPRESSION_HELPER_0, flags::filler_token | flags::opt_token>
		}));

	// Condition expression helper 0
	_lexer.set_rule(grammar_rule(BGR_CONDITION_EXPRESSION_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::compare_operator,
		lexer_token::rule_pointer<BGR_MATH_EXPRESSION, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Value expression
	_lexer.set_rule(grammar_rule(BGR_VALUE_EXPRESSION, grammar_rule::F_WRAP_UP, {
		lexer_token::rule_pointer<BGR_CONDITION_EXPRESSION>,
		lexer_token::rule_pointer<BGR_VALUE_EXPRESSION_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	// Value expression helper 0
	_lexer.set_rule(grammar_rule(BGR_VALUE_EXPRESSION_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::rule_pointer<BGR_VALUE_EXPRESSION_HELPER_1, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_CONDITION_EXPRESSION, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Value expression helper 1
	_lexer.set_rule(grammar_rule(BGR_VALUE_EXPRESSION_HELPER_1, grammar_rule::F_OR, {
		lexer_token::keyword<operator_logical_and>, // BVO_LOGICAL_AND
		lexer_token::keyword<operator_logical_or> // BVO_LOGICAL_OR
		}));

	// Value
	_lexer.set_rule(grammar_rule(BGR_VALUE, grammar_rule::F_WRAP_UP | grammar_rule::F_OR, {
		lexer_token::rule_pointer<BGR_VARIABLE_DECLARATION_INLINE>,
		lexer_token::rule_pointer<BGR_VALUE_HELPER_0>,
		lexer_token::rule_pointer<BGR_VALUE_EXPRESSION>
		}));

	// Value helper 0
	_lexer.set_rule(grammar_rule(BGR_VALUE_HELPER_0, grammar_rule::F_NONE, {
		lexer_token::identifier,
		lexer_token::assign_operator,
		lexer_token::rule_pointer<BGR_VALUE_EXPRESSION, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Member
	_lexer.set_rule(grammar_rule(BGR_MEMBER, grammar_rule::F_WRAP_UP, {
		//interpreter_token::custom_operator<flags::opt_token>,
		lexer_token::first_member,
		lexer_token::rule_pointer<BGR_MEMBER_HELPER_0, flags::filler_token | flags::looping_token>,
		lexer_token::rule_pointer<BGR_MEMBER_HELPER_1, flags::filler_token | flags::looping_token>
		}));

	// Member helper 0
	_lexer.set_rule(grammar_rule(BGR_MEMBER_HELPER_0, grammar_rule::F_OR, {
		lexer_token::rule_pointer<BGR_PARAMETER, flags::filler_token | flags::starting_ws_opt_token>,
		lexer_token::rule_pointer<BGR_PARAMETER_ITEM_ACCESS, flags::filler_token | flags::starting_ws_opt_token>
		}));

	// Member helper 1
	_lexer.set_rule(grammar_rule(BGR_MEMBER_HELPER_1, grammar_rule::F_NONE, {
		lexer_token::keyword<operator_dot, flags::filler_token | flags::starting_ws_opt_token | flags::ending_ws_opt_token>,
		lexer_token::identifier,
		lexer_token::rule_pointer<BGR_MEMBER_HELPER_0, flags::filler_token | flags::looping_token>
		}));

	return _lexer;
}

}
}
