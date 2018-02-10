#include "biaUndefined.hpp"

namespace bia
{
namespace framework
{

void BiaUndefined::Undefine()
{
}

void BiaUndefined::Print()
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::Call(BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::CallCount(BiaMember*, parameter_count, ...)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::CallFormat(BiaMember*, const char*, ...)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorCall(uint32_t, BiaMember*, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorCallInt_32(uint32_t, int32_t, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorCallInt_64(uint32_t, int64_t, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorCallFloat(uint32_t, float, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorCallDouble(uint32_t, double, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorAssignCall(uint32_t, BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorAssignCallInt_32(uint32_t, int32_t)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorAssignCallInt_64(uint32_t, int64_t)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorAssignCallFloat(uint32_t, float)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorAssignCallDouble(uint32_t, double)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::OperatorSelfCall(uint32_t)
{
	throw exception::SymbolException("Undefined symbol.");
}

void BiaUndefined::Clone(BiaMember*)
{
	throw exception::SymbolException("Undefined symbol.");
}

bool BiaUndefined::IsType(const std::type_info&) const
{
	throw exception::SymbolException("Undefined symbol.");
}

int BiaUndefined::GetNativeType() const
{
	throw exception::SymbolException("Undefined symbol.");
}

int32_t BiaUndefined::Test()
{
	throw exception::SymbolException("Undefined symbol.");
}

void * BiaUndefined::GetNativeData(NATIVE_TYPE)
{
	throw exception::SymbolException("Undefined symbol.");
}

void * BiaUndefined::GetData(const std::type_info&, bool)
{
	throw exception::SymbolException("Undefined symbol.");
}

}
}