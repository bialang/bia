#pragma once

#include "native_variable.hpp"
#include "print.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class cstring_member final : public native_variable
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _string The zero-terminated string.
	*/
	cstring_member(const char * _string) noexcept
	{
		this->_string = _string;
	}
	virtual void print() const override
	{
		//machine::link::print(_value);
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
		switch (_type) {
		case NATIVE_TYPE::CONST_STRING:
			return &_string;
		default:
			break;
		}

		throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	/** The zero-terminated C style pointer. */
	const char * _string;
};

}
}
}