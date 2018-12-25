#pragma once

#include <string>

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
	machine::machine_code code()
	{
		return machine::machine_code({ nullptr, 0 }, machine::machine_schein(_context.allocator(), _context.executable_allocator()));
	}
	//machine::machine_schein get_machine_schein();

private:
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
	 *
	 * @throws See machine::machine_context::get_address_of_member().
	 *
	 * @return The end of the report.
	*/
	BIA_EXPORT const grammar::report * handle_identifier(const grammar::report * _report);
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
	BIA_EXPORT const grammar::report * handle_import(const grammar::report * _report);
};

}
}
