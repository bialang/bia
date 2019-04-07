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
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(machine::stack * _stack, member * _destination) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(machine::stack * _stack, member * _destination, void * _reserved, parameter_count_t _count) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(machine::stack * _stack, member * _destination, const char * _format, parameter_count_t _count) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}

protected:
	virtual int32_t int32_data(bool & _success) const override
	{
		return 0;
	}
	virtual int64_t int64_data(bool & _success) const override
	{
		return 0;
	}
	virtual double double_data(bool & _success) const override
	{
		return 0.0;
	}
	virtual void * data(const std::type_info & _type, bool & _success) override
	{
		return nullptr;
	}
	virtual const void * const_data(const std::type_info & _type, bool & _success) const override
	{
		return nullptr;
	}
};

}
}
}
