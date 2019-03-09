#pragma once

#include "config.hpp"
#include "report_bundle.hpp"
#include "keyword.hpp"
#include "grammar_id.hpp"
#include "grammar_rule.hpp"
#include "buffer_input_stream.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief The lexographical analyzer for the syntax.
 *
 * @see @ref grammar_rule, @ref syntax
*/
class lexer
{
public:
	/**
	 * Sets a rule.
	 *
	 * @since 2.39.81.472
	 * @date 10-Sep-17
	 *
	 * @param _rule Defines the rule.
	*/
	BIA_EXPORT void set_rule(grammar_rule && _rule);
	BIA_EXPORT void lex(stream::buffer_input_stream & _input, report_receiver & _receiver, machine::machine_context & _context) const;

private:
	/** All available rules. */
	grammar_rule _rules[BGR_RULE_COUNT];
};

}
}