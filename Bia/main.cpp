#include "biaMachineCode.hpp"
#include "biaToolGcc.hpp"
#include "biaOutputStreamBuffer.hpp"

#include "biaGrammar.hpp"
#include "biaCompiler.hpp"

void hello_world(unsigned long long c, void*p)
{
	printf("Hello, %llu! %p\n", c, p);
	
}


int main()
{
	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;
	
	char script[] = R"(
	var i = 2 * 4 + 7*5*5;
)";
	{
		bia::compiler::BiaCompiler<bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86>> compiler(buf, context);

		bia::grammar::InitializeRules().Interpret(script, sizeof(script) - 1, compiler);
	}

	printf("address: %p\n", &context);
	
	/*{
		bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86> toolset(buf, context);

		toolset.PushParameter(6542ull);
		toolset.Call(reinterpret_cast<const void*>(hello_world));

		toolset.Call(reinterpret_cast<const void*>(hello_world));

		toolset.PopParameters();
	}*/

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