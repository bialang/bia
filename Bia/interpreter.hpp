#pragma once

#include "report_bundle.hpp"
#include "interpreter_ids.hpp"
#include "interpreter_rule.hpp"


namespace bia
{
namespace grammar
{

class interpreter
{
public:
	/**
	 * Sets a rule.
	 *
	 * @since	2.39.81.472
	 * @date	10-Sep-17
	 *
	 * @param	p_iRuleId	Defines the id of the rule.
	 * @param	p_rule	Defines the rule.
	*/
	void set_rule(report::rule_type _rule_id, interpreter_rule && _rule);
	size_t interpret(const char * _buffer, size_t _length, report_receiver & _receiver) const;

private:
	interpreter_rule _rules[BGR_RULE_COUNT];
};

}
}