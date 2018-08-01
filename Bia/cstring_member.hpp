#pragma once

#include <cstddef>
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
	cstring_member(const char * _string) noexcept : cstring_member(_string, std::char_traits<char>::length(_string))
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _string The zero-terminated string.
	 * @param _length The length of the string.
	*/
	cstring_member(const char * _string, size_t _length) noexcept
	{
		this->_string = _string;
		this->_length = _length;
	}
	virtual void print() const override
	{
		machine::link::print_string(_string);
	}
	virtual void copy(member * _destination) override
	{
	}
	virtual void refer(member * _destination) override
	{
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<cstring_member>(_string, _length);
	}
	virtual void operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int flags() const override
	{
		return F_CONST;
	}
	virtual int32_t test() const override
	{
		return static_cast<int32_t>(_length != 0);
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
	virtual void * native_data(native::NATIVE_TYPE _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_native_data(native::NATIVE_TYPE _type) const override
	{
		switch (_type) {
		case NATIVE_TYPE::CONST_STRING:
			return &_string;
		default:
			break;
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
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