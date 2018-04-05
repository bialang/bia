#pragma once

#include <type_traits>

#include "biaTypeTraits.hpp"
#include "biaNativeVariable.hpp"
#include "biaNativeOperator.hpp"
#include "biaNativeTestOperator.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename T>
class BiaNative final : public BiaNativeVariable
{
public:
	template<typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	inline explicit BiaNative(T p_value) : m_value(p_value) {}
	template<typename _DUMMY, typename = typename std::enable_if<utility::Negation<std::is_arithmetic<_DUMMY>::value>::value>::type>
	inline explicit BiaNative(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}

	inline virtual void Print() override
	{
		machine::link::Print(m_value);
	}
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

		throw exception::OperatorException("Invalid type on native operation.");
	}
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	{
		CreateResultMember(operation_chooser<T>::OperationResult(m_value, p_unOperator, p_nRight), p_pDestination);
	}
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	{
		CreateResultMember(operation_chooser<T>::OperationResult(m_value, p_unOperator, p_llRight), p_pDestination);
	}
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	{
		CreateResultMember(operation_chooser<T>::OperationResult(m_value, p_unOperator, p_rRight), p_pDestination);
	}
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
	{
		CreateResultMember(operation_chooser<T>::OperationResult(m_value, p_unOperator, p_rRight), p_pDestination);
	}
	inline virtual void OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("String values are not supported.");
	}
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
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		operation_chooser<T>::Operation(m_value, p_unOperator, p_nRight);
	}
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		operation_chooser<T>::Operation(m_value, p_unOperator, p_llRight);
	}
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		operation_chooser<T>::Operation(m_value, p_unOperator, p_rRight);
	}
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		operation_chooser<T>::Operation(m_value, p_unOperator, p_rRight);
	}
	inline virtual void OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::BadCallException("String values are not supported.");
	}
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaNative<T>>(m_value);
	}
	inline virtual int GetNativeType() const override
	{
		//Integral
		if (std::is_same<T, int64_t>::value)
			return NTF_INT_8 | NTF_INT_16 | NTF_INT_32 | NTF_INT_64;
		//Float
		else if (std::is_same<T, float>::value)
			return NTF_FLOAT;
		//Double
		else if (std::is_same<T, double>::value)
			return NTF_DOUBLE;

		return NTF_NONE;
	}
	inline virtual int32_t Test() override
	{
		return native::Test(m_value);
	}
	inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
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
	inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		return test_operation_chooser<T>::Operation(m_value, p_unOperator, p_nRight);
	}
	inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		return test_operation_chooser<T>::Operation(m_value, p_unOperator, p_llRight);
	}
	inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		return test_operation_chooser<T>::Operation(m_value, p_unOperator, p_rRight);
	}
	inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		return test_operation_chooser<T>::Operation(m_value, p_unOperator, p_rRight);
	}
	inline virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::OperatorException("Cannot compare an integral to a string.");
	}

protected:
	inline virtual void * GetNativeData(native::NATIVE_TYPE p_nativeType) override
	{
		//Integral
		if (std::is_same<T, int64_t>::value)
		{
			switch (p_nativeType)
			{
			case NATIVE_TYPE::BOOL:
				m_bNonZero = static_cast<bool>(m_value);

				return &m_bNonZero;
			case NATIVE_TYPE::INT_8:
			case NATIVE_TYPE::CONST_INT_8:
			case NATIVE_TYPE::INT_16:
			case NATIVE_TYPE::CONST_INT_16:
			case NATIVE_TYPE::INT_32:
			case NATIVE_TYPE::CONST_INT_32:
			case NATIVE_TYPE::INT_64:
			case NATIVE_TYPE::CONST_INT_64:
				return &m_value;
			default:
				break;
			}
		}
		//Float
		else if (std::is_same<T, float>::value)
		{
			switch (p_nativeType)
			{
			case NATIVE_TYPE::BOOL:
				m_bNonZero = static_cast<bool>(m_value);

				return &m_bNonZero;
			case NATIVE_TYPE::FLOAT:
			case NATIVE_TYPE::CONST_FLOAT:
				return &m_value;
			default:
				break;
			}
		}
		//Double
		else if (std::is_same<T, float>::value)
		{
			switch (p_nativeType)
			{
			case NATIVE_TYPE::BOOL:
				m_bNonZero = static_cast<bool>(m_value);

				return &m_bNonZero;
			case NATIVE_TYPE::DOUBLE:
			case NATIVE_TYPE::CONST_DOUBLE:
				return &m_value;
			default:
				break;
			}
		}

		throw exception::BadCastException("Native type is not supported.");
	}

private:
	/**	The arithmetic value of type: int64_t, float or double.	*/
	T m_value;
	/**	True if the value is non zero.	*/
	bool m_bNonZero;


	template<typename T>
	inline static void CreateResultMember(T && p_value, BiaMember * p_pDestination)
	{
		if (std::is_integral<T>::value)
			p_pDestination->ReplaceObject<BiaNative<int64_t>>(p_value);
		else if (std::is_same<T, float>::value)
			p_pDestination->ReplaceObject<BiaNative<float>>(p_value);
		else if (std::is_same<T, double>::value)
			p_pDestination->ReplaceObject<BiaNative<double>>(p_value);
		else
			throw BIA_IMPLEMENTATION_EXCEPTION("Implementation error.");
	}
};

using BiaInt = BiaNative<int64_t>;
using BiaFloat = BiaNative<float>;
using BiaDouble = BiaNative<double>;

}
}
}