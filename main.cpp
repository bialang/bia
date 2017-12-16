#include "biaMachineCode.hpp"
#include "biaToolGcc.hpp"
#include "biaOutputStreamBuffer.hpp"

void hello_world(void*p)
{
	printf("Hello, World! %p\n", p);
}

int main()
{
	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;

	printf("address: %p\n", &context);

	bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86>::Initialize(buf, &context);
	bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86>::Call(buf, reinterpret_cast<const void*>(hello_world));
	bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86>::Call(buf, reinterpret_cast<const void*>(&bia::machine::BiaMachineContext::hello_world));
	bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86>::Finalize(buf);

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

	code.Execute();
}