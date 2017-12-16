#include "biaMachineContext.hpp"
#include "biaOutputStreamBuffer.hpp"

#include <memory>
#include <cstdint>


namespace bia
{
namespace machine
{

void BiaMachineContext::Run(stream::BiaInputStream & p_input)
{
	uint8_t aucSpace[sizeof(BiaMachineCode)];
	std::unique_ptr<BiaMachineCode> pMachineCode;

	{
		//Compile
		stream::BiaOutputStreamBuffer compiled;

		//Make the compiled buffer executable
		pMachineCode.reset(new(aucSpace) BiaMachineCode(compiled.GetBuffer()), [](BiaMachineCode * p_pCode) {
			p_pCode->~BiaMachineCode();
		});
	}

	//Execute script
	if (pMachineCode->IsValid())
		pMachineCode->Execute();
}

}
}