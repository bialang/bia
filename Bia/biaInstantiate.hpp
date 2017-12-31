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

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateCopy(framework::BiaMember * p_pMember, framework::BiaMember * p_pSource))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	p_pSource->Clone(p_pMember);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateInt_32(framework::BiaMember * p_pMember, int32_t p_nValue))
{
	//Destruct old object
	p_pMember->~BiaMember();
	printf("Ins: %i\n", p_nValue);
	//Create new int object
	new(p_pMember) framework::BiaInt(p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateInt_64(framework::BiaMember * p_pMember, int64_t p_llValue))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(p_llValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateInt0(framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(0);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateIntP1(framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(1);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateIntN1(framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(-1);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateFloat(framework::BiaMember * p_pMember, float p_rValue))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) api::framework::BiaInt(p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(inline void, InstantiateDouble(framework::BiaMember * p_pMember, double p_rValue))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) api::framework::BiaInt(p_nValue);
}

}
}
}