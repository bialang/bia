#pragma once

#include "biaMember.hpp"
#include "biaException.hpp"


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
	 * @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t, BiaMember*, BiaMember*) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	inline virtual void OperatorCallInt_32(uint32_t, int32_t, BiaMember*) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t, int64_t, BiaMember*) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t, float, BiaMember*) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t, double, BiaMember*) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	inline virtual void OperatorAssignCallInt_32(uint32_t, int32_t) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	inline virtual void OperatorAssignCallInt_64(uint32_t, int64_t) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	inline virtual void OperatorAssignCallFloat(uint32_t, float) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallDouble(uint32_t, double) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	inline virtual void OperatorSelfCall(uint32_t) override
	{
		throw exception::OperatorException("Invalid operator call to a function.");
	}
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
	}
	/**
	 * @see	BiaMember::GetMember().
	*/
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
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