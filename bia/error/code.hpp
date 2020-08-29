#ifndef BIA_ERROR_CODE_HPP_
#define BIA_ERROR_CODE_HPP_

#include <system_error>
#include <type_traits>

namespace bia {
namespace error {

enum class code
{
	bad_ascii = 1,
	unfinished_utf_sequence,
	bad_utf_sequence,
	bad_unicode,

	bad_narrowing,
	out_of_bounds,
	null_argument,
	argument_count_mismatch,
	bad_infix_operator,
	bad_test_operator,
	bad_self_operator,

	empty_variant,
	bad_variant_index,

	expected_curly_bracket,
	expected_flow_control,
	expected_in,
	expected_parameter_list,
	expected_regex,
	expected_declaration_statement,
	expected_import_statement,
	expected_command_end,
	expected_string,
	expected_while_statement,
	expected_whitespace,
	bad_for_statement,
	bad_function_statement,
	bad_identifier,
	bad_if_statement,
	bad_else_statement,
	bad_else_if_statement,
	bad_number,
	bad_operator,

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
			default: return "(unrecognized error code)";
			}
		}
	} category;

	return category;
}

inline std::error_code make_error_code(code c)
{
	return { static_cast<int>(c), code_category() };
}

} // namespace error
} // namespace bia

template<>
struct std::is_error_code_enum<bia::error::code> : std::true_type
{};

#endif
