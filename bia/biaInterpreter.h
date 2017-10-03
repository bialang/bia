#pragma once

#include "biaReportBundle.h"
#include "biaInterpreterRule.h"


namespace bia
{
namespace api
{
namespace grammar
{

template<uint32_t _RULES>
class BiaInterpreter
{
public:
	/**
	 * Sets a rule.
	 *
	 * @since	2.39.81.472
	 * @date	10-Sep-17
	 *
	 * @param	p_nRuleId	Defines the id of the rule.
	 * @param	p_rule	Defines the rule.
	*/
	inline void SetRule(uint32_t p_unRuleId, BiaInterpreterRule p_rule)
	{
		if (p_unRuleId < _RULES)
			m_aRules[p_unRuleId] = std::move(p_rule);
		else
			throw exception::ImplementationException("Invalid rule id.");
	}
	inline size_t Interpret(const char * p_pcBuffer, size_t p_iSize, BiaReportReceiver & p_receiver)
	{
		const auto ciSize = p_iSize;
		BiaReportBundle bundle;

		//Interpretation loop
		while (p_iSize)
		{
			bundle.Clear();

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

		return ciSize - p_iSize;
	}
	/**
	 * Gets the rule.
	 *
	 * @since	2.39.81.472
	 * @date	10-Sep-17
	 *
	 * @param	p_unRuleId	Defines the id of the rule.
	 *
	 * @return	The rule.
	*/
	inline BiaInterpreterRule & GetRule(uint32_t p_unRuleId)
	{
		if (p_unRuleId < _RULES)
			return m_aRules[p_unRuleId];
		else
			throw exception::UnknownException("Invalid rule id.");
	}

private:
	BiaInterpreterRule m_aRules[_RULES];
};

}
}
}