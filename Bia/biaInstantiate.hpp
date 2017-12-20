#pragma once

#include <cstdint>
#include <new>

#include "biaConfig.hpp"
#include "biaMember.hpp"
#include "biaInt.hpp"


namespace bia
{
namespace machine
{
namespace link
{

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateInt_32(int32_t p_nValue, api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();
	printf("Ins: %i\n", p_nValue);
	//Create new int object
	new(p_pMember) api::framework::BiaInt(p_nValue);
}

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateInt_64(int64_t p_llValue, api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) api::framework::BiaInt(p_llValue);
}

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateInt0(api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) api::framework::BiaInt(0);
}

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateIntP1(api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) api::framework::BiaInt(1);
}

inline int32_t BIA_INSTRUCTION_CALLING_CONVETION testt(int32_t p_nRight, int32_t p_nLeft)
{
	printf("%i * %i\n", p_nLeft, p_nRight);

	return p_nLeft * p_nRight;
}

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateIntN1(api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) api::framework::BiaInt(-1);
}

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateFloat(float p_rValue, api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) api::framework::BiaInt(p_nValue);
}

inline void BIA_INSTRUCTION_CALLING_CONVETION InstantiateDouble(double p_rValue, api::framework::BiaMember * p_pMember)
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) api::framework::BiaInt(p_nValue);
}

}
}
}