#pragma once

#include <cstdint>

#include "biaConfig.hpp"
#include "biaMachineContext.hpp"
#include "biaMember.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(inline void, AllocateTemporaryMembers(framework::BiaMember ** p_pDestination, int8_t p_cCount, BiaMachineContext * p_pContext))
{
	for (int8_t i = 0; i < p_cCount; ++i)
	{

	}
}

}
}
}