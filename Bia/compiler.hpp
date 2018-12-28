#pragma once

#include <string>
#include <functional>
#include <vector>

#include "config.hpp"
#include "exception.hpp"
#include "output_stream.hpp"
#include "toolset.hpp"
#include "report.hpp"
#include "interpreter_id.hpp"
#include "compiler_value.hpp"
#include "temp_counter.hpp"
#include "operator.hpp"
#include "machine_context.hpp"
#include "compile_normal_operation.hpp"
#include "compiler_loop_tracker.hpp"
#include "scope_handler.hpp"

#include "interpreter.hpp"
#include "interpreter_rule.hpp"
#include "machine_code.hpp"



namespace bia
{
namespace compiler
{

class compiler : public grammar::report_receiver
{
public:
	BIA_EXPORT compiler(stream::output_stream & _output, machine::machine_context & _context);
	compiler(const compiler & _copy) = delete;
	compiler(compiler && _rvalue) = delete;
	~compiler()
	{
	}
	BIA_EXPORT virtual void report(const grammar::report * _begin, const grammar::report * _end) override;
	/**
	 * Finalizes the machine code.
	 *
	 * @since 3.64.127.719
	 * @date 16-May-18
	 *
	 * @throws See machine::platform::toolset::finalize().
	*/
	BIA_EXPORT void finalize();
	//machine::machine_schein get_machine_schein();

private:
	enum class VARIABLE_TYPE
	{
		UNKNOWN,
		DEFINITELY_LOCAL,
		DEFINITELY_GLOBAL
	};

	typedef const grammar::report*(compiler::*handle_function)(const grammar::report*);

	/** The result value for calculating and compiling. */
	compiler_value _value;
	/** A counter for the needed temporary variables. */
	temp_counter _counter;
	/** Tracks all open loops. */
	compiler_loop_tracker _loop_tracker;
	/** The compilers toolset for writing the machine code. */
	machine::platform::toolset _toolset;
	/** The context. */
	machine::machine_context & _context;
	/** Manages all scopes and their local variables. */
	scope_handler _scope_handler;
	/** A list of task that need to be executed before the script is finished. */
	std::vector<std::pair<machine::platform::toolset::position_type, std::function<void()>>> _finish_tasks;

