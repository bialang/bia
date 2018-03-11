#include "biaInt.hpp"
#include "biaFloat.hpp"
#include "biaDouble.hpp"
#include "biaNativeOperator.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{
namespace native
{

void BiaInt::Print()
{
	machine::link::Print_I(m_llValue);
}

void BiaInt::OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination)
{
	auto fRightNativeType = p_pRight->GetNativeType();

	//64 bit int operand
	if (fRightNativeType & NTF_INT_64)
		return OperatorCallInt_64(p_unOperator, *p_pRight->Cast<int64_t>(), p_pDestination);
	//Float
	else if (fRightNativeType & NTF_FLOAT)
		return OperatorCallFloat(p_unOperator, *p_pRight->Cast<float>(), p_pDestination);
	//Double
	else if (fRightNativeType & NTF_DOUBLE)
		return OperatorCallDouble(p_unOperator, *p_pRight->Cast<double>(), p_pDestination);
	/*//Maybe 8, 16 or 32 bit?
	else if (fRightNativeType & (NTF_INT_8 | NTF_INT_16 | NTF_INT_32))
	{
	if (fRightNativeType & NTF_INT_64)
	return OperatorCallInt_32(p_unOperator, *p_pRight->Cast<int32_t>(), p_pDestination);
	else if (fRightNativeType & NTF_INT_64)
	return OperatorCallInt_32(p_unOperator, *p_pRight->Cast<int16_t>(), p_pDestination);
	else
	return OperatorCallInt_32(p_unOperator, *p_pRight->Cast<int8_t>(), p_pDestination);
	}*/

	throw exception::OperatorException("Invalid type on native operation.");
}

void BiaInt::OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaInt>(IntegralOperation(m_llValue, p_nRight, p_unOperator));
}

void BiaInt::OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaInt>(IntegralOperation(m_llValue, p_llRight, p_unOperator));
}

void BiaInt::OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaFloat>(ArithmeticOperation(m_llValue, p_rRight, p_unOperator));
}

void BiaInt::OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(ArithmeticOperation(m_llValue, p_rRight, p_unOperator));
}

void BiaInt::OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaInt::OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	auto fRightNativeType = p_pRight->GetNativeType();

	//64 bit int operand
	if (fRightNativeType & NTF_INT_64)
		return OperatorAssignCallInt_64(p_unOperator, *p_pRight->Cast<int64_t>());
	//Float
	else if (fRightNativeType & NTF_FLOAT)
		return OperatorAssignCallFloat(p_unOperator, *p_pRight->Cast<float>());
	//Double
	else if (fRightNativeType & NTF_DOUBLE)
		return OperatorAssignCallDouble(p_unOperator, *p_pRight->Cast<double>());

	throw exception::OperatorException("Invalid type on native operation.");
}

void BiaInt::OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	m_llValue = IntegralOperation(m_llValue, p_nRight, p_unOperator);
}

void BiaInt::OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	m_llValue = IntegralOperation(m_llValue, p_llRight, p_unOperator);
}

void BiaInt::OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight)
{
	m_llValue = static_cast<int64_t>(ArithmeticOperation(m_llValue, p_rRight, p_unOperator));
}

void BiaInt::OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight)
{
	m_llValue = static_cast<int64_t>(ArithmeticOperation(m_llValue, p_rRight, p_unOperator));
}

void BiaInt::OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaInt::OperatorSelfCall(uint32_t p_unOperator)
{
}

void BiaInt::Clone(BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaInt>(m_llValue);
}

int BiaInt::GetNativeType() const
{
	return NTF_INT_8 | NTF_INT_16 | NTF_INT_32 | NTF_INT_64;
}

int32_t BiaInt::Test()
{
	return reinterpret_cast<int32_t*>(&m_llValue)[0] | reinterpret_cast<int32_t*>(&m_llValue)[1];
}

int32_t BiaInt::TestCall(uint32_t p_unOperator, BiaMember * p_pRight)
{
	auto fRightNativeType = p_pRight->GetNativeType();

	//64 bit int operand
	if (fRightNativeType & NTF_INT_64)
		return TestCallInt_64(p_unOperator, *p_pRight->Cast<int64_t>());
	//Float
	else if (fRightNativeType & NTF_FLOAT)
		return TestCallFloat(p_unOperator, *p_pRight->Cast<float>());
	//Double
	else if (fRightNativeType & NTF_DOUBLE)
		return TestCallDouble(p_unOperator, *p_pRight->Cast<double>());

	throw exception::OperatorException("Invalid type on native operation.");
}

int32_t BiaInt::TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	return CompareOperation(m_llValue, p_nRight, p_unOperator);
}

int32_t BiaInt::TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	return CompareOperation(m_llValue, p_llRight, p_unOperator);
}

int32_t BiaInt::TestCallFloat(uint32_t p_unOperator, float p_rRight)
{
	return CompareOperation(m_llValue, p_rRight, p_unOperator);
}

int32_t BiaInt::TestCallDouble(uint32_t p_unOperator, double p_rRight)
{
	return CompareOperation(m_llValue, p_rRight, p_unOperator);
}

int32_t BiaInt::TestCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::OperatorException("Cannot compare an integral to a string.");
}

void * BiaInt::GetNativeData(NATIVE_TYPE p_nativeType)
{
	switch (p_nativeType)
	{
	case NATIVE_TYPE::INT_8:
	case NATIVE_TYPE::CONST_INT_8:
	case NATIVE_TYPE::INT_16:
	case NATIVE_TYPE::CONST_INT_16:
	case NATIVE_TYPE::INT_32:
	case NATIVE_TYPE::CONST_INT_32:
	case NATIVE_TYPE::INT_64:
	case NATIVE_TYPE::CONST_INT_64:
		return &m_llValue;
	default:
		throw exception::BadCastException("Native type is not supported.");
	}
}

}
}
}