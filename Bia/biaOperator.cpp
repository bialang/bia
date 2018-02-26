#include "biaOperator.hpp"
#include "biaInt.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(void, OperatorCallInt_32(int32_t p_nLeft, uint32_t p_unOperator, framework::BiaMember * p_pRight, framework::BiaMember * p_pDestination))
{
	//Create left
	framework::BiaInt left(p_nLeft);

	left.OperatorCall(p_unOperator, p_pRight, p_pDestination);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, OperatorCallInt_64(int64_t p_llLeft, uint32_t p_unOperator, framework::BiaMember * p_pRight, framework::BiaMember * p_pDestination))
{
	//Create left
	framework::BiaInt left(p_llLeft);

	left.OperatorCall(p_unOperator, p_pRight, p_pDestination);
}

BIA_INSTRUCTION_CALLING_CONVETION(void, OperatorCallFloat(float p_rLeft, uint32_t p_unOperator, framework::BiaMember * p_pRight, framework::BiaMember * p_pDestination))
{
}

BIA_INSTRUCTION_CALLING_CONVETION(void, OperatorCallDouble(double p_rLeft, uint32_t p_unOperator, framework::BiaMember * p_pRight, framework::BiaMember * p_pDestination))
{
}

}
}
}