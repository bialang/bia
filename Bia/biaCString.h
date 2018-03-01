#pragma once

#include <new>
#include <string>

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
	/**
	 * Constructor.
	 *
	 * @param	p_szConstantString	Defines a string address that has to be valid until the end of the lifetime of this object.
	*/
	inline explicit BiaCString(const char * p_szConstantString) : m_szString(p_szConstantString) {}
	/**
	 * Dummy-Constructor in order to prevent compiler errors.
	*/
	template<typename _DUMMY>
	inline explicit BiaCString(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}
	~BiaCString() = default;

	/**
	 * @see	BiaMember::Undefine().
	*/
	virtual void Undefine() override;
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
	virtual void Call(BiaMember*, BiaMember*) override;
	/**
	 * @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(BiaMember*, BiaMember*, parameter_count, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	/**
	 * @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(BiaMember*, BiaMember*, parameter_count, const char*, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Invalid type on native operation.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	{
	}
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	{
	}
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	{
	}
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
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
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaCString>(m_szString);
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
		return NTF_STRING;
	}
	/**
	 * @see	BiaMember::Test().
	*/
	virtual int32_t Test() override
	{
		return false;
		//return reinterpret_cast<int32_t*>(&m_llValue)[0] | reinterpret_cast<int32_t*>(&m_llValue)[1];
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
	virtual BiaMember * GetMember(const char * p_szName) override;

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override;
	/**
	 * @see	BiaMember::GetData().
	*/
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) override;

private:
	const char * m_szString;	/**	Defines the constant address of the string. Must not be modified.	*/
};

}
}