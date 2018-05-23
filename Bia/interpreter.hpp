#pragma once

#include "report_bundle.hpp"
#include "interpreter_id.hpp"
#include "interpreter_rule.hpp"
#include "input_stream.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief The interpreter for syntax.
 *
 * The Bia interpreter with rules.
 *
 * @see @ref interpreter_rule, @ref syntax
*/
class interpreter
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
	void set_rule(interpreter_rule && _rule);
	void interpret(stream::input_stream & _input, report_receiver & _receiver, machine::machine_context & _context) const;

private:
	/** All available rules. */
	interpreter_rule _rules[BGR_RULE_COUNT];
};

}
}