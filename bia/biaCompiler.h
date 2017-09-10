#pragma once

#include "biaGrammar.h"
#include "biaReportBundle.h"


namespace bia
{
namespace api
{
namespace compiler
{

class BiaCompiler : public grammar::BiaReportReceiver
{
public:
	inline virtual void Report(const grammar::BiaReportBundle & p_bundle) override
	{
		for (auto i = p_bundle.Begin(), cond = p_bundle.End(); i < cond; ++i)
		{
			fwrite(i->pcString, 1, i->iSize, stdout);
			printf(" id: %zi rule: %zi\n", i->iTokenId, i->iRuleId);
		}
	}
};

}
}
}