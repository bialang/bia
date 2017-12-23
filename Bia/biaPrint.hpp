#pragma once

#include <cstdio>

#include "biaMember.hpp"


namespace bia
{
namespace machine
{
namespace link
{

inline void Print_M(api::framework::BiaMember * p_pMember)
{
	p_pMember->Print();
}

inline void Print_i(int32_t p_nValue)
{
	printf("%i", p_nValue);
}

inline void Print_I(int64_t p_llValue)
{
	printf("%lli", p_llValue);
}

inline void Print_f(float p_rValue)
{
	printf("%f", p_rValue);
}

inline void Print_d(double p_rValue)
{
	printf("%f", p_rValue);
}

}
}
}