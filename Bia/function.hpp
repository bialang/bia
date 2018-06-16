#pragma once

#include "member.hpp"
#include "exception.hpp"
#include "undefined_member.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

/**
 * @brief A function member interface.
 *
 * Functions have only basic functionality and can be executed.
*/
class function : public member
{
public:
	function(machine::machine_context * _machine_context) noexcept : member(_machine_context)
	{
	}
	virtual void undefine() override
	{
		replace_this<undefined_member>();
	}
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right)
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int get_flags() const override
	{
		return F_CONST;
	}
	virtual int32_t test() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t test_member(operator_type _operator, member * _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t test_double(operator_type _operator, double _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int64_t to_int() const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual double to_double() const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual void * get_data(const std::type_info & _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * get_const_data(const std::type_info & _type) const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
};

}
}
}