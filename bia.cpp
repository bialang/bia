#include "bia.hpp"
#include "biaGrammar.hpp"
#include "biaCompiler.hpp"

#include <Windows.h>


namespace bia
{

void Bia::Initialize()
{
	SetConsoleOutputCP(CP_UTF8);

//	api::grammar::BiaGrammar::InitializeGrammar();
}

void Bia::Finalize()
{
}

bool Bia::Compile(const char * p_pcCode, size_t p_iSize, stream::BiaStream & p_compiled)
{
	if (p_pcCode && p_iSize)
	{
		p_compiled.Reserve(p_iSize * 2 + 20);

		//api::compiler::BiaCompiler compiler(p_compiled);

		//ycode code = "";
		//code.PointTo(p_pcCode, p_iSize);

		//if (api::grammar::BiaGrammar::sBiaGrammar.Interpret(api::grammar::BGI_R_ROOT, &compiler, code))
		{
			//Add terminate
			constexpr machine::OP terminator[21] = { machine::OP::TERMINATE };

			p_compiled.Write(&terminator, sizeof(terminator));

			return true;
		}
	}

	return false;
}

}