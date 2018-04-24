#pragma once


#include "exception.hpp"
#include "output_stream.hpp"
#include "toolset.hpp"
#include "report.hpp"
#include "interpreter_ids.hpp"
#include "compiler_value.hpp"
#include "temp_counter.hpp"

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
	compiler(stream::output_stream & _output);
	compiler(const compiler & _copy) = delete;
	compiler(compiler && _rvalue) = delete;
	~compiler();
	virtual void report(const grammar::report * _begin, const grammar::report * _end) override;
	void finalize();
	machine::machine_code get_code();
	//machine::machine_schein get_machine_schein();

private:
	/** The result value for calculating and compiling. */
	compiler_value _value;
	/** A counter for the needed temporary variables. */
	temp_counter _counter;
	
	/**
	 * Handles the value rule.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @tparam _Test If the result value should be guaranteed testable.
	 * @tparam _Lambda The callback lambda function.
	 *
	 * @param _report The corresponding report.
	 * @param [in] _callback The callback for safe execution.
	 *
	 * @throws See temp_counter::peek().
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
	 * @throws See handle_value_expression().
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
			// Identifier
			_report[1].content.member;
			// Operator
			_report[2].content.operatorCode;

			// Handle right value expression
			handle_value_expression<false>(_report + 3);

			// Call operator

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
		return _report->content.end;
	}
	const grammar::report * handle_root(const grammar::report * _report);
	/**
	 * Handle the root without compiling it. This is only used to get the last report.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @param _repot The corresponding report.
	 *
	 * @return The end of the report.
	*/
	const grammar::report * handle_root_ignore(const grammar::report * _report);
	const grammar::report * handle_number(const grammar::report * _report);
	const grammar::report * handle_raw_value(const grammar::report * _report);
	const grammar::report * handle_member(const grammar::report * _report);
	const grammar::report * handle_instantiation(const grammar::report * _report);
};

}
}