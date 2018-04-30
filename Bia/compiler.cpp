#include "compiler.hpp"
#include "link.hpp"

namespace bia
{
namespace compiler
{

using namespace bia::grammar;

compiler::compiler(stream::output_stream & _output) : _toolset(_output)
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
		return handle_variable_declaration(_report);
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

const grammar::report * compiler::handle_variable_declaration(const grammar::report * _report)
{
	// Handle value and prepare the result for a function call
	handle_value<false>(_report + 2, [&] {
		// Make call
		switch (_value.get_type()) {
		case compiler_value::VALUE_TYPE::INT:
		{
			// Optimize common used constant values
			switch (_value.get_value().rt_int) {
			case 0:
				_toolset.call(&machine::link::instantiate_int_0, _report[1].content.member);

				break;
			case 1:
				_toolset.call(&machine::link::instantiate_int_1, _report[1].content.member);

				break;
			case -1:
				_toolset.call(&machine::link::instantiate_int_n1, _report[1].content.member);

				break;
			default:
			{
				// Can be int32
				if (_value.is_int32()) {
					_toolset.call(&machine::link::instantiate_int32, _report[1].content.member, static_cast<int32_t>(_value.get_value().rt_int));
				} else {
					_toolset.call(&machine::link::instantiate_int64, _report[1].content.member, _value.get_value().rt_int);
				}

				break;
			}
			}

			break;
		}
		case compiler_value::VALUE_TYPE::DOUBLE:
			_toolset.call(&machine::link::instantiate_double, _report[1].content.member, _value.get_value().rt_double);

			break;
		case compiler_value::VALUE_TYPE::STRING:
			_toolset.call(&machine::link::instantiate_string, _report[1].content.member, _value.get_value().rt_string.data);

			break;
		/*case compiler_value::VALUE_TYPE::MEMBER:
			m_toolset.SafeCall(&framework::BiaMember::Clone, m_value.pMember, pVariable);

			break;
		case compiler_value::VALUE_TYPE::TEMPORARY_MEMBER:
			m_toolset.Call(&framework::BiaMember::Clone, machine::architecture::BiaToolset::TemporaryMember(m_value.temporaryResultIndex), pVariable);

			break;
		case compiler_value::VALUE_TYPE::TEST_VALUE_REGISTER:
			m_toolset.Call(&machine::link::InstantiateInt_32, pVariable, machine::architecture::BiaToolset::TestValueResult());

			break;*/
		case compiler_value::VALUE_TYPE::TEST_VALUE_CONSTANT:
		{
			if (_value.get_value().rt_test_result) {
				_toolset.call(&machine::link::instantiate_int_1, _report[1].content.member);
			} else {
				_toolset.call(&machine::link::instantiate_int_n1, _report[1].content.member);
			}

			break;
		}
		/*case compiler_value::VALUE_TYPE::RESULT_REGISTER:
			m_toolset.Call(&framework::BiaMember::Clone, machine::architecture::BiaToolset::ResultValue(), pVariable);

			break;*/
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	});

	return _report->content.end;
}

const grammar::report * compiler::handle_print(const grammar::report * _report)
{
	// Handle value to print
	handle_value<false>(_report + 1, [this] {
		// Call print function
		switch (_value.get_type()) {
		case compiler_value::VALUE_TYPE::INT:
		{
			// Can be int32
			if (_value.is_int32()) {
				_toolset.call(&machine::link::print_i, static_cast<int32_t>(_value.get_value().rt_int));
			} else {
				_toolset.call(&machine::link::print_I, _value.get_value().rt_int);
			}

			break;
		}
		case compiler_value::VALUE_TYPE::DOUBLE:
			_toolset.call(&machine::link::print_d, _value.get_value().rt_double);

			break;
		case compiler_value::VALUE_TYPE::STRING:
			_toolset.call(&machine::link::print_s, _value.get_value().rt_string.data);

			break;
		case compiler_value::VALUE_TYPE::MEMBER:
			_toolset.call(&framework::member::print, _value.get_value().rt_member);

			break;
		case compiler_value::VALUE_TYPE::TEMPORARY_MEMBER:
			_toolset.call(&framework::member::print, machine::platform::toolset::to_temp_member(_value.get_value().rt_temp_member));

			break;
		case compiler_value::VALUE_TYPE::TEST_VALUE_REGISTER:
			_toolset.call(&machine::link::print_b, machine::platform::toolset::get_test_result_value());

			break;
		case compiler_value::VALUE_TYPE::TEST_VALUE_CONSTANT:
		{
			if (_value.get_value().rt_test_result) {
				_toolset.call(&machine::link::print_true);
			} else {
				_toolset.call(&machine::link::print_false);
			}

			break;
		}
		/*case compiler_value::VALUE_TYPE::RESULT_REGISTER:
			_toolset.call(&framework::member::print)
			m_toolset.Call(&framework::BiaMember::Print, machine::architecture::BiaToolset::ResultValue());

			break;*/
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	});

	return _report->content.end;
}

}
}