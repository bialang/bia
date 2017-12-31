#include "biaUnknown.hpp"

namespace bia
{
namespace framework
{

void BiaUnknown::Print()
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorSelfCall(uint32_t p_unOperator)
{
	throw exception::SymbolException("Undefined symbol.");
}

bool BiaUnknown::IsType(const std::type_info & p_type) const
{
	throw exception::SymbolException("Undefined symbol.");
}

}
}