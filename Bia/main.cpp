#include "biaMachineCode.hpp"
#include "biaOutputStreamBuffer.hpp"
#include "biaToolset.hpp"

#include "biaGrammar.hpp"
#include "biaCompiler.hpp"

void hi(int val, int a)
{
	printf("say hi to val %i\n", val);
}

int main()
{
	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;
//var i = 65*65+5*8;
	char script[] = R"(
	var i = 65*5+5*8+9*46/3*5598+239488278/2+5-514;
var o = i;
print o;
)";
	/*{
		bia::machine::architecture::BiaToolset toolset(buf);
		toolset.SafeCall(&hi, 34, 5);
	}*/
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