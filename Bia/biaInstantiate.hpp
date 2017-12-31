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

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_32(int32_t p_nValue, framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();
	printf("Ins: %i\n", p_nValue);
	//Create new int object
	new(p_pMember) framework::BiaInt(p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_64(int64_t p_llValue, framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(p_llValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt0(framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(0);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateIntP1(framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(1);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateIntN1(framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(-1);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateFloat(float p_rValue, framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) api::framework::BiaInt(p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateDouble(double p_rValue, framework::BiaMember * p_pMember))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) api::framework::BiaInt(p_nValue);
}

}
}
}