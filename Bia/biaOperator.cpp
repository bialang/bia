#include "biaOperator.hpp"
#include "biaInt.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_INSTRUCTION_CALLING_CONVETION(void*, OperatorCall_MM(uint32_t p_unOperator, framework::BiaMember * p_pLeft, framework::BiaMember * p_pRight, void * p_pDestination))
{
	printf("Destination: %p\n", p_pDestination);

	//Destruct destination if it was not already
	//static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();
	
	//Call operator
	//p_pLeft->OperatorCall(p_unOperator, p_pRight, p_pDestination);
	
	return p_pDestination;
}

BIA_INSTRUCTION_CALLING_CONVETION(void*, OperatorCall_Mi(uint32_t p_unOperator, int32_t p_nRight, framework::BiaMember * p_pLeft, void * p_pDestination))
{
	//Destruct destination if it was not already
	static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

	//Create right
	framework::BiaInt right(p_nRight);

	//Call operator
	p_pLeft->OperatorCall(p_unOperator, &right, p_pDestination);

	return p_pDestination;
}

}
}
}