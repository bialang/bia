#pragma once

#include <string>

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
		_length = std::char_traits<char>::length(_string);
	}
	cstring_member(const char * _string, size_t _length) noexcept
	{
		this->_string = _string;
		this->_length = _length;
	}
	virtual void print() const override
	{
		machine::link::print_s(_string);
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<cstring_member>(_string, _length);
	}
	virtual bool is_const() const override
	{
		return true;
	}
	virtual int32_t test() const override
	{
		return static_cast<int32_t>(_length != 0);
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
	/** The length of the string. */
	size_t _length;
};

}
}
}