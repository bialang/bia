#ifndef BIA_ERROR_CODE_HPP_
#define BIA_ERROR_CODE_HPP_

#include <system_error>
#include <type_traits>

namespace bia {
namespace error {

enum class code
{
	success,

	bad_ascii,
	unfinished_utf_sequence,
	bad_utf_sequence,
	bad_unicode,

	out_of_stack,
	bad_narrowing,
	bad_cast,
	out_of_bounds,
	null_argument,
	argument_count_mismatch,
	bad_infix_operator,
	bad_test_operator,
	bad_self_operator,

	empty_variant,
	bad_variant_index,

	expected_opening_curly_bracket,
	expected_closing_curly_bracket,
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

	type_mismatch,
	symbol_already_declared,
	unknown_type,

	bad_opcode,
	bad_offset_option,
	bad_constant_option,
	bad_resource_option,
	bad_member_source_option,
	bad_member_destination_option,

	module_not_found,

	bad_switch_value,
	why_did_this_happen
};

inline const std::error_category& code_category() noexcept
{
	static class : public std::error_category
	{
	public:
		const char* name() const noexcept override
		{
			return "bia-errc";
		}
		std::string message(int ec) const override
		{
			switch (static_cast<code>(ec)) {
			case code::bad_ascii: return "bad ASCII code point value";
			case code::unfinished_utf_sequence: return "unfinished UTF sequence";
			case code::bad_utf_sequence: return "bad UTF sequence";
			case code::bad_unicode: return "bad Unicode code point value";
			case code::bad_narrowing: return "bad narrowing";
			case code::bad_cast: return "bad cast";
			case code::out_of_bounds: return "out of bounds";
			case code::null_argument: return "null argument not allowed";
			case code::argument_count_mismatch: return "argument count mismatch";
			case code::bad_infix_operator: return "bad infix operator";
			case code::bad_test_operator: return "bad test operator";
			case code::bad_self_operator: return "bad self operator";
			case code::empty_variant: return "accessing empty variant";
			case code::bad_variant_index: return "bad variant index";
			// case code::expected_curly_bracket:
			// case code::expected_flow_control:
			// case code::expected_in:
			// case code::expected_parameter_list:
			// case code::expected_regex:
			// case code::expected_declaration_statement:
			// case code::expected_import_statement:
			case code::expected_command_end: return "expected command end, like a semicolon";
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
			case code::bad_opcode: return "bad opcode";
			// case code::bad_offset_option:
			// case code::bad_constant_option:
			// case code::bad_resource_option:
			// case code::bad_member_source_option:
			// case code::bad_member_destination_option:
			case code::module_not_found: return "module was not found";
			case code::bad_switch_value: return "a bad switch value";
			case code::why_did_this_happen: return "this should not have happened";
			default: return "(unrecognized error code)";
			}
		}
	} category;

	return category;
}

inline std::error_code make_error_code(code c) noexcept
{
	return { static_cast<int>(c), code_category() };
}

} // namespace error
} // namespace bia

namespace std {
template<>
struct is_error_code_enum<bia::error::code> : true_type
{};
} // namespace std

#endif
