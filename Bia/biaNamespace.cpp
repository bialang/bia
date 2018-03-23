#include "biaNamespace.hpp"
#include "biaUndefined.hpp"


namespace bia
{
namespace framework
{

BiaNamespace::BiaNamespace(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager) : m_pMemberHolder(new BiaMemberHolder(p_pAllocator, p_pNameManager))
{
}

void BiaNamespace::Undefine()
{
	ReplaceObject<BiaUndefined>();
}

void BiaNamespace::Print()
{
	printf("<%s at %p>", typeid(*this).name(), this);
}

void BiaNamespace::Call(BiaMember * p_pInstance, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid call on namespace.");
}

void BiaNamespace::CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...)
{
	throw exception::BadCallException("Invalid call on namespace.");
}

void BiaNamespace::CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...)
{
	throw exception::BadCallException("Invalid call on namespace.");
}

void BiaNamespace::Instantiate(BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid instantiation call on namespace.");
}

void BiaNamespace::InstantiateCount(BiaMember * p_pDestination, parameter_count p_unParameterCount, ...)
{
	throw exception::BadCallException("Invalid instantiation call on namespace.");
}

void BiaNamespace::InstantiateFormat(BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...)
{
	throw exception::BadCallException("Invalid instantiation call on namespace.");
}

void BiaNamespace::OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::OperatorSelfCall(uint32_t p_unOperator)
{
	throw exception::BadCallException("Invalid operator call on namespace.");
}

void BiaNamespace::Clone(BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaNamespace>(*this);
}

bool BiaNamespace::IsType(const std::type_info & p_type) const
{
	return false;
}

int BiaNamespace::GetNativeType() const
{
	return NTF_NONE;
}

int32_t BiaNamespace::Test()
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

int32_t BiaNamespace::TestCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

int32_t BiaNamespace::TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

int32_t BiaNamespace::TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

int32_t BiaNamespace::TestCallFloat(uint32_t p_unOperator, float p_rRight)
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

int32_t BiaNamespace::TestCallDouble(uint32_t p_unOperator, double p_rRight)
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

int32_t BiaNamespace::TestCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::BadCallException("Invalid test call on namespace.");
}

BiaMember * BiaNamespace::GetMember(const char * p_szName)
{
	if (auto pMember = m_pMemberHolder->GetMember(p_szName))
		return pMember;

	throw exception::SymbolException("Unkown member.");
}

void * BiaNamespace::GetNativeData(native::NATIVE_TYPE p_nativeType)
{
	throw exception::BadCastException("Invalid cast on namespace.");
}

void * BiaNamespace::GetData(const std::type_info & p_type, bool p_bConst)
{
	throw exception::BadCastException("Invalid cast on namespace.");
}

}
}