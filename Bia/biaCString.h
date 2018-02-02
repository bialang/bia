#pragma once

#include <new>

#include "biaMember.hpp"
#include "biaPrint.hpp"
#include "biaException.hpp"
#include "biaUndefined.hpp"


namespace bia
{
namespace framework
{

class BiaCString : public BiaMember
{
public:
	inline explicit BiaCString(const char * p_szConstantString) : m_szString(p_szConstantString) {}
	template<typename _DUMMY>
	inline explicit BiaCString(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}
	inline ~BiaCString() = default;

	/**
	* @see	BiaMember::Undefine().
	*/
	virtual void Undefine() override
	{
		//Destroy this
		this->~BiaCString();

		//Undefine
		new(this) BiaUndefined();
	}
	/**
	* @see	BiaMember::Print().
	*/
	inline virtual void Print() override
	{
		machine::link::Print_s(m_szString);
	}
	/**
	* @see	BiaMember::Call().
	*/
	inline virtual void Call(BiaMember*) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	/**
	* @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(BiaMember*, parameter_count, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	/**
	* @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(BiaMember*, const char*, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	/**
	* @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) override
	{
		throw exception::OperatorException("Invalid type on native operation.");
	}
	/**
	* @see	BiaMember::OperatorCallInt_32().
	*/
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, void * p_pDestination) override
	{
	}
	/**
	* @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, void * p_pDestination) override
	{
	}
	/**
	* @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, void * p_pDestination) override
	{
	}
	/**
	* @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, void * p_pDestination) override
	{
	}
	/**
	* @see	BiaMember::OperatorAssignCall().
	*/
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::OperatorException("Invalid type on native operation.");
	}
	/**
	* @see	BiaMember::OperatorAssignCallInt_32().
	*/
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
	}
	/**
	* @see	BiaMember::OperatorAssignCallInt_64().
	*/
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
	}
	/**
	* @see	BiaMember::OperatorAssignCallFloat().
	*/
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
	}
	/**
	* @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
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
		new(p_pDestination) BiaCString(m_szString);
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
		return false;
		//return reinterpret_cast<int32_t*>(&m_llValue)[0] | reinterpret_cast<int32_t*>(&m_llValue)[1];
	}

protected:
	/**
	* @see	BiaMember::GetNativeData().
	*/
	inline virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override
	{
		switch (p_nativeType)
		{
		default:
			throw exception::BadCastException("Native type is not supported.");
		}
	}
	/**
	* @see	BiaMember::GetData().
	*/
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Type is not supported.");
	}

private:
	const char * m_szString;
};

}
}