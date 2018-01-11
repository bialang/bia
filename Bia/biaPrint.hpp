#pragma once

#include <cstdio>

#include "biaConfig.hpp"
#include "biaMember.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_i(int32_t p_nValue))
{
	printf("%i", p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_I(int64_t p_llValue))
{
	printf("%lli", p_llValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_f(float p_rValue))
{
	printf("%f", p_rValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_d(double p_rValue))
{
	printf("%f", p_rValue);
}

}
}
}