#include "biaMachineCode.hpp"
#include "biaOutputStreamBuffer.hpp"
#include "biaToolset.hpp"

#include "biaGrammar.hpp"
#include "biaCompiler.hpp"
#include "biaMachineDecoder.hpp"

void hi(int val, int a)
{
	printf("say hi to val %i\n", val);
}

struct a
{
	virtual void da(int p)
	{
		printf("hi from a at %p to %i\n", this, p);
	}
};

struct b : a
{
	virtual void da(int p) override
	{
		printf("hi from b at %p to %i\n", this, p);
	}
};

int main()
{
	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;
//var i = 65*65+5*8;
	char script[] = R"(
	var i = 2*2*2;
var o = 2;
print i*o;
)";

	a * ptr = new a();
	printf("ad: %p\n", ptr);

	/*{
		bia::machine::architecture::BiaToolset toolset(buf);
		toolset.SafeCall(&hi, 34, 5);
		toolset.SafeCall(&a::da, ptr, 376);
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

	puts("--BEGIN--");
	buffer = buf.GetBuffer();
	bia::machine::disassembler::BiaMachineDecoder decoder(&context, context.m_index);
	decoder.Disassemble(buffer.first, buffer.second);
	puts("--END--");

	
	system("pause");

	try
	{
		code.Execute();
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
		puts("Something was thrown");
	}
	system("pause");
}