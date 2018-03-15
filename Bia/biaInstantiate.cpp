#include "biaInstantiate.hpp"
#include "biaInt.hpp"
#include "biaFloat.hpp"
#include "biaDouble.hpp"
#include "biaCString.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_32(framework::BiaMember * p_pMember, int32_t p_nValue))
{
	p_pMember->ReplaceObject<framework::native::BiaInt>(p_nValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_64(framework::BiaMember * p_pMember, int64_t p_llValue))
{
	p_pMember->ReplaceObject<framework::native::BiaInt>(p_llValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt0(framework::BiaMember * p_pMember))
{
	p_pMember->ReplaceObject<framework::native::BiaInt>(0);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateIntP1(framework::BiaMember * p_pMember))
{
	p_pMember->ReplaceObject<framework::native::BiaInt>(1);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateIntN1(framework::BiaMember * p_pMember))
{
	p_pMember->ReplaceObject<framework::native::BiaInt>(-1);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateFloat(framework::BiaMember *p_pMember, float p_rValue))
{
	p_pMember->ReplaceObject<framework::native::BiaFloat>(p_rValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateDouble(framework::BiaMember *p_pMember, double p_rValue))
{
	p_pMember->ReplaceObject<framework::native::BiaDouble>(p_rValue);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateCString(framework::BiaMember *p_pMember, const char *p_szString))
{
	p_pMember->ReplaceObject<framework::native::BiaCString>(p_szString);
}

}
}
}