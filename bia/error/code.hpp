#ifndef BIA_ERROR_CODE_HPP_
#define BIA_ERROR_CODE_HPP_

#include <system_error>
#include <type_traits>

namespace bia {
namespace error {

enum class Code
{
	success,

	bad_ascii,
	unfinished_utf_sequence,
	bad_utf_sequence,
	bad_unicode,

	out_of_stack,
	bad_stack_alignment,
	bad_narrowing,
	bad_cast,
	out_of_bounds,
	null_argument,
	argument_count_mismatch,
	bad_operation,

	// bad usage
	empty_optional,
	empty_variant,
	bad_variant_index,
	undefined_definition,

	// lexing errors
	expected_opening_curly_bracket = 50,
	expected_closing_curly_bracket,
	expected_opening_bracket,
	expected_closing_bracket,
	expected_scope,
	expected_return,
	expected_yield,
	expected_defer,
	expected_flow_control,
	expected_type_declaration,
	expected_type_definition,
	expected_in,
	expected_parameter_list,
	expected_regex,
	expected_let,
	expected_drop,
	expected_if,
	expected_member_access,
	expected_else,
	expected_else_if,
	expected_import_statement,
	expected_command_end,
	expected_string,
	expected_while_statement,
	expected_seperator,
	expected_use,
	expected_assignment,
	bad_tuple,
	bad_constant_keyword,
	bad_for_statement,
	bad_function_statement,
	bad_identifier,
	bad_if_statement,
	bad_else_statement,
	bad_else_if_statement,
	bad_number,
	bad_operator,

	// compilation errors
	type_mismatch = 150,
	not_boolean,
	symbol_already_declared,
	symbol_not_a_type,
	symbol_not_a_value,
	symbol_immutable,
	undefined_symbol,
	type_not_truthable,
	not_an_integral,
	not_a_function,
	too_few_arguments,
	too_many_arguments,
	not_an_object,
	unsupported_operator,
	symbol_defined_in_different_scope,

	// bvm errors
	bad_opcode = 200,
	bad_offset_option,
	bad_constant_option,
	bad_resource_option,
	bad_member_source_option,
	bad_member_destination_option,

	// runtime errors
	module_not_found = 250,

	bad_switch_value = 300,
	why_did_this_happen,
};

enum class Condition
{
	success,
	lexer,
	compiler,
	bvm,
	runtime,
	implementation,
};

std::error_condition make_error_condition(Condition condition) noexcept;

inline const std::error_category& code_category() noexcept
{
	static class : public std::error_category
	{
	public:
		const char* name() const noexcept override
		{
			return "bialang";
		}
		std::error_condition default_error_condition(int code) const noexcept override
		{
			if (code >= 50 && code < 150) {
				return make_error_condition(Condition::lexer);
			} else if (code >= 150 && code < 200) {
				return make_error_condition(Condition::compiler);
			} else if (code >= 200 && code < 250) {
				return make_error_condition(Condition::bvm);
			} else if (code >= 250 && code < 300) {
				return make_error_condition(Condition::runtime);
			}
			return error_category::default_error_condition(code);
		}
		std::string message(int ec) const override
		{
			switch (static_cast<Code>(ec)) {
			case Code::bad_ascii: return "bad ASCII code point value";
			case Code::unfinished_utf_sequence: return "unfinished UTF sequence";
			case Code::bad_utf_sequence: return "bad UTF sequence";
			case Code::bad_unicode: return "bad Unicode code point value";
			case Code::bad_stack_alignment: return "bad stack alignment";
			case Code::bad_narrowing: return "bad narrowing";
			case Code::bad_cast: return "bad cast";
			case Code::out_of_bounds: return "out of bounds";
			case Code::null_argument: return "null argument not allowed";
			case Code::argument_count_mismatch: return "argument count mismatch";
			case Code::bad_operation: return "bad operation";
			case Code::empty_variant: return "accessing empty variant";
			case Code::bad_variant_index: return "bad variant index";
			case Code::undefined_definition: return "definition of C++ type is undefined";
			// case code::expected_curly_bracket:
			// case code::expected_flow_control:
			// case code::expected_in:
			// case code::expected_parameter_list:
			// case code::expected_regex:
			// case code::expected_declaration_statement:
			// case code::expected_import_statement:
			case Code::expected_command_end:
				return "expected command end, like a semicolon";
				// case code::expected_string:
				// case code::expected_while_statement:
				// case code::expected_whitespace:
				// case code::bad_for_statement:
				// case code::bad_function_statement:
				// case code::bad_identifier:
				// case code::bad_if_statement:
				// case code::bad_else_statement:
				// case code::bad_else_if_statement:
				// case code::bad_number:
				// case code::bad_operator:
			case Code::type_mismatch: return "type mismatch";
			case Code::not_boolean: return "expression is not boolean";
			case Code::symbol_already_declared: return "symbol already declared";
			case Code::symbol_not_a_type: return "symbol not a type";
			case Code::symbol_not_a_value: return "symbol not a value";
			case Code::symbol_immutable: return "symbol is not mutable";
			case Code::undefined_symbol: return "undefined symbol";
			case Code::type_not_truthable: return "type is not truthable";
			case Code::not_an_integral: return "type is not an integral";
			case Code::not_a_function: return "not a function";
			case Code::too_few_arguments: return "too few arguments in function call";
			case Code::too_many_arguments: return "too many arguments in function call";
			case Code::not_an_object: return "not an object";
			case Code::unsupported_operator: return "unsupported operator";
			case Code::symbol_defined_in_different_scope: return "symbol was defined in different scope";
			case Code::bad_opcode: return "bad opcode";
			// case code::bad_offset_option:
			// case code::bad_constant_option:
			// case code::bad_resource_option:
			// case code::bad_member_source_option:
			// case code::bad_member_destination_option:
			case Code::module_not_found: return "module was not found";
			case Code::bad_switch_value: return "a bad switch value";
			case Code::why_did_this_happen: return "How could this happen to me, I've made my mistakes";
			default: return "(unrecognized error code)";
			}
		}
	} category;
	return category;
}

inline const std::error_category& condition_category() noexcept
{
	static class : public std::error_category
	{
	public:
		const char* name() const noexcept override
		{
			return "bia";
		}
		std::string message(int condition) const override
		{
			switch (static_cast<Condition>(condition)) {
			case Condition::compiler: return "compilation error";
			default: return "(unrecognized error condition)";
			}
		}
		bool equivalent(const std::error_code& code, int condition) const noexcept override
		{
			switch (static_cast<Condition>(condition)) {
			case Condition::compiler: return code.value() >= 150 && code.value() < 200;
			default: return false;
			}
		}
	} category;
	return category;
}

inline std::error_code make_error_code(Code code) noexcept
{
	return { static_cast<int>(code), code_category() };
}

inline std::error_condition make_error_condition(Condition condition) noexcept
{
	return { static_cast<int>(condition), condition_category() };
}

} // namespace error
} // namespace bia

namespace std {

template<>
struct is_error_code_enum<bia::error::Code> : true_type
{};

template<>
struct is_error_condition_enum<bia::error::Condition> : true_type
{};

} // namespace std

#endif
