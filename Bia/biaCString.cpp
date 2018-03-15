#include "biaCString.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{
namespace native
{

void BiaCString::Print()
{
	machine::link::Print_s(m_szString);
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

void BiaCString::OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("String values are not supported.");
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

void BiaCString::OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaCString::OperatorSelfCall(uint32_t p_unOperator)
{
	throw exception::BadCallException("Invalid self operator call on native type.");
}

void BiaCString::Clone(BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaCString>(m_szString);
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

}
}
}