	/**
	 * Executes the given member.
	 *
	 * @remarks The @ref compiler::_value must contain the temporary destination.
	 *
	 * @since 3.67.135.751
	 * @date 6-Aug-18
	 *
	 * @tparam Type The type of the member.
	 *
	 * @param _member The member.
	 * @param _format The format of the passed parameters.
	 * @param _mixed Whether some constants were passed too or not.
	 * @param _count The amount of passed parameters.
	 * @param [in] _passer The varg passer.
	 *
	 * @throws See machine::string_manager::format_address().
	 * @throws See machine::platform::toolset::call().
	*/
	template<typename Type>
	void handle_parameter_execute(Type _member, const std::string & _format, bool _mixed, uint32_t _count, machine::platform::varg_member_passer & _passer)
	{
		auto _destination = machine::platform::toolset::to_temp_member(_value.value().rt_temp_member);

		// Execute without parameters
		if (!_count) {
			_toolset.call_virtual(&framework::member::execute, _member, _destination);
		} // Formatted execute
		else if (_mixed) {
			auto _format_ptr = _context.string_manager().format_address(_format.data(), _format.length());

			_toolset.call_virtual(&framework::member::execute_format, _member, _passer, _destination, _format_ptr, _count);
		} // Only members as parameters
		else {
			_toolset.call_virtual(&framework::member::execute_count, _member, _passer, _destination, machine::platform::reserved_parameter(), _count);
		}
	}
	template<typename Destination>
	void handle_variable_declaration_helper(compiler_value _expression, Destination _destination)
	{
		using T = machine::platform::toolset;
		using VT = compiler_value::VALUE_TYPE;

		switch (_expression.type()) {
		case VT::TEST_VALUE_CONSTANT:
			_expression.set_return(static_cast<int64_t>(_expression.value().rt_test_result));
		case VT::INT:
		{
			// Optimize common used constant values
			switch (_expression.value().rt_int) {
			case 0:
				_toolset.call_static(&machine::link::instantiate_int_0, _destination);

				break;
			case 1:
				_toolset.call_static(&machine::link::instantiate_int_1, _destination);

				break;
			case -1:
				_toolset.call_static(&machine::link::instantiate_int_n1, _destination);

				break;
			default:
			{
				// Can be int32
				if (_expression.is_int32()) {
					_toolset.call_static(&machine::link::instantiate_int32, _destination, static_cast<int32_t>(_expression.value().rt_int));
				} else {
					_toolset.call_static(&machine::link::instantiate_int64, _destination, _expression.value().rt_int);
				}

				break;
			}
			}

			break;
		}
		case VT::BIG_INT:
			_toolset.call_static(&machine::link::instantiate_big_int, _destination, _expression.value().rt_big_int);

			break;
		case VT::DOUBLE:
			_toolset.call_static(&machine::link::instantiate_double, _destination, _expression.value().rt_double);

			break;
		case VT::STRING:
			_toolset.call_static(&machine::link::instantiate_string, _destination, _expression.value().rt_string.data, _expression.value().rt_string.size, _expression.value().rt_string.length);

			break;
		case VT::MEMBER:
			_toolset.call_virtual(&framework::member::clone, _expression.value().rt_member, _destination);

			break;
		case VT::TEMPORARY_MEMBER:
			_toolset.call_virtual(&framework::member::clone, T::to_temp_member(_expression.value().rt_temp_member), _destination);

			break;
		case VT::LOCAL_MEMBER:
			_toolset.call_virtual(&framework::member::clone, T::to_local_member(_expression.value().rt_local_member), _destination);

			break;
		case VT::TEST_VALUE_REGISTER:
			_toolset.call_static(&machine::link::instantiate_int32, _destination, T::test_result_value());

			break;
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	}
	/**
	 * Tests the compiler value and returns a test value.
	 *
	 * @since 3.64.127.716
	 * @date 1-May-18
	 *
	 * @throws
	*/
	BIA_EXPORT void test_compiler_value();
	/**
	 * Passes one parameter item.
	 *
	 * @since 3.67.135.751
	 * @date 6-Aug-18
	 *
	 * @param [in,out] _passer The varg parameter passer.
	 *
	 * @throws See machine::platform::varg_member_passer::pass().
	 *
	 * @return The char of the item type.
	*/
	BIA_EXPORT char handle_parameter_item(machine::platform::varg_member_passer & _passer);
	/**
	 * Handles a math expression or a math term token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam Expression true for math expression, otherwise math term.
	 *
	 * @param _report The math report.
	 *
	 * @throws See handle_math_expression_and_term() and handle_math_factor().
	 *
	 * @return The end of the report.
	*/
	template<bool Expression = true>
	const grammar::report * handle_math_expression_and_term(const grammar::report * _report)
	{
		constexpr handle_function next = Expression ? &compiler::handle_math_expression_and_term<false> : &compiler::handle_math_factor;

		// Only one math expression or term to handle
		if (_report[1].content.end == _report->content.end) {
			(this->*next)(_report + 1);
		} else {
			handle_math_expression_and_term_inner(_report, next);
		}

		return _report->content.end;
	}
	/**
	 * Handles the value rule.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @tparam Test If the result value should be guaranteed testable.
	 * @tparam Lambda The callback lambda function.
	 *
	 * @param _report The value report.
	 * @param [in] _callback The callback for safe execution.
	 *
	 * @throws See temp_counter::pop().
	 * @throws See handle_value_insecure().
	 *
	 * @return The end of the report.
	*/
	template<bool Test, typename Lambda>
	const grammar::report * handle_value(const grammar::report * _report, Lambda && _callback)
	{
		// Save old counter
		auto _old = _counter.peek();

		// Handle value
		handle_value_insecure<Test>(_report);

		// Execute callback
		_callback();

		// Reset counter
		_counter.pop(_old);

		return _report->content.end;
	}
	/**
	 * Handles the value rule.
	 *
	 * @remarks This function does not handle the counter variable.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @tparam Test If the result value should be guaranteed testable.
	 *
	 * @param _report The corresponding report.
	 *
	 * @throws See handle_value_expression() and operation().
	 * @throws See compile_normal_operation::operate().
	 *
	 * @return The end of the report.
	*/
	template<bool Test>
	const grammar::report * handle_value_insecure(const grammar::report * _report)
	{
		switch (_report[1].rule_id) {
		case grammar::BGR_VARIABLE_DECLARATION_INLINE:
			handle_variable_declaration(_report + 1);

			break;
		case grammar::BGR_VALUE_EXPRESSION:
			handle_value_expression(_report + 1);

			break;
		case grammar::BGR_VALUE_HELPER_0:
		{
			// Set identifier
			handle_identifier(_report + 1);

			auto _left = _value;

			// Handle right value expression
			handle_value_expression(_report + 3);

			auto _right = _value;

			// Reset destination
			_value.set_return();

			// Call assign operator
			compile_normal_operation(_toolset, _value).operate(_left, _report[2].content.operator_code, _right);

			// Set left as return
			_value = _left;

			break;
		}
		default:
			BIA_IMPLEMENTATION_ERROR;
		}

		// Test
		if (Test) {
			test_compiler_value();
		}

		return _report->content.end;
	}
	BIA_EXPORT const grammar::report * handle_value_expression(const grammar::report * _report);
	BIA_EXPORT const grammar::report * handle_root(const grammar::report * _report);
	/**
	 * Handle the root without compiling it. This is only used to get the last report.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @param _report The root report.
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_root_ignore(const grammar::report * _report);
	/**
	 * Handles a math expression or a math term token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _report The math report.
	 * @param _next The next function hop. Should handle_math_expression_and_term<false>() or handle_math_factor().
	 *
	 * @throws See operation().
	 * @throws See temp_counter::next(), temp_counter::update() and temp_counter::pop().
	 * @throws Whatever @a _next throws.
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_math_expression_and_term_inner(const grammar::report * _report, handle_function _next);
	/**
	 * Handles a condition expression token.
	 *
	 * @since 3.64.127.716
	 * @date 1-May-18
	 *
	 * @param _report The condition expression token.
	 *
	 * @throws See handle_math_expression_and_term() and compare_operation().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_condition_expression(const grammar::report * _report);
	/**
	 * Handles a number token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _report The number report.
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_number(const grammar::report * _report);
	/**
	 * Handles a raw value token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _report The raw value token.
	 *
	 * @throws See handle_member().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_raw_value(const grammar::report * _report);
	/**
	 * Handles a single identifier.
	 *
	 * @since 3.64.132.731
	 * @date 17-Jun-18
	 *
	 * @param _report The identifier.
	 * @param _type (Optional) The type of the variable.
	 *
	 * @throws See machine::machine_context::get_address_of_member().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_identifier(const grammar::report * _report, VARIABLE_TYPE _type = VARIABLE_TYPE::UNKNOWN);
	/**
	 * Handles a math factor token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _report The math factor token.
	 *
	 * @throws See handle_raw_value() and handle_value_insecure().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_math_factor(const grammar::report * _report);
	/**
	 * Handles the member token.
	 *
	 * @since 3.67.135.751
	 * @date 6-Aug-18
	 *
	 * @param _report The member token.
	 *
	 * @throws See handle_string(), handle_identifier() and handle_parameter().
	 * @throws See machine::platform::toolset::call().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_member(const grammar::report * _report);
	/**
	 * Handles the parameter token.
	 *
	 * @since 3.64.127.716
	 * @date 6-Aug-18
	 *
	 * @param _report The parameter token.
	 *
	 * @throws See handle_parameter_execute(), handle_parameter_item() and handle_value_insecure().
	 * @throws See temp_counter::pop().
	 * @throws See machine::platform::toolset::save_result_value().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_parameter(const grammar::report * _report);
	BIA_EXPORT const grammar::report * handle_string(const grammar::report * _report);
	/**
	 * Handles a variable declaration token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _report The variable declaration token.
	 *
	 * @throws See handle_value().
	 * @throws See machine::platform::toolset::call().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_variable_declaration(const grammar::report * _report);
	/**
	 * Handles an if statement.
	 *
	 * @since 3.64.132.731
	 * @date 17-Jun-18
	 *
	 * @param _report The statement.
	 *
	 * @throws See handle_value(), handle_root() and handle_root_ignore().
	 * @throws See machine::platform::toolset::jump() and stream::output_stream::position().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_if(const grammar::report * _report);
	/**
	 * Handles a print token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _report The print token.
	 *
	 * @throws See handle_value().
	 * @throws See machine::platform::toolset::call().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_print(const grammar::report * _report);
	BIA_EXPORT const grammar::report * handle_test_loop(const grammar::report * _report);
	BIA_EXPORT const grammar::report * handle_loop_control(const grammar::report * _report);
	BIA_EXPORT const grammar::report * handle_import(const grammar::report * _report);
};

}
}
