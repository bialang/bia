#pragma once

#include <cstdint>

#include "biaConfig.hpp"
#include "biaMember.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_32(framework::BiaMember * p_pMember, int32_t p_nValue));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt_64(framework::BiaMember * p_pMember, int64_t p_llValue));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateInt0(framework::BiaMember * p_pMember));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateIntP1(framework::BiaMember * p_pMember));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateIntN1(framework::BiaMember * p_pMember));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateFloat(framework::BiaMember * p_pMember, float p_rValue));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateDouble(framework::BiaMember * p_pMember, double p_rValue));
BIA_INSTRUCTION_CALLING_CONVETION(void, InstantiateCString(framework::BiaMember * p_pMember, const char * p_szString));

}
}
}