#pragma once

#include <cstdint>
#include <vector>

#include "report_bundle.hpp"
#include "input_stream.hpp"


namespace bia
{
namespace grammar
{

struct flags
{
	typedef uint64_t flag_type;
	constexpr static flag_type none = 0;
	constexpr static flag_type filler_token = 0x1;
	constexpr static flag_type opt_token = 0x2;
	constexpr static flag_type looping_token = 0x4;
	constexpr static flag_type starting_ws_token = 0x8;
	constexpr static flag_type starting_ws_opt_token = 0x10;
	constexpr static flag_type ending_ws_token = 0x20;
	constexpr static flag_type starting_padding_token = 0x40;
	constexpr static flag_type starting_padding_opt_token = 0x80;
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
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	*/
	interpreter_rule() noexcept;
	/**
	 * Constructor.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	_id	Defines the id of this rule.
	 * @param	_flags	Defines the flags.
	 * @param	[in]	_tokens	Defines the tokens for this rule.
	*/
	interpreter_rule(report::rule_type _id, uint32_t _flags, std::vector<bia_token_function> && _tokens) noexcept;
	/**
	 * Runs this rule.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_pcBuffer	Defines a buffer which this rule should be run on.
	 * @param	p_iSize	Defines the size of the buffer.
	 * @param	p_params	Defines parameters for the token functions.
	 *
	 * @return	The amount of bytes processed of the buffer.
	*/
	void run_rule(stream::input_stream & _input, token_param _token_param) const;
	report::rule_type get_id() const;

private:
	/**	Defines the id of this rule.	*/
	report::rule_type _id;
	/**	Defines the flags set for this rule.	*/
	uint32_t _flags;
	/**	Holds all tokens for this rule.	*/
	std::vector<bia_token_function> _tokens;


	void begin_wrap_up(token_param _token_param) const;
};

}
}