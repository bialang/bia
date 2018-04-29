#pragma once

#include <cstdint>
#include <cstddef>

#include "member.hpp"


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
		INT_32,
		INT_64,
		FLOAT,
		DOUBLE,
		STRING,
		MEMBER,
		TEMPORARY_MEMBER,
		/** Defines that the test value is stored in the test register. */
		TEST_VALUE_REGISTER,
		/** Defines that the test value is known at compile time. */
		TEST_VALUE_CONSTANT,
		PARAMETER,
		/** Defines that the result is stored in the result register. */
		RESULT_REGISTER,
		NONE,
	};

	union return_value
	{
		bool rt_test_result;	/**	Defines the constant test _value.	*/
		int32_t rt_int32;
		int64_t rt_int64;
		float rt_float;
		double rt_double;
		struct string
		{
			const char * data;
			size_t length;
		} rt_string;
		framework::member * rt_member;
	//	temp_counter::counter_type rt_temp_member;
		struct parameter
		{
			const char * format;
			framework::member::parameter_count parameter_count;
		//	machine::platform::toolset::pass_count passed_quartets;
		} rt_parameter;
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
	 * Sets the return _value and the type VALUE_TYPE::INT_32.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(int32_t _value) noexcept
	{
		_return_type = VALUE_TYPE::INT_32;
		_return_value.rt_int32 = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::INT_64.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(int64_t _value) noexcept
	{
		_return_type = VALUE_TYPE::INT_64;
		_return_value.rt_int64 = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::FLOAT.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(float _value) noexcept
	{
		_return_type = VALUE_TYPE::FLOAT;
		_return_value.rt_float = _value;
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
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(return_value::string _value) noexcept
	{
		_return_type = VALUE_TYPE::STRING;
		_return_value.rt_string = _value;
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
	/*void set_return(temp_counter::counter_type _value) noexcept
	{
		_return_type = VALUE_TYPE::TEMPORARY_MEMBER;
		_return_value.rt_temp_member = _value;
	}
	/**
	 * Sets the return _value and the type VALUE_TYPE::PARAMETER.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _value Defines the _value.
	*/
	void set_return(return_value::parameter _value) noexcept
	{
		_return_type = VALUE_TYPE::PARAMETER;
		_return_value.rt_parameter = _value;
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
		case VALUE_TYPE::INT_32:
		case VALUE_TYPE::INT_64:
		case VALUE_TYPE::FLOAT:
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
	VALUE_TYPE get_type() const noexcept
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
	return_value get_value() const noexcept
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