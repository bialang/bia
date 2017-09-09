#pragma once

#include "biaInterpreterRule.h"


namespace bia
{
namespace api
{
namespace grammar
{
constexpr size_t _RULES = 3;
//template<size_t _RULES>
class BiaInterpreter
{
public:
	inline void SetRule(size_t p_iRuleId, BiaInterpreterRule p_rule)
	{
		if (p_iRuleId < _RULES)
			m_aRules[p_iRuleId] = std::move(p_rule);
		else
			throw exception::UnknownException("Invalid rule id.");
	}
	inline size_t Interpret(const char * p_pcBuffer, size_t p_iSize)
	{
		const auto ciSize = p_iSize;

		//Interpretation loop
		while (p_iSize)
		{
			//Start with rule 0
			auto iSize = RunRule(m_aRules[0], p_pcBuffer, p_iSize);

			//Report
			if (iSize)
			{

				p_pcBuffer += iSize;
				p_iSize -= iSize;
			}
			else
				break;
		}

		return ciSize - p_iSize;
	}
	inline BiaInterpreterRule & GetRule(size_t p_iRuleId)
	{
		if (p_iRuleId < _RULES)
			return m_aRules[p_iRuleId];
		else
			throw exception::UnknownException("Invalid rule id.");
	}

private:
	BiaInterpreterRule m_aRules[_RULES];

	inline static size_t RunRule(BiaInterpreterRule & p_rule, const char * p_pcBuffer, size_t p_iSize)
	{
		const auto ciSize = p_iSize;

		p_rule.Reset();

		while (p_rule.NotFinished())
		{
			size_t iTokenSize = 0;

			switch (p_rule.Next()(p_pcBuffer, p_iSize, iTokenSize))
			{
			case ACTION::ACCEPT:
			case ACTION::IGNORE:
				p_pcBuffer += iTokenSize;
				p_iSize -= iTokenSize;

				break;
			case ACTION::REJECT:
				return 0;
			}
		}

		return ciSize - p_iSize;
	}
};

}
}
}