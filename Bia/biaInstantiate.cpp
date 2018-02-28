#include "biaInstantiate.hpp"
#include "biaInt.hpp"
#include "biaCString.h"

#include <new>


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_32(framework::BiaMember * p_pMember, int32_t p_nValue))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	new(p_pMember) framework::BiaInt(p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_64(framework::BiaMember * p_pMember, int64_t p_llValue))
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

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateFloat(framework::BiaMember *p_pMember, float p_rValue))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) framework::BiaNativeVariable<float>(p_rValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateDouble(framework::BiaMember *p_pMember, double p_rValue))
{
	//Destruct old object
	p_pMember->~BiaMember();

	//Create new int object
	//new(p_pMember) framework::BiaNativeVariable<double>(p_rValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateCString(framework::BiaMember *p_pMember, const char *p_szString))
{
	p_pMember->~BiaMember();

	new(p_pMember) framework::BiaCString(p_szString);
}

}
}
}