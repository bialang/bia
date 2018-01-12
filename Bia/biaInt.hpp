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
class BiaNativeVariable<long long> final : public BiaMember
{
public:
	inline explicit BiaNativeVariable(long long p_llValue) : m_llValue(p_llValue) {}

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
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) override
	{
		auto fRightNativeType = p_pRight->GetNativeType();

		//64 bit int operand
		if (fRightNativeType & NTF_INT_64)
		{
			if (auto pRight = p_pRight->Cast<int64_t>())
			{
				static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();
				new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationIntegral(m_llValue, *pRight, p_unOperator));

				return;
			}
		}
		//Float
		else if (fRightNativeType & NTF_FLOAT)
		{
			//static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();
		}
		//Double
		else if (fRightNativeType & NTF_DOUBLE)
		{
			//static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();
		}
		//Maybe 8, 16 or 32 bit?
		else if (fRightNativeType & (NTF_INT_8 | NTF_INT_16 | NTF_INT_32))
		{
			//static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();
		}

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

		new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
	}
	/**
	* @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, void * p_pDestination) override
	{
		static_cast<framework::BiaMember*>(p_pDestination)->~BiaMember();

		new(p_pDestination) BiaNativeVariable(compiler::ConstantOperationBasic(m_llValue, p_rRight, p_unOperator));
	}
	/**
	* @see	BiaMember::OperatorAssignCall().
	*/
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		m_llValue = static_cast<long long>(compiler::ConstantOperationIntegral(m_llValue, *p_pRight->Cast<int64_t>(), p_unOperator));
	}
	/**
	* @see	BiaMember::OperatorAssignCallInt_32().
	*/
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		m_llValue = static_cast<long long>(compiler::ConstantOperationIntegral(m_llValue, p_nRight, p_unOperator));
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
	long long m_llValue;
};

}
}