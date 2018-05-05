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
	virtual void undefine() override
	{
		replace_this<undefined_member>();
	}
	virtual bool is_const() const override
	{
		return true;
	}
	virtual int32_t test() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override
	{
		throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override
	{
		throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
	}
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