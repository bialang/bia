#pragma once

#include "biaNativeVariable.hpp"
#include "biaNativeOperator.hpp"
#include "biaMember.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class BiaInt final : public BiaNativeVariable
{
public:
	inline explicit BiaInt(int64_t p_llValue) : m_llValue(p_llValue) {}
	inline explicit BiaInt(int32_t p_nValue) : m_llValue(p_nValue) {}
	template<typename _DUMMY>
	inline explicit BiaInt(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}

	/**
	 * @see	BiaMember::Print().
	*/
	inline virtual void Print() override
	{
		machine::link::Print_I(m_llValue);
	}
	/**
	* @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override
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
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		new(p_pDestination) BiaInt(IntegralOperation(m_llValue, p_nRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		new(p_pDestination) BiaInt(IntegralOperation(m_llValue, p_llRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		//new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		//new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
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
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		m_llValue = IntegralOperation(m_llValue, p_nRight, p_unOperator);
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		m_llValue = IntegralOperation(m_llValue, p_llRight, p_unOperator);
	}
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		m_llValue = static_cast<int64_t>(ArithmeticOperation(m_llValue, p_rRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		m_llValue = static_cast<int64_t>(ArithmeticOperation(m_llValue, p_rRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{

	}
	/**
	 * @see	BiaMember::Clone().
	*/
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaInt>(m_llValue);
	}
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	inline virtual int GetNativeType() const override
	{
		return NTF_INT_8 | NTF_INT_16 | NTF_INT_32 | NTF_INT_64;
	}
	/**
	 * @see	BiaMember::Test().
	*/
	inline virtual int32_t Test() override
	{
		return reinterpret_cast<int32_t*>(&m_llValue)[0] | reinterpret_cast<int32_t*>(&m_llValue)[1];
	}
	/**
	 * @see	BiaMember::TestCall().
	*/
	inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallInt_32().
	*/
	inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallInt_64().
	*/
	inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallFloat().
	*/
	inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallDouble().
	*/
	inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		return 0;
	}
	/**
	 * @see	BiaMember::TestCallString().
	*/
	inline virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::OperatorException("Cannot compare an integral to a string.");
	}

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	inline virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override
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

private:
	int64_t m_llValue;
};

}
}
}