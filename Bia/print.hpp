#pragma once

#include <cstdio>
#include <cstdint>

#include "config.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(inline void, Print(int64_t p_llValue))
{
	printf("%lli\n", p_llValue);
}

BIA_STATIC_CALLING_CONVETION(inline void, Print(float p_rValue))
{
	printf("%f\n", p_rValue);
}

BIA_STATIC_CALLING_CONVETION(inline void, Print(double p_rValue))
{
	printf("%f\n", p_rValue);
}

template<typename _Ty>
BIA_STATIC_CALLING_CONVETION(inline void, Print(_Ty))
{
	printf("%s\n", typeid(_Ty).name());
}


BIA_STATIC_CALLING_CONVETION(inline void, print_i(int32_t p_nValue))
{
	printf("%i\n", p_nValue);
}

BIA_STATIC_CALLING_CONVETION(inline void, print_I(int64_t p_llValue))
{
	printf("%lli\n", p_llValue);
}

BIA_STATIC_CALLING_CONVETION(inline void, print_true())
{
	puts("true");
}

BIA_STATIC_CALLING_CONVETION(inline void, print_false())
{
	puts("false");
}

BIA_STATIC_CALLING_CONVETION(inline void, print_b(int32_t p_nValue))
{
	if (p_nValue)
		Print_true();
	else
		Print_false();
}

BIA_STATIC_CALLING_CONVETION(inline void, print_d(double p_rValue))
{
	printf("%f\n", p_rValue);
}

BIA_STATIC_CALLING_CONVETION(inline void, print_s(const char * p_szString))
{
	puts(p_szString);
}

}
}
}