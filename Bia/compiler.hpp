#pragma once


#include "exception.hpp"
#include "output_stream.hpp"
#include "toolset.hpp"
#include "report.hpp"
#include "interpreter_id.hpp"
#include "compiler_value.hpp"
#include "temp_counter.hpp"
#include "operator.hpp"
#include "machine_context.hpp"

#include "interpreter.hpp"
#include "interpreter_rule.hpp"
#include "machine_code.hpp"

#define BIA_COMPILER_DEV_INVALID throw 0 /*BIA_IMPLEMENTATION_EXCEPTION("Invalid case.")*/


namespace bia
{
namespace compiler
{

class compiler : public grammar::report_receiver
{
public:
	compiler(stream::output_stream & _output, machine::machine_context & _context);
	compiler(const compiler & _copy) = delete;
	compiler(compiler && _rvalue) = delete;
	~compiler(){ }
	virtual void report(const grammar::report * _begin, const grammar::report * _end) override;
	/**
	 * Finalizes the machine code.
	 *
	 * @since 3.64.127.719
	 * @date 16-May-18
	 *
	 * @throws See machine::platform::toolset::finalize().
	*/
	void finalize();
	machine::machine_code get_code()
	{
		return machine::machine_code({ nullptr, 0 }, machine::machine_schein(_context.get_allocator(), _context.get_executable_allocator()));
	}
	//machine::machine_schein get_machine_schein();

private:
	typedef const grammar::report*(compiler::*handle_function)(const grammar::report*);

	/** The result value for calculating and compiling. */
	compiler_value _value;
	/** A counter for the needed temporary variables. */
	temp_counter _counter;
	/** The compilers toolset for writing the machine code. */
	machine::platform::toolset _toolset;
	machine::machine_context & _context;

	void operation(const compiler_value & _left, framework::operator_type _operator, const compiler_value & _right);
	template<typename _Member>
	void member_operation(_Member && _left, framework::operator_type _operator, const compiler_value & _right)
	{
		switch (_right.get_type()) {
		case compiler_value::VALUE_TYPE::INT:
		case compiler_value::VALUE_TYPE::DOUBLE:
		case compiler_value::VALUE_TYPE::STRING:
		case compiler_value::VALUE_TYPE::MEMBER:
		{
			if (_value.get_type() == compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
				_counter.update(_value.get_value().rt_temp_member);
				//_toolset.call(&framework::member::operator_call, _left.get_value().rt_member, _operator, _);
			} else {
				//_toolset.call(&framework::member::operator_assign_call, _left.get_value().rt_member, _operator, _);
			}

			break;
		}
		case compiler_value::VALUE_TYPE::TEMPORARY_MEMBER:
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
	void constant_operation(const compiler_value & _left, framework::operator_type _operator, const compiler_value & _right);
	void compare_operation(const compiler_value & _left, framework::operator_type _operator, const compiler_value & _right)
	{

	}
	/**
	 * Tests the compiler value and returns a test value.
	 *
	 * @since 3.64.127.716
	 * @date 1-May-18
	 *
	 * @throws 
	*/
	void test_compiler_value();
	/**
	 * Handles a math expression or a math term token.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam _Expression true for math expression, otherwise math term.
	 *
	 * @param _report The math report.
	 *
	 * @throws See handle_math_expression_and_term() and handle_math_factor().
	 *
	 * @return The end of the report.
	*/
	template<bool _Expression = true>
	const grammar::report * handle_math_expression_and_term(const grammar::report * _report)
	{
		constexpr handle_function next = _Expression ? &compiler::handle_math_expression_and_term<false> : &compiler::handle_math_factor;

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
	 * @tparam _Test If the result value should be guaranteed testable.
	 * @tparam _Lambda The callback lambda function.
	 *
	 * @param _report The value report.
	 * @param [in] _callback The callback for safe execution.
	 *
	 * @throws See temp_counter::pop().
	 * @throws See handle_value_insecure().
	 *
	 * @return The end of the report.
	*/
	template<bool _Test, typename _Lambda>
	const grammar::report * handle_value(const grammar::report * _report, _Lambda && _callback)
	{
		// Save old counter
		auto _old = _counter.peek();

		// Handle value
		handle_value_insecure<_Test>(_report);

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
	 * @tparam _Test If the result value should be guaranteed testable.
	 *
	 * @param _report The corresponding report.
	 *
	 * @throws See handle_value_expression() and operation().
	 *
	 * @return The end of the report.
	*/
	template<bool _Test>
	const grammar::report * handle_value_insecure(const grammar::report * _report)
	{
		switch (_report[1].rule_id) {
		case grammar::BGR_VALUE_EXPRESSION:
			handle_value_expression<_Test>(_report + 1);

			break;
		case grammar::BGR_VALUE_HELPER_0:
		{
			// Set identifier
			compiler_value _left;

			_left.set_return(_report[1].content.member);

			// Handle right value expression
			handle_value_expression<false>(_report + 3);

			// Call operator
			operation(_left, _report[2].content.operatorCode, _value);

			break;
		}
		default:
			BIA_COMPILER_DEV_INVALID;
		}

		return _report->content.end;
	}
	template<bool _Test>
	const grammar::report * handle_value_expression(const grammar::report * _report)
	{
		using JUMP = machine::platform::toolset::JUMP;

		const auto _end = _report->content.end;
		auto _test = false;
		///TODO
		do {
			// Handle expression
			_report = handle_condition_expression(_report + 1) + 1;

			// Create test result
			if (_Test || _test || _report < _end) {
				test_compiler_value();
			}

			_test = true;
		} while (_report < _end);

		return _report->content.end;
	}
	const grammar::report * handle_root(const grammar::report * _report);
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
	const grammar::report * handle_root_ignore(const grammar::report * _report);
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
	 * @throws See temp_counter::next(), temp_counter::current() and temp_counter::pop().
	 * @throws Whatever @a _next throws.
	 *
	 * @return The end of the report.
	*/
	const grammar::report * handle_math_expression_and_term_inner(const grammar::report * _report, handle_function _next);
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
	const grammar::report * handle_condition_expression(const grammar::report * _report);
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
	const grammar::report * handle_number(const grammar::report * _report);
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
	const grammar::report * handle_raw_value(const grammar::report * _report);
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
	const grammar::report * handle_math_factor(const grammar::report * _report);
	const grammar::report * handle_member(const grammar::report * _report);
	const grammar::report * handle_instantiation(const grammar::report * _report);
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
	const grammar::report * handle_variable_declaration(const grammar::report * _report);
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
	const grammar::report * handle_print(const grammar::report * _report);
};

}
}