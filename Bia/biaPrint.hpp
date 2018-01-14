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
	printf("%i\n", p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_I(int64_t p_llValue))
{
	printf("%lli\n", p_llValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_true())
{
	puts("true");
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_false())
{
	puts("false");
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_b(int32_t p_nValue))
{
	if (p_nValue)
		Print_true();
	else
		Print_false();
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_f(float p_rValue))
{
	printf("%f\n", p_rValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, Print_d(double p_rValue))
{
	printf("%f\n", p_rValue);
}

}
}
}