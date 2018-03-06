#pragma once

#include "biaMember.hpp"
#include "biaException.hpp"
#include "biaUndefined.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

class BiaFunction : public BiaMember
{
public:
	/**
	 * @see	BiaMember::Undefine().
	*/
	virtual void Undefine() override
	{
		ReplaceObject<BiaUndefined>();
	}
	/**
	 * @see	BiaMember::Instantiate().
	*/
	inline virtual void Instantiate(BiaMember*) override
	{
		throw exception::BadCallException("Invalid instantiation call.");
	}
	/**
	 * @see	BiaMember::InstantiateCount().
	*/
	inline virtual void InstantiateCount(BiaMember*, parameter_count, ...) override
	{
		throw exception::BadCallException("Invalid instantiation call.");
	}
	/**
	 * @see	BiaMember::InstantiateFormat().
	*/
	inline virtual void InstantiateFormat(BiaMember*, parameter_count, const char*, ...) override
	{
		throw exception::BadCallException("Invalid instantiation call.");
	}
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t, BiaMember*, BiaMember*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	inline virtual void OperatorCallInt_32(uint32_t, int32_t, BiaMember*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t, int64_t, BiaMember*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t, float, BiaMember*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t, double, BiaMember*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorCallString().
	*/
	inline virtual void OperatorCallString(uint32_t, const char*, BiaMember*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	inline virtual void OperatorAssignCallInt_32(uint32_t, int32_t) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	inline virtual void OperatorAssignCallInt_64(uint32_t, int64_t) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	inline virtual void OperatorAssignCallFloat(uint32_t, float) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallDouble(uint32_t, double) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallString(uint32_t, const char*) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	inline virtual void OperatorSelfCall(uint32_t) override
	{
		throw exception::BadCallException("Functions do not support operators.");
	}
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
	}
	/**
	 * @see	BiaMember::Test().
	*/
	inline virtual int32_t Test() override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCall().
	*/
	inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallInt_32().
	*/
	inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallInt_64().
	*/
	inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallFloat().
	*/
	inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallDouble().
	*/
	inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallString().
	*/
	inline virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::BadCallException("Functions cannot be tested.");
	}
	/**
	 * @see	BiaMember::GetMember().
	*/
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
		return this;
		throw exception::SymbolException("Unkown member.");
	}

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	inline virtual void * GetNativeData(NATIVE_TYPE) override
	{
		throw exception::BadCastException("Native type is not supported.");
	}
};

}
}
}