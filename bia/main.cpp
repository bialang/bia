#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#include "bia.h"
#include "biaMemberHolderSize.h"
#include "resource.h"
#include "biaStreamBuffer.h"
#include "biaDisassembler.h"
#include "biaStdVector.h"
#include "biaNamespace.h"
#include "biaModule.h"


#define END system("pause"); return 0;

using namespace bia;
using namespace machine;
using namespace bia::api;
using namespace bia::api::framework;

int fac = 6161;


struct Printer
{
	Printer(const short & r)
	{
		buf = nullptr;
		//buf = new char[10000];
		factor = r;
		printf("constructed%i\n", factor);
	}
	Printer(const Printer &)
	{
		buf = nullptr;
		factor = 23;
		printf("copy constructed%i\n", factor);
	}
	Printer(Printer &&)
	{
		buf = nullptr;
		factor = 23;
		printf("move constructed%i\n", factor);
	}
	~Printer()
	{
		//delete[] buf;
		std::cout << "destructed" << factor<< std::endl;
	}
	void PrintNothing(int &i) const
	{
	//	printf("hellad ad akdj \n");
		std::cout << "My parameter is: " << i << "\n";
		std::cout << "Hello, I print nothing except for: " << (factor * i) << std::endl;


		i *= factor;

		//return /*i / */factor;
	}
	int operator+(const Printer & right)
	{
		return factor + right.factor;
	}
	void operator+=(const Printer & p_r)
	{
		factor += p_r.factor;
	}
	int& DoNot()
	{
		std::cout << "Hello, I do not do anything." << std::endl;

		return factor;
	}
	Printer &Print0()
	{
		std::cout << "Jo, I am printing 0" << std::endl;

		return *this;
	}
	void Print1() const
	{
		std::cout << "Jo, I am printing 1 and my factor " << fac << std::endl;
	}
	std::string * Modify(std::string & p_ststring)
	{
		std::cout << "Modifying: " << p_ststring << std::endl;
		p_ststring = "modkkkkkkkkkkkkkified";

		return &p_ststring;
	}

	char * buf;
	int factor;
};

using namespace std::string_literals;


std::string JustPrint(const char * lol)
{
	std::cout << "I am just printing something." << lol << std::endl;

	return "yunus";
}

inline std::string Input()
{
	/*if (p_pszInput)
	{
		auto iSize = std::char_traits<char>::length(p_pszInput);

		if (iSize)
			fwrite(p_pszInput, iSize, 1, stdout);
	}*/

	std::string stInput;

	std::getline(std::cin >> std::ws, stInput);

	return stInput;
}

void HeyCallback(std::string(*p)(const char*))
{
	p("Hey callback");
}

namespace std
{
template<typename T>
constexpr T copy(T & p_value)
{
	return T(p_value);
}
}

BIA_MODULE_DEFINE_SPECIFIC(test)
p_pOutput->Initialize<BiaNamespace>();

BiaNamespace * m = static_cast<BiaNamespace*>(p_pOutput->GetMember());

m->AddFunction("now", [] {
	return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
});
m->AddFunction("hi", [] { puts("Hihihi"); });
BIA_MODULE_DEFINE_END(test)

#include "biaCompiler.h"
#include "biaInterpreter.h"

