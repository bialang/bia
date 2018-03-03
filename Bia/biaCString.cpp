#include "biaCString.h"

namespace bia
{
namespace framework
{

void BiaCString::Undefine()
{
	ReplaceObject<BiaUndefined>();
}

void BiaCString::Print()
{
	machine::link::Print_s(m_szString);
}

void BiaCString::Call(BiaMember*, BiaMember *)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

void BiaCString::CallCount(BiaMember *, BiaMember *, parameter_count, ...)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

void BiaCString::CallFormat(BiaMember *, BiaMember *, parameter_count, const char *, ...)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

void BiaCString::Instantiate(BiaMember *)
{
	throw exception::BadCallException("Invalid instantiation call.");
}

void BiaCString::InstantiateCount(BiaMember *, parameter_count, ...)
{
	throw exception::BadCallException("Invalid instantiation call.");
}

void BiaCString::InstantiateFormat(BiaMember *, parameter_count, const char *, ...)
{
	throw exception::BadCallException("Invalid instantiation call.");
}

void BiaCString::OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight)
{
	throw exception::BadCallException("Not implemented.");
}

void BiaCString::OperatorSelfCall(uint32_t p_unOperator)
{
	throw exception::BadCallException("Invalid self operator call on native type.");
}

void BiaCString::Clone(BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaCString>(m_szString);
}

bool BiaCString::IsType(const std::type_info & p_type) const
{
	return false;
}

int BiaCString::GetNativeType() const
{
	return NTF_STRING;
}

int32_t BiaCString::Test()
{
	return static_cast<int32_t>(m_szString[0]);
}

int32_t BiaCString::TestCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	throw exception::BadCallException("Not implemented.");
}

int32_t BiaCString::TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	throw exception::OperatorException("Cannot compare a string to a number.");
}

int32_t BiaCString::TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	throw exception::OperatorException("Cannot compare a string to a number.");
}

int32_t BiaCString::TestCallFloat(uint32_t p_unOperator, float p_rRight)
{
	throw exception::OperatorException("Cannot compare a string to a number.");
}

int32_t BiaCString::TestCallDouble(uint32_t p_unOperator, double p_rRight)
{
	throw exception::OperatorException("Cannot compare a string to a number.");
}

int32_t BiaCString::TestCallString(uint32_t p_unOperator, const char * p_szRight)
{
	if (p_unOperator == O_EQUALS)
		return static_cast<int32_t>(m_szString == p_szRight);
	else if (p_unOperator == O_EQUALS_NOT)
		return static_cast<int32_t>(m_szString != p_szRight);

	throw exception::OperatorException("Invalid compare operator.");
}

BiaMember * BiaCString::GetMember(const char*)
{
	throw exception::SymbolException("Unkown member.");
}

void * BiaCString::GetNativeData(NATIVE_TYPE p_nativeType)
{
	switch (p_nativeType)
	{
	case NATIVE_TYPE::CONST_STRING:
		return &m_szString;
	default:
		throw exception::BadCastException("Native type is not supported.");
	}
}

void * BiaCString::GetData(const std::type_info & p_type, bool p_bConst)
{
	throw exception::BadCastException("Type is not supported.");
}

}
}