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
	virtual void Print() override;
	/**
	 * @see	BiaMember::Call().
	*/
	virtual void Call(BiaMember*, BiaMember*) override;
	/**
	 * @see	BiaMember::CallCount().
	*/
	virtual void CallCount(BiaMember*, BiaMember*, parameter_count, ...) override;
	/**
	 * @see	BiaMember::CallFormat().
	*/
	virtual void CallFormat(BiaMember*, BiaMember*, parameter_count, const char*, ...) override;
	/**
	 * @see	BiaMember::Instantiate().
	*/
	virtual void Instantiate(BiaMember*) override;
	/**
	 * @see	BiaMember::InstantiateCount().
	*/
	virtual void InstantiateCount(BiaMember*, parameter_count, ...) override;
	/**
	 * @see	BiaMember::InstantiateFormat().
	*/
	virtual void InstantiateFormat(BiaMember*, parameter_count, const char*, ...) override;
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override;
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	virtual void OperatorSelfCall(uint32_t p_unOperator) override;
	/**
	 * @see	BiaMember::Clone().
	*/
	virtual void Clone(BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info & p_type) const override;
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	virtual int GetNativeType() const override;
	/**
	 * @see	BiaMember::Test().
	*/
	virtual int32_t Test() override;
	/**
	 * @see	BiaMember::TestCall().
	*/
	virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	/**
	 * @see	BiaMember::TestCallInt_32().
	*/
	virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	/**
	 * @see	BiaMember::TestCallInt_64().
	*/
	virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override;
	/**
	 * @see	BiaMember::TestCallFloat().
	*/
	virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override;
	/**
	 * @see	BiaMember::TestCallDouble().
	*/
	virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override;
	/**
	 * @see	BiaMember::TestCallString().
	*/
	virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override;
	/**
	 * @see	BiaMember::GetMember().
	*/
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
	/**	Defines the constant address of the string. Must not be modified.	*/
	const char * m_szString;
};

}
}