int main(int argc, char ** argv)
{
	stream::BiaStreamBuffer cc;

	char tetea[] = "var test = 100;";
	
	grammar::InitializeRules().Interpret(tetea, sizeof(tetea) - 1, compiler::BiaCompiler(cc));

	constexpr char NOT[21]{};

	cc.Write(&NOT, sizeof(NOT));

	debug::BiaDisassembler::DisassembleByteCode(cc.GetByteStream());

	END

	Bia::Initialize();
	
	/*
	Operator precedence:

	1)	*	/	//	%
	2)	+	-
	3)	&	|	^	<<	>>	>>>
	4)	<	>	==	!=	<=	>=
	5)	=

	custom_op ::= ("+" | "-" | "&" | "|" | "^" | "<" | ">" | "°" | "§" | "$" | "#")+

	*/
	printf("MemberHolder size must be: %zi\n\n", BIA_MEMBER_HOLDER_SIZE_MIN);

	auto bCompileEnd = true;
	char testCode[] = u8R"(

var i = new Printer(23);
var j = new Printer(77);

j + i;
print j.DoNot();
)";
	//setvbuf(stdout, nullptr, _IOFBF, 10000024 * 4);
	{
		BiaMachineContext context;

		std::shared_ptr<object::BiaClassWrapperBase> asd((new object::BiaClassWrapper<Printer>())
			->AddConstructor<short>()
			->SetFunction("PrintNothing"s, &Printer::PrintNothing)
			->SetFunction("DoNot", &Printer::DoNot)
			->SetFunction("lol", [] {puts("just printing lol. lol");})
			->SetSMFunction("sm", [](Printer * pThis) { printf("Your factor is %i\n", pThis->factor); })
			->SetFunction("Print0", &Printer::Print0)
			->SetFunction("Print1", &Printer::Print1)
			->SetOperator(BiaMember::O_PLUS, std::unique_ptr<object::BiaClassOperatorBase>(new object::BiaClassOperator<Printer, const Printer &, void>(&Printer::operator+=)))
		);


		//Add templates
		context.GetTemplateTable().AddTemplate("Printer", asd);
		context.GetTemplateTable().AddTemplate("vector", standard::CreateStandardVector<std::string>());
		
		//Add global functions
		context.SetFunction("JustPrint", JustPrint);
		context.SetFunction("HeyCallback", HeyCallback);
		context.SetFunction("exit", [] { exit(0); });
		context.SetFunction("input", Input);
		context.SetFunction("print", [](const std::string & str) { printf(str.c_str()); });
		context.SetFunction("system", [](const char * p_pszCmd) { return system(p_pszCmd); });

#ifdef _DEBUG
#define TMP "Debug"
#else
#define TMP "Release"
#endif

		context.SetFunction("version", [] { puts("Bia Version: 2.37.78.454 (" TMP ")"); });
#undef TMP

		//Add modules
		context.GetModuleHandler().SetSpecific("test", "", ___BiaModuleDefinition_test);
		
		//
		if (argc > 1)
		{
			FILE * pFile = nullptr;

			if (!fopen_s(&pFile, argv[1], "rb"))
			{
				fseek(pFile, 0, SEEK_END);
				auto size = ftell(pFile);
				std::unique_ptr<char[]> pBuffer(new char[size]);
				rewind(pFile);
				fread_s(pBuffer.get(), size, 1, size, pFile);

				try
				{
					stream::BiaStreamBuffer compiledScript;
					
					Bia::Compile(pBuffer.get(), size, compiledScript);

					auto code = compiledScript.GetByteStream();
					debug::BiaDisassembler::DisassembleByteCode(code);
					
					for (auto o = code.pcByteCode; o < code.pcByteCodeEnd; ++o)
					{
						printf("%02x", static_cast<unsigned int>(*o));
					}

					puts("\n\n===================OUTPUT========================");

					context.Execute(code);
				}
				catch (const bia::exception::Exception & e)
				{
					e.Print();
				}
				catch (const std::exception & e)
				{
					puts(e.what());
				}
				catch (...)
				{
					puts("Some other error.");
				}

				fclose(pFile);

				puts("===================OUTPUT========================\n");
				system("pause");

				return 0;
			}
		}
		else if (bCompileEnd)
		{
			try
			{
				stream::BiaStreamBuffer compiledScript;

				Bia::Compile(testCode, sizeof(testCode) - 1, compiledScript);

				auto code = compiledScript.GetByteStream();
				debug::BiaDisassembler::DisassembleByteCode(code);

				for (auto o = code.pcByteCode; o < code.pcByteCodeEnd; ++o)
				{
					printf("%02x", static_cast<unsigned int>(*o));
				}

				puts("\n\n===================OUTPUT========================");

				context.Execute(code);
			}
			catch (const bia::exception::Exception & e)
			{
				e.Print();
			}
			catch (const std::exception & e)
			{
				puts(e.what());
			}
			catch (...)
			{
				puts("Some other error.");
			}
			puts("===================OUTPUT========================\n");

			context.ClearScope();

			END
		}

		std::string stCode;

		for (auto i= 0; true;++i)
		{
			std::cout << ">>>";
			
			auto bFirst = true;
			stCode.clear();
			
			while (true)
			{
				std::string stLine;
				std::getline(std::cin, stLine);
			
				stCode.append(stLine);
			
				if (!stLine.empty())
				{
					if ((stLine.back() == ';' && bFirst) || stLine.back() == '}')
						break;
				}

				std::cout << "...";
				bFirst = false;
			}

			//Compile
			try
			{
				stream::BiaStreamBuffer compiledScript;

				if (!Bia::Compile(stCode.c_str(), stCode.length(), compiledScript))
					continue;

				//Run
				auto code = compiledScript.GetByteStream();
				
				debug::BiaDisassembler::DisassembleByteCode(code);

				for (auto o = code.pcByteCode; o < code.pcByteCodeEnd; ++o)
				{
					printf("%02x", static_cast<unsigned int>(*o));
				}

				puts("\n\n===================OUTPUT========================");

				context.Execute(code);
			}
			catch (const bia::exception::Exception & e)
			{
				e.Print();
			}
			catch (const std::exception & e)
			{
				puts(e.what());
			}
			catch (...)
			{
				puts("Some other error.");
			}

			puts("===================OUTPUT========================\n");
			//exit
			try
			{
				if (Conditional(context.GetMember("exit_now")))
					Execute(context, context.GetMember("exit"));
			}
			catch (const exception::Exception&)
			{
			}

			puts("");
		}

		return 0;
	}

	system("pause");
}