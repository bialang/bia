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
	virtual void BIA_MEMBER_CALLING_CONVENTION undefine() override
	{
		replace_this<undefined_member>();
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count, machine::stack * _stack) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count, machine::stack * _stack) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}

protected:
	virtual void * data(const std::type_info & _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_data(const std::type_info & _type) const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
};

}
}
}
