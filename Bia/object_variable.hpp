#pragma once

#include <cstdarg>

#include "config.hpp"
#include "exception.hpp"
#include "member.hpp"
#include "undefined_member.hpp"


namespace bia
{
namespace framework
{
namespace object
{

class object_variable : public member
{
public:
	virtual void BIA_MEMBER_CALLING_CONVENTION undefine() override
	{
		replace_this<undefined_member>();
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override
	{
		refer(_destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_t _operator, const member * _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_t _operator, int32_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_t _operator, int64_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_big_int(member * _destination, operator_t _operator, const detail::big_int * _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_t _operator, double _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_t _operator, member * _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_t _operator, int32_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_t _operator, int64_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_t _operator, double _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int64_t to_int() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual double to_double() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual const char * to_cstring(utility::buffer_builder * _builder) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
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
