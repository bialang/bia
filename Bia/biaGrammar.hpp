#pragma once

#include "biaInterpreter.hpp"
#include "biaInterpreterTokens.hpp"
#include "biaInterpreterStringSet.hpp"
#include "biaInterpreterIdentifiers.hpp"


namespace bia
{
namespace grammar
{

class BiaGrammar
{
public:
	static const BiaInterpreter<BGR_RULE_COUNT> & GetGrammar();

private:
	static BiaInterpreter<BGR_RULE_COUNT> m_interpreter;


	static void InitializeRules();
};

}
}