#pragma once

#include <cstdint>
#include <type_traits>

#include "biaMachineContext.h"
#include "biaArchitecture.h"
#include "biax86.h"
#include "biaStream.h"


namespace bia
{
namespace machine
{
namespace architecture
{

template<typename _ARCHITECTURE>
class BiaToolGcc
{
public:
	inline static void Call(stream::BiaStream & p_output, BiaMachineContext * p_context, const void * p_pAddress)
	{
		//For 32-Bit systems
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			//Push context onto the stack
			Biax86::Operation32<OP_CODE::PUSH>(p_output, reinterpret_cast<uint32_t>(p_context));

			//Move the address of the function into EAX
			Biax86::Operation32<OP_CODE::MOVE>(p_output, reinterpret_cast<uint32_t>(p_pAddress), REGISTER::EAX);

			//Call EAX
			Biax86::Operation<OP_CODE::CALL>(p_output, REGISTER::EAX);

			//Pop the context from the stack
			Biax86::Operation32<OP_CODE::SUBTRACT>(p_output, 4, REGISTER::ESP);
		}
	}
};

}
}
}