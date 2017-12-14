//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <map>
#include <sstream>

#include <iostream>
#include <string>
#include <fstream>

void System(const std::string & p_stCommand)
{
	system(p_stCommand.c_str());
}

bool g_bReport = false;
std::map<ptrdiff_t, std::size_t> g_vAllocations;

void * operator new(
	_In_   size_t      _Size,
	_In_   int         _BlockUse,
	_In_z_ char const* _FileName,
	_In_   int         _LineNumber
	) throw(std::bad_alloc)
{
	auto n = _Size;
	auto p = malloc(n);

	if (g_bReport)
	{
		printf("New allocation of %zi bytes at %p in line %i.\n", n, p, _LineNumber);

		g_bReport = false;
		if (g_vAllocations.find(reinterpret_cast<ptrdiff_t>(p)) != g_vAllocations.end())
			printf("Duplicate allocation.\n\n");
		g_vAllocations[reinterpret_cast<ptrdiff_t>(p)] = n;
		g_bReport = true;
	}

	return p;
}
void operator delete(void * p)
{
	if (p)
	{
		if (g_bReport)
		{
			printf("Deleteing %p.\n", p);

			g_bReport = false;
			if (g_vAllocations.find(reinterpret_cast<ptrdiff_t>(p)) == g_vAllocations.end())
				printf("Deleting non-mapped allocation.\n\n");
			else
				g_vAllocations.erase(reinterpret_cast<ptrdiff_t>(p));
			g_bReport = true;
		}

		free(p);
	}
}

#ifdef _DEBUG
#ifndef DBG_NEW
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new(x) new(x, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif  // _DEBUG

#include "bia.h"
#include "biaClass.h"
#include "biaDisassembler.h"

void PrintRestAllocations()
{
	for each(auto & allocation in g_vAllocations)
		printf("Non deleted allocation at %#x with %zi.\n", allocation.first, allocation.second);
}


int main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
	{
		bia::Bia::Initialize();

		auto code = u8R"bia(

print "Wieso?";

)bia";

		std::stringstream compiledFile;

		bia::BiaInterpreter::Compile(code, std::char_traits<char>::length(code), compiledFile);

		compiledFile.clear();
		compiledFile.seekg(0);

		bia::machine::debug::BiaDisassembler::DisassembleByteCode(compiledFile);

		auto pContext = bia::machine::BiaMachineSettings().CreateNewContext();
		//g_bReport = false;
		pContext->GetLocalScope().global.AddFunction("system", System);

		//bia::machine::BiaMachineSettings().CreateNewContext()->GetLocalScope().global.AddFunction("system", System);
		g_bReport = true;
		bia::machine::BiaMachine machine;
		compiledFile.clear();
		compiledFile.seekg(0, std::ios::end);
		auto size = compiledFile.tellg();
		auto buffer = new char[size];
		compiledFile.clear();
		compiledFile.seekg(0);
		compiledFile.read(buffer, size);

		bia::BiaByteStream compiled(buffer, size);
		new char[61];
		try
		{
			machine.Execute(compiled, *pContext);
		}
		catch (const bia::exception::Exception & e)
		{
			e.Print();
		}
		delete[] buffer;

		g_bReport = false;
		bia::Bia::Finalize();
	}
		_CrtDumpMemoryLeaks();


	system("pause");
}