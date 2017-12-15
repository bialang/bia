#include "biaMachineCode.h"
#include "biaToolGcc.h"
#include "biaStreamBuffer.h"

void hello_world(void*)
{
	puts("Hello, World!");
}

int main()
{
	bia::stream::BiaStreamBuffer buf;

	bia::machine::architecture::BiaToolGcc<bia::machine::architecture::Biax86>::Call(buf, nullptr, hello_world);

	bia::machine::BiaMachineCode code(buf.GetByteStream());

	code.Execute(nullptr);
}