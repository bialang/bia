#pragma once

#include <cstdint>
#include <type_traits>

#include "biaMachineContext.hpp"
#include "biaArchitecture.hpp"
#include "biax86.hpp"
#include "biaOutputStream.hpp"


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
	inline static void Initialize(stream::BiaOutputStream & p_output, BiaMachineContext * p_context)
	{
		//For 32-Bit systems
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
			Biax86::Operation32<OP_CODE::PUSH>(p_output, reinterpret_cast<uint32_t>(p_context));
	}
	inline static void Finalize(stream::BiaOutputStream & p_output)
	{
		//For 32-Bit systems
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			Biax86::Operation8<OP_CODE::ADD>(p_output, 4, REGISTER::ESP);
			Biax86::Operation<OP_CODE::RETURN_NEAR>(p_output);
		}
	}
	inline static void Call(stream::BiaOutputStream & p_output, const void * p_pAddress)
	{
		//For 32-Bit systems
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			//Move the address of the function into EAX
			Biax86::Operation32<OP_CODE::MOVE>(p_output, reinterpret_cast<uint32_t>(p_pAddress), REGISTER::EAX);

			//Call EAX
			Biax86::Operation<OP_CODE::CALL>(p_output, REGISTER::EAX);
		}
	}
};

}
}
}