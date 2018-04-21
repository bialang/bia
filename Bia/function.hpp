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