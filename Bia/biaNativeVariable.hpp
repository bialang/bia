#pragma once

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaException.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class BiaNativeVariable : public BiaMember
{
public:
	/**
	 * @see	BiaMember::Undefine().
	*/
	inline virtual void Undefine() override
	{
		ReplaceObject<BiaUndefined>();
	}
	/**
	 * @see	BiaMember::Call().
	*/
	inline virtual void Call(BiaMember*, BiaMember*) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
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
	 * @see	BiaMember::Instantiate().
	*/
	inline virtual void Instantiate(BiaMember*) override
	{
		throw exception::BadCallException("Invalid instantiation call on native type.");
	}
	/**
	 * @see	BiaMember::InstantiateCount().
	*/
	inline virtual void InstantiateCount(BiaMember*, parameter_count, ...) override
	{
		throw exception::BadCallException("Invalid instantiation call on native type.");
	}
	/**
	 * @see	BiaMember::InstantiateFormat().
	*/
	inline virtual void InstantiateFormat(BiaMember*, parameter_count, const char*, ...) override
	{
		throw exception::BadCallException("Invalid instantiation call on native type.");
	}
	/**
	 * @see	BiaMember::IsType().
	*/
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
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
	 * @see	BiaMember::GetData().
	*/
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Type is not supported.");
	}
};

}
}
}