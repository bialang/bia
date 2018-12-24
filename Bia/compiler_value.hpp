#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>

#include "member.hpp"
#include "temp_counter.hpp"
#include "string_stream.hpp"
#include "big_int.hpp"


namespace bia
{
namespace compiler
{

/**
 * @brief A value for the compiler.
 *
 * A value that can be of different types for compiling and optimizations.
 *
 * @see @ref compiler
*/
class compiler_value
{
public:
	enum class VALUE_TYPE
	{
		INT,
		BIG_INT,
		DOUBLE,
		/** ASCII or UTF-8 encoded string. */
		STRING,
		/** UTF-16 encoded string. */
		STRING16,
		/** UTF-32 encoded string. */
		STRING32,
		/** A wchar_t string. */
		WSTRING,
		MEMBER,
		TEMPORARY_MEMBER,
		/** Defines that the test value is stored in the test register. */
		TEST_VALUE_REGISTER,
		/** Defines that the test value is known at compile time. */
		TEST_VALUE_CONSTANT,
		NONE,
	};

	union return_value
	{
		/** The constant test value. */
		bool rt_test_result;
		/** A constant 64 bit integer. */
		int64_t rt_int;
		/** A constant big integer. */
		dependency::big_int * rt_big_int;
		/** A constant floating point. */
		double rt_double;
		struct string
		{
			const int8_t * data;
			stream::string_stream::size_type size;
			stream::string_stream::length_type length;
		} rt_string;
		framework::member * rt_member;
		temp_counter::counter_type rt_temp_member;
	};

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	*/
	compiler_value() noexcept
	{
		_return_type = VALUE_TYPE::NONE;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::NONE.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	*/
	void set_return() noexcept
	{
		_return_type = VALUE_TYPE::NONE;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::TEST_VALUE_REGISTER.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	*/
	void set_return_test() noexcept
	{
		_return_type = VALUE_TYPE::TEST_VALUE_REGISTER;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::TEST_VALUE_CONSTANT.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(bool _value) noexcept
	{
		_return_type = VALUE_TYPE::TEST_VALUE_CONSTANT;
		_return_value.rt_test_result = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::INT.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(int64_t _value) noexcept
	{
		_return_type = VALUE_TYPE::INT;
		_return_value.rt_int = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::BIG_INT.
	 *
	 * @since 3.68.140.792
	 * @date 13-Nov-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(dependency::big_int * _value) noexcept
	{
		_return_type = VALUE_TYPE::BIG_INT;
		_return_value.rt_big_int = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::DOUBLE.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(double _value) noexcept
	{
		_return_type = VALUE_TYPE::DOUBLE;
		_return_value.rt_double = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::STRING.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _value The string.
	 * @param _size The size of the string.
	 * @param _length The length of the string.
	*/
	void set_return(const char * _value, stream::string_stream::size_type _size, stream::string_stream::length_type _length) noexcept
	{
		_return_type = VALUE_TYPE::STRING;
		_return_value.rt_string.data = reinterpret_cast<const int8_t*>(_value);
		_return_value.rt_string.size = _size;
		_return_value.rt_string.length = _length;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::STRING16.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _value The string.
	 * @param _size The size of the string.
	 * @param _length The length of the string.
	*/
	void set_return(const char16_t * _value, stream::string_stream::size_type _size, stream::string_stream::length_type _length) noexcept
	{
		_return_type = VALUE_TYPE::STRING16;
		_return_value.rt_string.data = reinterpret_cast<const int8_t*>(_value);
		_return_value.rt_string.size = _size;
		_return_value.rt_string.length = _length;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::STRING32.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _value The string.
	 * @param _size The size of the string.
	 * @param _length The length of the string.
	*/
	void set_return(const char32_t * _value, stream::string_stream::size_type _size, stream::string_stream::length_type _length) noexcept
	{
		_return_type = VALUE_TYPE::STRING32;
		_return_value.rt_string.data = reinterpret_cast<const int8_t*>(_value);
		_return_value.rt_string.size = _size;
		_return_value.rt_string.length = _length;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::STRING.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _value The string.
	 * @param _size The size of the string.
	 * @param _length The length of the string.
	*/
	void set_return(const wchar_t * _value, stream::string_stream::size_type _size, stream::string_stream::length_type _length) noexcept
	{
		_return_type = VALUE_TYPE::WSTRING;
		_return_value.rt_string.data = reinterpret_cast<const int8_t*>(_value);
		_return_value.rt_string.size = _size;
		_return_value.rt_string.length = _length;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::MEMBER.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(framework::member * _value) noexcept
	{
		_return_type = VALUE_TYPE::MEMBER;
		_return_value.rt_member = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::TEMPORARY_MEMBER.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return_temp(temp_counter::counter_type _value) noexcept
	{
		_return_type = VALUE_TYPE::TEMPORARY_MEMBER;
		_return_value.rt_temp_member = _value;
	}
	/**
	 * Checks whether the int value can be stored in a int32 type.
	 *
	 * @since 3.64.127.716
	 * @date 30-Apr-18
	 *
	 * @return true if the int can be stored in a int32 type, otherwise false.
	*/
	bool is_int32() const noexcept
	{
		return _return_type == VALUE_TYPE::INT && _return_value.rt_int <= std::numeric_limits<int32_t>::max() && _return_value.rt_int >= std::numeric_limits<int32_t>::min();
	}
	/**
	 * Checks wheter the held value is constant.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @return true if the value is constant, otherwise false.
	*/
	bool is_const() const noexcept
	{
		switch (_return_type) {
		case VALUE_TYPE::INT:
		case VALUE_TYPE::DOUBLE:
		case VALUE_TYPE::STRING:
		case VALUE_TYPE::TEST_VALUE_CONSTANT:
			return true;
		default:
			break;
		}

		return false;
	}
	/**
	 * Returns the type of the value.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @return The type.
	*/
	VALUE_TYPE type() const noexcept
	{
		return _return_type;
	}
	/**
	 * Returns the value.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @return The value.
	*/
	return_value value() const noexcept
	{
		return _return_value;
	}

private:
	/** Defines the type of the last operation result. */
	VALUE_TYPE _return_type;
	/** Defines the _value of the last operation result. */
	return_value _return_value;
};

}
}