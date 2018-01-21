#pragma once

#include <cstdint>
#include <new>
#include <type_traits>

#include "biaNativeVariable.hpp"
#include "biaMember.hpp"
#include "biaPrint.hpp"
#include "biaException.hpp"
#include "biaConstantOperation.hpp"


namespace bia
{
namespace framework
{

template<>
class BiaNativeVariable<int64_t> final : public BiaMember
{
public:
	inline explicit BiaNativeVariable(int64_t p_llValue) : m_llValue(p_llValue) {}
	inline explicit BiaNativeVariable(int32_t p_nValue) : m_llValue(p_nValue) {}

	/**
	* @see	BiaMember::Print().
	*/
	inline virtual void Print() override
	{
		machine::link::Print_I(m_llValue);
	}
	/**
	 * @see	BiaMember::Call().
	*/
	inline virtual void Call() override
	{
		puts("system execute");
	}
	/**
	 * @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(uint32_t p_unParameterCount, ...) override
	{

	}
	/**
	 * @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(const char * p_szFormat, ...) override
	{
		va_list parameters;
		va_start(parameters, p_szFormat);

		while (true)
		{
			switch (*p_szFormat++)
			{
			case 0:
				goto gt_break;
			case 'M':
				va_arg(parameters, BiaMember*);
			case 'i':
				va_arg(parameters, int32_t);
			case 'I':
				va_arg(parameters, int64_t);
			case 'f':
				va_arg(parameters, float);
			case 'd':
				va_arg(parameters, double);
			case 's':
			default:
				break;
			}
		}

	gt_break:;

		va_end(parameters);
	}
	/**
	* @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) override
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
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, void * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationIntegral(m_llValue, p_nRight, p_unOperator));
	}
	/**
	* @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, void * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationIntegral(m_llValue, p_llRight, p_unOperator));
	}
	/**
	* @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, void * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		//new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
	}
	/**
	* @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, void * p_pDestination) override
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
		m_llValue = compiler::ConstantOperationIntegral(m_llValue, p_nRight, p_unOperator);
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		m_llValue = compiler::ConstantOperationIntegral(m_llValue, p_llRight, p_unOperator);
	}
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		m_llValue = static_cast<int64_t>(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
	}
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		m_llValue = static_cast<int64_t>(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
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
	inline virtual void Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable(m_llValue);
	}
	/**
	* @see	BiaMember::IsType().
	*/
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
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
	virtual int32_t Test() override
	{
		return reinterpret_cast<int32_t*>(&m_llValue)[0] | reinterpret_cast<int32_t*>(&m_llValue)[1];
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
			return nullptr;
		}
	}
	/**
	* @see	BiaMember::GetData().
	*/
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		return nullptr;
	}

private:
	int64_t m_llValue;
};

}
}