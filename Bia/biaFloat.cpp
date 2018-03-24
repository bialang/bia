#include "biaFloat.hpp"
#include "biaDouble.hpp"
#include "biaNativeOperator.hpp"
#include "biaNativeTestOperator.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{
namespace native
{

void BiaFloat::Print()
{
	machine::link::Print_f(m_rValue);
}

void BiaFloat::OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination)
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

void BiaFloat::OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaFloat>(ArithmeticOperation<false>(m_rValue, p_nRight, p_unOperator));
}

void BiaFloat::OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaFloat>(ArithmeticOperation<false>(m_rValue, p_llRight, p_unOperator));
}

void BiaFloat::OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaFloat>(ArithmeticOperation<false>(m_rValue, p_rRight, p_unOperator));
}

void BiaFloat::OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(ArithmeticOperation<false>(m_rValue, p_rRight, p_unOperator));
}

void BiaFloat::OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaFloat::OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight)
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

void BiaFloat::OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	m_rValue = ArithmeticOperation<true>(m_rValue, p_nRight, p_unOperator);
}

void BiaFloat::OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	m_rValue = ArithmeticOperation<true>(m_rValue, p_llRight, p_unOperator);
}

void BiaFloat::OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight)
{
	m_rValue = ArithmeticOperation<true>(m_rValue, p_rRight, p_unOperator);
}

void BiaFloat::OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight)
{
	m_rValue = static_cast<float>(ArithmeticOperation<true>(m_rValue, p_rRight, p_unOperator));
}

void BiaFloat::OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaFloat::OperatorSelfCall(uint32_t p_unOperator)
{
}

void BiaFloat::Clone(BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaFloat>(m_rValue);
}

int BiaFloat::GetNativeType() const
{
	return NTF_FLOAT;
}

int32_t BiaFloat::Test()
{
	return native::Test(m_rValue);
	//return static_cast<int32_t>(m_rValue != 0.0f);
}

int32_t BiaFloat::TestCall(uint32_t p_unOperator, BiaMember * p_pRight)
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

int32_t BiaFloat::TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	return TestOperation(m_rValue, p_nRight, p_unOperator);
}

int32_t BiaFloat::TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	return TestOperation(m_rValue, p_llRight, p_unOperator);
}

int32_t BiaFloat::TestCallFloat(uint32_t p_unOperator, float p_rRight)
{
	return TestOperation(m_rValue, p_rRight, p_unOperator);
}

int32_t BiaFloat::TestCallDouble(uint32_t p_unOperator, double p_rRight)
{
	return TestOperation(m_rValue, p_rRight, p_unOperator);
}

int32_t BiaFloat::TestCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::OperatorException("Cannot compare an floating point to a string.");
}

void * BiaFloat::GetNativeData(native::NATIVE_TYPE p_nativeType)
{
	switch (p_nativeType)
	{
	case NATIVE_TYPE::FLOAT:
	case NATIVE_TYPE::CONST_FLOAT:
		return &m_rValue;
	default:
		throw exception::BadCastException("Native type is not supported.");
	}
}

}
}
}