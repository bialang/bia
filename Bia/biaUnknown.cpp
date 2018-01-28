#include "biaUnknown.hpp"

namespace bia
{
namespace framework
{

void BiaUnknown::Print()
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::Call(BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::CallCount(BiaMember*, parameter_count, ...)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::CallFormat(BiaMember*, const char*, ...)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorCall(uint32_t, BiaMember*, void*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorCallInt_32(uint32_t, int32_t, void*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorCallInt_64(uint32_t, int64_t, void*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorCallFloat(uint32_t, float, void*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorCallDouble(uint32_t, double, void*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorAssignCall(uint32_t, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorAssignCallInt_32(uint32_t, int32_t)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorAssignCallInt_64(uint32_t, int64_t)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorAssignCallFloat(uint32_t, float)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorAssignCallDouble(uint32_t, double)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::OperatorSelfCall(uint32_t)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUnknown::Clone(void*)
{
	throw exception::SymbolException("Undefined symbol.");
}

bool BiaUnknown::IsType(const std::type_info&) const
{
	throw exception::SymbolException("Undefined symbol.");
}

int BiaUnknown::GetNativeType() const
{
	throw exception::SymbolException("Undefined symbol.");
}

int32_t BiaUnknown::Test()
{
	throw exception::SymbolException("Undefined symbol.");
}

void * BiaUnknown::GetNativeData(NATIVE_TYPE)
{
	throw exception::SymbolException("Undefined symbol.");
}

void * BiaUnknown::GetData(const std::type_info&, bool)
{
	throw exception::SymbolException("Undefined symbol.");
}

}
}