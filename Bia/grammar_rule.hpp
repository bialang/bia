#pragma once

#include <cstdint>
#include <vector>

#include "config.hpp"
#include "report_bundle.hpp"
#include "buffer_input_stream.hpp"
#include "machine_context.hpp"
#include "virtual_machine_schein.hpp"
#include "encoder.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief Flags used for token specialization.
*/
struct flags
{
	/** The flag type. */
	typedef uint64_t flag_t;

	/** No flag. */
	constexpr static flag_t none = 0;
	/** The token will not be reported. */
	constexpr static flag_t filler_token = 0x1;
	/** The token is optional. */
	constexpr static flag_t opt_token = 0x2;
	/** The token will be looped and is optional. */
	constexpr static flag_t looping_token = 0x4;
	/** At least one whitespace character at the beginning is required. */
	constexpr static flag_t starting_ws_token = 0x8;
	/** Whitespace at the beginning is optional. */
	constexpr static flag_t starting_ws_opt_token = 0x10;
	/** At least one whitespace character at the end is required. */
	constexpr static flag_t ending_ws_token = 0x20;
	/** Whitespace at the end is optional. */
	constexpr static flag_t ending_ws_opt_token = 0x40;
	constexpr static flag_t starting_padding_token = 0x80;
	constexpr static flag_t starting_padding_opt_token = 0x100;
};

/** The result of a token. */
enum class ACTION
{
	REPORT,
	DONT_REPORT,
	REPORT_AND_LOOP,
	DONT_REPORT_AND_LOOP,
	ERROR
};

class grammar_rule;

/**
 * @brief Additional token parameters.
*/
struct token_param
{
	/** The output report bundle. */
	report_bundle * bundle;
	/** The available rules. */
	const grammar_rule * rules;
	/** The current token id. */
	report::token_t token_id;
	/** The corresponding machine context. */
	machine::machine_context * context;
	/** The schein of the resulting code. */
	machine::virtual_machine::virtual_machine_schein schein;
	/** The decoder for the input stream. */
	encoding::encoder * encoder;

	explicit token_param(machine::machine_context & _context) : schein(_context.allocator(), _context.executable_allocator(), _context.big_int_allocator())
	{
		context = &_context;
	}
};

typedef report token_output;

/** The interper token signature. */
typedef ACTION(*bia_token_function)(stream::buffer_input_stream&, token_param&, token_output&);

/**
 * A rule for the grammar.
*/
class grammar_rule
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
	BIA_EXPORT grammar_rule() noexcept;
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
	BIA_EXPORT grammar_rule(report::rule_t _id, uint32_t _flags, std::vector<bia_token_function> && _tokens) noexcept;
	/**
	 * Runs this rule. If this function fails, the input stream will be resetted to its original position.
	 *
	 * @since 2.39.82.486
	 * @date 16-Sep-17
	 *
	 * @param [in] _input The input stream.
	 * @param [in] _token_param Token parameter for this rule.
	 *
	 * @return true if it succeeded, otherwise false.
	 *
	 * @throws
	*/
	BIA_EXPORT bool run(stream::buffer_input_stream & _input, token_param & _token_param) const;
	/**
	 * Returns the id of this rule.
	 *
	 * @since 3.64.127.716
	 * @date 16-Apr-18
	 *
	 * @return The id.
	*/
	BIA_EXPORT report::rule_t id() const noexcept;

private:
	/** The id of this rule. */
	report::rule_t _id;
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
	 * @param [in] _token_param The parameter.
	*/
	BIA_EXPORT void begin_wrap_up(token_param & _token_param) const;
};

}
}