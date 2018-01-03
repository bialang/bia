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

int main()
{
	uint64_t p_ullInstruction = 0x691234;
	//Rotate instruction
	/*for (uint8_t i = 1; i < 3; ++i)
		p_ullInstruction = (p_ullInstruction >> 8 & 0xffffff) | p_ullInstruction << 3 * 8 - 8;
		//p_ullInstruction = p_ullInstruction << i * 8 | (p_ullInstruction >> 3 * 8 - 8 & 0xff);

	p_ullInstruction &= ~(~0ull << 3 * 8);*/

	p_ullInstruction =	_byteswap_uint64(p_ullInstruction);
	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;
//var i = 65*65+5*8;
	char script[] = R"(
	var i = 2*2*2;
print i*i;
)";

	/*{
		bia::machine::architecture::BiaToolset toolset(buf);
		toolset.SafeCall(&hi, 34, 5);
		toolset.SafeCall(&bia::machine::BiaMachineContext::AllocateTemporaryAddresses, &context, (bia::framework::BiaMember**)0, (int8_t)8);
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