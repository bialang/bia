#pragma once

#include <cstddef>
#include <string>

#include "native_variable.hpp"
#include "share.hpp"
#include "print.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename _Char>
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
	 *
	 * @throws See cstring_member().
	*/
	cstring_member(const _Char * _string) : cstring_member(_string, std::char_traits<_Char>::length(_string))
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
	 *
	 * @throws See utility::share::share().
	*/
	cstring_member(const _Char * _string, size_t _length) : _data(_string, _length)
	{
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.65.134.742
	 * @date 1-Aug-18
	 *
	 * @param _data The data of the referred object.
	*/
	cstring_member(const utility::share<std::pair<const _Char*, size_t>> & _data) noexcept : _data(_data)
	{
	}
	virtual void print() const override
	{
		//machine::link::print_string(_string);
	}
	virtual void copy(member * _destination) override
	{
		_destination->replace_this<cstring_member<_Char>>(_data.get().first, _data.get().second);
	}
	virtual void refer(member * _destination) override
	{
		_destination->replace_this<cstring_member<_Char>>(_data);
	}
	virtual void clone(member * _destination) override
	{
		copy(_destination);
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
		return static_cast<int32_t>(_data.get().second != 0);
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
			return &_data.get().first;
		default:
			break;
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	/** The zero-terminated C style string and its length. */
	utility::share<std::pair<const _Char*, size_t>> _data;
};

}
}
}