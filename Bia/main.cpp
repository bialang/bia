#include "biaMachineCode.hpp"
#include "biaOutputStreamBuffer.hpp"

#include "biaGrammar.hpp"
#include "biaCompiler.hpp"
#include <iostream>
int main()
{
	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;
	
	char script[] = R"(
	print 2 * (4 + 7)*5*5.5;
)";
	
	//bia::compiler::OperationResult<int, double>::type;

	try
	{
		bia::compiler::BiaCompiler compiler(buf, context);

		bia::grammar::InitializeRules().Interpret(script, sizeof(script) - 1, compiler);
	}
	catch (bia::exception::Exception & e)
	{
		e.Print();

		system("pause");

		return 1;
	}

	printf("address: %p\n", &context);

	bia::machine::BiaMachineCode code(buf.GetBuffer());

	auto buffer = buf.GetBuffer();
	int t = 0;

	while (buffer.second--)
	{
		printf("%02hhx ", *buffer.first++);

		if (++t == 10)
		{
			puts("");
			t =0 ;
		}
	}

	if (t != 0)
	{
		puts("");
	}
	system("pause");
	code.Execute();

	system("pause");
}