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

/*
 * M	= Member pointer
 * i	= int 32 bit constant
 * I	= int 64 bit constant
 * f	= float constant
 * d	= double constant
 * s	= zero-terminated string pointer
*/

inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_MM(uint32_t p_unOperator, api::framework::BiaMember * p_pRight, api::framework::BiaMember * p_pLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_iM(uint32_t p_unOperator, api::framework::BiaMember * p_pRight, int32_t p_nLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_IM(uint32_t p_unOperator, api::framework::BiaMember * p_pRight, int64_t p_llLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_fM(uint32_t p_unOperator, api::framework::BiaMember * p_pRight, float p_rLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_dM(uint32_t p_unOperator, api::framework::BiaMember * p_pRight, double p_rLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_sM(uint32_t p_unOperator, api::framework::BiaMember * p_pRight, const char * p_szLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_Mi(uint32_t p_unOperator, int32_t p_nRight, api::framework::BiaMember * p_pLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_MI(uint32_t p_unOperator, int64_t p_llRight, api::framework::BiaMember * p_pLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_Mf(uint32_t p_unOperator, float p_rRight, api::framework::BiaMember * p_pLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_Md(uint32_t p_unOperator, double p_rRight, api::framework::BiaMember * p_pLeft);
inline api::framework::BiaMember * BIA_INSTRUCTION_CALLING_CONVETION Operator_Ms(uint32_t p_unOperator, const char * p_szRight, api::framework::BiaMember * p_pLeft);

}
}
}