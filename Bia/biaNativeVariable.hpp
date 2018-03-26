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
	inline virtual void Undefine() override
	{
		ReplaceObject<BiaUndefined>();
	}
	inline virtual void Call(BiaMember*, BiaMember*) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	inline virtual void CallCount(BiaMember*, BiaMember*, parameter_count, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	inline virtual void CallFormat(BiaMember*, BiaMember*, parameter_count, const char*, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
	}
	inline virtual void Instantiate(BiaMember*) override
	{
		throw exception::BadCallException("Invalid instantiation call on native type.");
	}
	inline virtual void InstantiateCount(BiaMember*, parameter_count, ...) override
	{
		throw exception::BadCallException("Invalid instantiation call on native type.");
	}
	inline virtual void InstantiateFormat(BiaMember*, parameter_count, const char*, ...) override
	{
		throw exception::BadCallException("Invalid instantiation call on native type.");
	}
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
	}
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
		throw exception::SymbolException("Unkown member.");
	}

protected:
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Type is not supported.");
	}
};

}
}
}