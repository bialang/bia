#include "biaDouble.hpp"
#include "biaNativeOperator.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{
namespace native
{

void BiaDouble::Print()
{
	machine::link::Print_d(m_rValue);
}

void BiaDouble::OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination)
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

void BiaDouble::OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(ArithmeticOperation(m_rValue, p_nRight, p_unOperator));
}

void BiaDouble::OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(ArithmeticOperation(m_rValue, p_llRight, p_unOperator));
}

void BiaDouble::OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(ArithmeticOperation(m_rValue, p_rRight, p_unOperator));
}

void BiaDouble::OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(ArithmeticOperation(m_rValue, p_rRight, p_unOperator));
}

void BiaDouble::OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaDouble::OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight)
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

void BiaDouble::OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	m_rValue = ArithmeticOperation(m_rValue, p_nRight, p_unOperator);
}

void BiaDouble::OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	m_rValue = ArithmeticOperation(m_rValue, p_llRight, p_unOperator);
}

void BiaDouble::OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight)
{
	m_rValue = ArithmeticOperation(m_rValue, p_rRight, p_unOperator);
}

void BiaDouble::OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight)
{
	m_rValue = ArithmeticOperation(m_rValue, p_rRight, p_unOperator);
}

void BiaDouble::OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::BadCallException("String values are not supported.");
}

void BiaDouble::OperatorSelfCall(uint32_t p_unOperator)
{
}

void BiaDouble::Clone(BiaMember * p_pDestination)
{
	p_pDestination->ReplaceObject<BiaDouble>(m_rValue);
}

int BiaDouble::GetNativeType() const
{
	return NTF_DOUBLE;
}

int32_t BiaDouble::Test()
{
	return static_cast<int32_t>(m_rValue != 0.0);
}

int32_t BiaDouble::TestCall(uint32_t p_unOperator, BiaMember * p_pRight)
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

int32_t BiaDouble::TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight)
{
	return CompareOperation(m_rValue, p_nRight, p_unOperator);
}

int32_t BiaDouble::TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight)
{
	return CompareOperation(m_rValue, p_llRight, p_unOperator);
}

int32_t BiaDouble::TestCallFloat(uint32_t p_unOperator, float p_rRight)
{
	return CompareOperation(m_rValue, p_rRight, p_unOperator);
}

int32_t BiaDouble::TestCallDouble(uint32_t p_unOperator, double p_rRight)
{
	return CompareOperation(m_rValue, p_rRight, p_unOperator);
}

int32_t BiaDouble::TestCallString(uint32_t p_unOperator, const char * p_szRight)
{
	throw exception::OperatorException("Cannot compare an floating point to a string.");
}

void * BiaDouble::GetNativeData(NATIVE_TYPE p_nativeType)
{
	switch (p_nativeType)
	{
	case NATIVE_TYPE::DOUBLE:
	case NATIVE_TYPE::CONST_DOUBLE:
		return &m_rValue;
	default:
		throw exception::BadCastException("Native type is not supported.");
	}
}

}
}
}