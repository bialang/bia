#pragma once

#include <cstdint>
#include <vector>

#include "report_bundle.hpp"
#include "input_stream.hpp"


namespace bia
{
namespace grammar
{

/**
 * Flags used for token specialization.
*/
struct flags
{
	typedef uint64_t flag_type;

	/** No flag. */
	constexpr static flag_type none = 0;
	/** The token will not be reported. */
	constexpr static flag_type filler_token = 0x1;
	/** The token is optional. */
	constexpr static flag_type opt_token = 0x2;
	/** The token will be looped and is optional. */
	constexpr static flag_type looping_token = 0x4;
	/** At least one whitespace character at the beginning is required. */
	constexpr static flag_type starting_ws_token = 0x8;
	/** Whitespace at the beginning is optional. */
	constexpr static flag_type starting_ws_opt_token = 0x10;
	/** At least one whitespace character at the end is required. */
	constexpr static flag_type ending_ws_token = 0x20;
	/** Whitespace at the end is optional. */
	constexpr static flag_type ending_ws_opt_token = 0x40;
	constexpr static flag_type starting_padding_token = 0x80;
	constexpr static flag_type starting_padding_opt_token = 0x100;
};

enum class ACTION
{
	REPORT,
	DONT_REPORT,
	REPORT_AND_LOOP,
	DONT_REPORT_AND_LOOP,
	ERROR
};

class interpreter_rule;

struct token_param
{
	report_bundle * bundle;
	const interpreter_rule * rules;
	report::token_type token_id;
};

struct token_output
{
	report content;
	report::custom_type custom;
};

typedef ACTION(*bia_token_function)(stream::input_stream&, token_param, token_output&);

/**
 * A rule for the grammar.
*/
class interpreter_rule
{
public:
	enum FLAGS : uint32_t
	{
		F_NONE = 0,
		F_OR = 0x1,
		F_WRAP_UP = 0x2,
		F_DONT_REPORT_EMPTY = 0x4
	};


	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	*/
	interpreter_rule() noexcept;
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _id The id of this rule.
	 * @param _flags The flags.
	 * @param [in] _tokens The tokens for this rule.
	*/
	interpreter_rule(report::rule_type _id, uint32_t _flags, std::vector<bia_token_function> && _tokens) noexcept;
	/**
	 * Runs this rule. If this function fails, the input stream will be resetted to its original position.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @param [in] _input The input stream.
	 * @param _token_param Token parameter for this rule.
	 *
	 * @return true if it succeeded, otherwise false.
	 *
	 * @throws
	*/
	bool run_rule(stream::input_stream & _input, token_param _token_param) const;
	/**
	 * Returns the id of this rule.
	 *
	 * @since 3.64.127.716
	 * @date 16-Apr-18
	 *
	 * @return The id.
	*/
	report::rule_type get_id() const noexcept;

private:
	/** The id of this rule. */
	report::rule_type _id;
	/** Specialization flags. */
	uint32_t _flags;
	/** Holds all tokens for this rule. */
	std::vector<bia_token_function> _tokens;


	/**
	 * Adds the beginning of a wrap up if required.
	 *
	 * @since 3.64.127.716
	 * @date 16-Apr-18
	 *
	 * @param _token_param The parameter.
	*/
	void begin_wrap_up(token_param _token_param) const;
};

}
}