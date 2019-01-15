#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>
#include <cstring>

#include "string_stream.hpp"
#include "big_int.hpp"
#include "virtual_translator.hpp"
#include "report.hpp"


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
		/** The native 64 Bit signed integer type. */
		INT,
		/** The big integer without a limit. */
		BIG_INT,
		/** The native 64 Bit floating point type. */
		DOUBLE,
		/** ASCII or UTF-8 encoded string. */
		STRING,
		/** UTF-16 encoded string. */
		STRING16,
		/** UTF-32 encoded string. */
		STRING32,
		/** A wchar_t string. */
		WSTRING,
		/** A member address. */
		MEMBER,
		/** An index of a temp member. */
		TEMPORARY_MEMBER,
		/** A local member. */
		LOCAL_MEMBER,
		/** Defines that the test value is stored in the test register. */
		TEST_VALUE_REGISTER,
		/** Defines that the test value is known at compile time. */
		TEST_VALUE_CONSTANT,
		/** No value. */
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
		grammar::report::member_t rt_member;
		machine::virtual_machine::member_index_t rt_temp_member;
		machine::virtual_machine::member_index_t rt_local_member;
	};

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	*/
	compiler_value() noexcept
	{
		set_return();
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::NONE.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	*/
	void set_return() noexcept
	{
		clear();

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
		clear();

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
		clear();

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
		clear();

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
		clear();

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
		clear();

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
		clear();

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
		clear();

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
		clear();

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
		clear();

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
	void set_return_member(grammar::report::member_t _value) noexcept
	{
		clear();

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
	void set_return_temp(machine::virtual_machine::member_index_t _value) noexcept
	{
		clear();

		_return_type = VALUE_TYPE::TEMPORARY_MEMBER;
		_return_value.rt_temp_member = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::LOCAL_MEMBER.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param _value The value.
	*/
	void set_return_local(machine::virtual_machine::member_index_t _value) noexcept
	{
		clear();

		_return_type = VALUE_TYPE::LOCAL_MEMBER;
		_return_value.rt_local_member = _value;
	}
	/**
	 * Expands this value to the member types (VALUE_TYPE::MEMBER, VALUE_TYPE::TEMPORARY_MEMBER and VALUE_TYPE::LOCAL_MEMBER)
	 *
	 * @since 3.72.149.809
	 * @date 27-Dec-18
	 *
	 * @tparam Default The default value type.
	 * @tparam Lambda The lamdba type.
	 *
	 * @param _default The default value if this is not a member.
	 * @param _lambda The callback function that is called. The callback gets the - as only parameter - the expaneded value.
	 *
	 * @throws See @a _lambda.
	*/
	template<typename Default, typename Lambda>
	void expand_to_member(Default _default, Lambda && _lambda) const
	{
		// Save to member variable
		if (_return_type == VALUE_TYPE::MEMBER) {
			_lambda(_return_value.rt_member);
		} // Save to temp member
		else if (_return_type == VALUE_TYPE::TEMPORARY_MEMBER) {
			BIA_NOT_IMPLEMENTED;
			//_lambda(machine::platform::toolset::to_temp_member(_return_value.rt_temp_member));
		} // Save to local member
		else if (_return_type  == VALUE_TYPE::LOCAL_MEMBER) {
			BIA_NOT_IMPLEMENTED;
			//_lambda(machine::platform::toolset::to_local_member(_return_value.rt_local_member));
		} else {
			_lambda(_default);
		}
	}
	/**
	 * Checks whether this value is a member or not.
	 *
	 * @since 3.72.149.809
	 * @date 27-Dec-18
	 *
	 * @return true if this type is one of the following: VALUE_TYPE::MEMBER, VALUE_TYPE::TEMPORARY_MEMBER or VALUE_TYPE::LOCAL_MEMBER
	*/
	bool is_member() const noexcept
	{
		return _return_type == VALUE_TYPE::MEMBER || _return_type == VALUE_TYPE::TEMPORARY_MEMBER || _return_type == VALUE_TYPE::LOCAL_MEMBER;
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
	/**
	 * Compares this compiler value to another one.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param _right The other compiler value.
	 *
	 * @return true if they are the same, otherwise false.
	*/
	bool operator==(const compiler_value & _right) const noexcept
	{
		return _return_type == _right._return_type && !std::memcmp(&_return_value, &_right._return_value, sizeof(_return_value));
	}
	/**
	 * Compares this compiler value to another one.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	 *
	 * @param _right The other compiler value.
	 *
	 * @return true if they are different, otherwise false.
	*/
	bool operator!=(const compiler_value & _right) const noexcept
	{
		return !operator==(_right);
	}

private:
	/** Defines the type of the last operation result. */
	VALUE_TYPE _return_type;
	/** Defines the _value of the last operation result. */
	return_value _return_value;

	/**
	 * Clears the return value completely.
	 *
	 * @since 3.71.149.808
	 * @date 26-Dec-18
	*/
	void clear() noexcept
	{
		std::memset(&_return_value, 0, sizeof(_return_value));
	}
};

}
}
