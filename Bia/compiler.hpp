#pragma once

#include <cstdint>

#include "exception.hpp"
#include "output_stream.hpp"
#include "toolset.hpp"
#include "member.hpp"
#include "report_bundle.hpp"
#include "interpreter.hpp"
#include "interpreter_rule.hpp"

#define BIA_COMPILER_DEV_INVALID throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.")


namespace bia
{
namespace compiler
{

class compiler : public grammar::report_receiver
{
public:
	/**
	 * Constructor.
	 *
	 * @param [in] p_output	Defines the output stream for the machine code.
	 * @param [in] p_context	Defines the machine context.
	 * @param [in] p_pAllocator	Defines the memory allocator.
	 */
	compiler(stream::output_stream & _output);
	compiler(const compiler & _copy) = delete;
	compiler(compiler && _rvalue) = delete;
	~compiler();
	virtual void report(const grammar::report * _begin, const grammar::report * _end) override;
	//machine::machine_schein get_machine_schein();

private:
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

	/**	Defines the compiler toolset for the specific C++ compiler and architecture.	*/
	//machine::platform::toolset _toolset;
	/**	Defines the context for which this script should be compiled.	*/
	//machine::machine_context & _context;
	//machine::machine_schein _machine_schein;

	//machine::platform::toolset::temp_members parameter;	/**	Used for initializing and finalizing the code.	*/
	//temp_counter temp_variable_counter;	/**	Defines the temporary address counter for temporary storage.	*/

	VALUE_TYPE _return_type;	/**	Defines the type of the last operation result.	*/
	return_value _return_value;	/**	Defines the _value of the last operation result.	*/


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
	const grammar::report * handle_root(const grammar::report * _report);
	const grammar::report * handle_number(const grammar::report * _report);
	const grammar::report * handle_raw_value(const grammar::report * _report);
	const grammar::report * handle_member(const grammar::report * _report);
	const grammar::report * handle_instantiation(const grammar::report * _report);
};

}
}