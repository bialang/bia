#include "compiler.hpp"


namespace bia
{
namespace compiler
{

using namespace bia::grammar;

compiler::compiler(stream::output_stream & _output)
{
}

void compiler::report(const grammar::report * _begin, const grammar::report * _end)
{
	handle_root(_begin);
}

void compiler::operation(const compiler_value & _left, framework::member::operator_type _operator, const compiler_value & _right)
{
	// Constant operation
	if (_left.is_const() && _right.is_const()) {
		constant_operation(_left, _operator, _right);
	} else {
		///TODO
	}
}

void compiler::constant_operation(const compiler_value & _left, framework::member::operator_type _operator, const compiler_value & _right)
{
	///TODO

	_value.set_return(0);
}

const grammar::report * compiler::handle_root(const grammar::report * _report)
{
	switch (_report->rule_id) {
	case BGR_ROOT_HELPER_0:
	{
		auto _end = _report->content.end;

		++_report;

		// Handle all reports
		while (_report < _end) {
			_report = handle_root(_report) + 1;
		}

		return _end;
	}
	case BGR_VARIABLE_DECLARATION:
		//return HandleVariableDeclaration(p_pReport->content.children);
	case BGR_IF:
		//return HandleIf(p_pReport->content.children);
	case BGR_PRINT:
		//return HandlePrint(p_pReport->content.children);
	case BGR_TEST_LOOP:
		//return HandleTestLoop(p_pReport->content.children);
	//case BGR_IMPORT:
		//return HandleImport(p_pReport->content.children);
	case BGR_VALUE:
		return handle_value<false>(_report, [] {});
	default:
		BIA_COMPILER_DEV_INVALID;
	}
}

const grammar::report * compiler::handle_root_ignore(const grammar::report * _report)
{
	switch (_report->rule_id) {
	case BGR_ROOT_HELPER_0:
	{
		auto _end = _report->content.end;

		++_report;

		// Handle all reports
		while (_report < _end) {
			_report = handle_root_ignore(_report) + 1;
		}

		return _end;
	}
	case BGR_VARIABLE_DECLARATION:
	case BGR_IF:
	case BGR_PRINT:
	case BGR_TEST_LOOP:
	case BGR_IMPORT:
	case BGR_VALUE:
		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_math_expression_and_term(const grammar::report * _report, handle_type _next)
{
	// Handle leftmost math term
	auto _current_count = _counter.next();
	auto i = (this->*_next)(_report + 1) + 1;
	auto _left_value = _value;

	// Pop if not used
	if (_value.get_type() != compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
		_counter.pop(_current_count);
	}

	do {
		// Operator
		auto _operator = i->content.operatorCode;

		// Handle right math term
		i = (this->*_next)(i + 1) + 1;

		// Pop if not used
		if (_value.get_type() != compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
			_counter.pop(_current_count);
		}

		// Call operator
		///TODO: destination?
		operation(_left_value, _operator, _value);

		_left_value = _value;

		// Pop back
		_counter.pop(_current_count);
	} while (i < _report->content.end);

	return _report->content.end;
}

const grammar::report *  compiler::handle_number(const grammar::report * _report)
{
	using TYPE = report::TYPE;

	switch (_report->type) {
	case TYPE::INT_VALUE:
		_value.set_return(_report->content.intValue);

		break;
	case TYPE::FLOAT_VALUE:
		_value.set_return(_report->content.floatValue);

		break;
	case TYPE::DOUBLE_VALUE:
		_value.set_return(_report->content.doubleValue);

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _report;
}

const grammar::report * compiler::handle_raw_value(const grammar::report * _report)
{
	switch (_report[1].token_id) {
	case BV_NUMBER:
		break;
	case BV_TRUE:
		_value.set_return(true);

		break;
	case BV_FALSE:
		_value.set_return(false);

		break;
	case BV_MEMBER:
		handle_member(_report + 1);

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_math_factor(const grammar::report * _report)
{
	switch (_report[1].rule_id) {
	case BGR_VALUE_RAW:
		handle_raw_value(_report + 1);

		break;
	case BGR_VALUE:
		handle_value_insecure<false>(_report + 1);

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_member(const grammar::report * _report)
{


	return _report->content.end;
}

const grammar::report * compiler::handle_instantiation(const grammar::report * _report)
{
	// Set identifier
	_value.set_return(_report[1].content.member);

	// Handle parameters

	// Instantiate

	return _report->content.end;
}

}
}