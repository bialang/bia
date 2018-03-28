#pragma once

#include <type_traits>

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
class BiaNativeReference final : public BiaNativeVariable
{
public:
	inline explicit BiaNativeReference(T * p_pPointer) : m_pValue(p_pPointer) {}
	inline explicit BiaNativeReference(T & p_reference) : m_pValue(&p_reference) {}
	template<typename _DUMMY>
	inline explicit BiaNativeReference(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}

	inline virtual void Print() override
	{
		machine::link::Print(*m_pValue);
	}
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	{
		operation_chooser<T>::OperationResult(*m_pValue, p_unOperator, p_nRight);
	}
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	{
		operation_chooser<T>::OperationResult(*m_pValue, p_unOperator, p_llRight);
	}
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	{
		operation_chooser<T>::OperationResult(*m_pValue, p_unOperator, p_rRight);
	}
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
	{
		operation_chooser<T>::OperationResult(*m_pValue, p_unOperator, p_rRight);
	}
	inline virtual void OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_nRight);
	}
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_llRight);
	}
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_rRight);
	}
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_rRight);
	}
	inline virtual void OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaNativeReference<T>>(m_pValue);
	}
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
	}
	inline virtual int32_t Test() override
	{
		return native::Test(*m_pValue);
	}
	inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		return test_operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_nRight);
	}
	inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		return test_operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_llRight);
	}
	inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		return test_operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_rRight);
	}
	inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		return test_operation_chooser<T>::Operation(*m_pValue, p_unOperator, p_rRight);
	}
	inline virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::OperatorException("Cannot compare an integral to a string.");
	}

protected:
	inline virtual void * GetNativeData(native::NATIVE_TYPE p_nativeType) override
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented");
	}

private:
	T * m_pValue;
};

}
}
}