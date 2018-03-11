#pragma once

#include "biaReportBundle.hpp"
#include "biaInterpreterRule.hpp"


namespace bia
{
namespace grammar
{

template<Report::rule_id _RULES>
class BiaInterpreter
{
public:
	inline BiaInterpreter() = default;
	inline BiaInterpreter(void(*p_pInitializerFunction)())
	{
		p_pInitializerFunction();
	}
	/**
	 * Sets a rule.
	 *
	 * @since	2.39.81.472
	 * @date	10-Sep-17
	 *
	 * @param	p_iRuleId	Defines the id of the rule.
	 * @param	p_rule	Defines the rule.
	 *
	 * @throws	bia::exception::ImplementationException	Thrown when the rule id is invalid.
	*/
	inline void SetRule(Report::rule_id p_iRuleId, BiaInterpreterRule p_rule)
	{
		if (p_iRuleId < _RULES)
			m_aRules[p_iRuleId] = std::move(p_rule);
		else
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid rule id.");
	}
	inline size_t Interpret(const char * p_pcBuffer, size_t p_iSize, BiaReportReceiver & p_receiver) const
	{
		const auto ciSize = p_iSize;
		BiaReportBundle bundle;

		//Interpretation loop
		while (p_iSize)
		{
			bundle.Clear();

			//Remove leading whitespace
			{
				TokenOutput output{};

				WhitespaceDeleter<STARTING_PADDING_OPTIONAL_TOKEN, true>(p_pcBuffer, p_iSize, output);
			}

			//Start with rule 0
			auto iSize = m_aRules[0].RunRule(p_pcBuffer, p_iSize, { &bundle, m_aRules, 0 });

			//Report
			if (iSize)
			{
				p_receiver.Report(bundle.Begin(), bundle.End());

				p_pcBuffer += iSize;
				p_iSize -= iSize;
			}
			else
				break;
		}

		puts(p_pcBuffer);

		return ciSize - p_iSize;
	}
	/**
	 * Gets the rule.
	 *
	 * @since	2.39.81.472
	 * @date	10-Sep-17
	 *
	 * @param	p_iRuleId	Defines the id of the rule.
	 *
	 * @throws	bia::exception::ImplementationException	Thrown when the rule id is invalid.
	 *
	 * @return	The rule.
	*/
	inline BiaInterpreterRule & GetRule(Report::rule_id p_iRuleId)
	{
		if (p_iRuleId < _RULES)
			return m_aRules[p_iRuleId];
		else
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid rule id.");
	}

private:
	mutable BiaInterpreterRule m_aRules[_RULES];
};

}
}