#pragma once

#include <cstddef>
#include <tuple>

#include "native_variable.hpp"
#include "share.hpp"
#include "print.hpp"
#include "string_stream.hpp"


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
	typedef stream::string_stream::size_type size_type;
	typedef stream::string_stream::length_type length_type;
	typedef utility::share<std::tuple<const _Char*, size_type, length_type>> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _string The zero-terminated string.
	 * @param _size The total size of the string.
	 * @param _length The length of the string.
	 *
	 * @throws See utility::share::share().
	*/
	cstring_member(const _Char * _string, size_type _size, length_type _length) : _data(_string, _size, _length)
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
	cstring_member(const data_type & _data) noexcept : _data(_data)
	{
	}
	virtual void print() const override
	{
		print(std::get<0>(_data.get()));
	}
	virtual void copy(member * _destination) override
	{
		_destination->replace_this<cstring_member<_Char>>(std::get<0>(_data.get()), std::get<1>(_data.get()), std::get<2>(_data.get()));
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
	virtual void object_member(member * _destination, machine::string_manager::name_type _name) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int flags() const override
	{
		return F_CONST;
	}
	virtual int32_t test() const override
	{
		return static_cast<int32_t>(std::get<2>(_data.get()) != 0);
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
			return &std::get<0>(_data.get());
		default:
			break;
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	/** The zero-terminated C style string, its size and its length. */
	data_type _data;


	static void print(const char * _string)
	{
		machine::link::print_string(_string);
	}
	template<typename _Ty>
	static void print(const _Ty * _string) noexcept
	{
	}
};

}
}
}