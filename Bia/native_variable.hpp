#pragma once

#include "member.hpp"
#include "undefined_member.hpp"
#include "exception.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class native_variable : public member
{
public:
	virtual void undefine() noexcept override
	{
		replace_this<undefined_member>();
	}
	virtual void execute(member * _instance, member * _destination) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void execute_count(member * _instance, member * _destination, parameter_count _count...) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void execute_format(member * _instance, member * _destination, const char * _format, parameter_count _count...) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	/*virtual void call(member * _instance, member * _destination) override
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
	virtual bool is_custom_type(const std::type_info & _type) const override
	{
		return false;
	}
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
		throw exception::SymbolException("Unkown member.");
	}*/

protected:
	virtual void * get_data(const std::type_info & _type) override
	{
		throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * get_const_data(const std::type_info & _type) const override
	{
		throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
	}
};

}
}
}