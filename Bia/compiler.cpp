#include "compiler.hpp"
#include "link.hpp"
#include "compile_compare_operation.hpp"
#include "buffer_output_stream.hpp"
#include "string_stream.hpp"

#include <vector>


namespace bia
{
namespace compiler
{

using namespace bia::grammar;

compiler::compiler(stream::output_stream & _output, machine::machine_context & _context) : _toolset(_output, &_context), _context(_context), _scope_handler(_toolset)
{
}

void compiler::report(const grammar::report * _begin, const grammar::report * _end)
{
	handle_root(_begin);
}

void compiler::finalize()
{
	_toolset.finalize(_counter.max());

	auto _end = _toolset.output_stream().position();

	// Finish tasks
	for (auto & _task : _finish_tasks) {
		_toolset.output_stream().set_position(_task.first);
		_task.second();
	}

	_toolset.output_stream().set_position(_end);
}

void compiler::test_compiler_value()
{
	using VT = compiler_value::VALUE_TYPE;

	switch (_value.type()) {
	case VT::INT:
		_value.set_return(_value.value().rt_int != 0);

		break;
	case VT::DOUBLE:
		_value.set_return(_value.value().rt_double != 0.);

		break;
	case VT::STRING:
		_value.set_return(_value.value().rt_string.length != 0);

		break;
	case VT::MEMBER:
		_toolset.call_virtual(&framework::member::test, _value.value().rt_member);
		_value.set_return_test();
		_toolset.write_test();

		break;
	case VT::TEMPORARY_MEMBER:
		_toolset.call_virtual(&framework::member::test, machine::platform::toolset::to_temp_member(_value.value().rt_temp_member));
		_value.set_return_test();
		_toolset.write_test();

		break;
	case VT::LOCAL_MEMBER:
		_toolset.call_virtual(&framework::member::test, machine::platform::toolset::to_local_member(_value.value().rt_local_member));
		_value.set_return_test();
		_toolset.write_test();

		break;
	case VT::TEST_VALUE_REGISTER:
		_toolset.write_test();
	case VT::TEST_VALUE_CONSTANT:
		break;
	default:
		BIA_IMPLEMENTATION_ERROR;
	}
}

char compiler::handle_parameter_item(machine::platform::varg_member_passer & _passer)
{
	using VT = compiler_value::VALUE_TYPE;

	switch (_value.type()) {
	case VT::TEST_VALUE_CONSTANT:
		_value.set_return(static_cast<int64_t>(_value.value().rt_test_result));
	case VT::INT:
	{
		if (_value.is_int32()) {
			_passer.pass_varg(static_cast<int32_t>(_value.value().rt_int));

			return 'i';
		}

		_passer.pass_varg(_value.value().rt_int);

		return 'I';
	}
	case VT::DOUBLE:
		_passer.pass_varg(_value.value().rt_double);

		return 'd';
	case VT::STRING:
		_passer.pass_varg(_value.value().rt_string.data);

		return 'a';
	case VT::STRING16:
		_passer.pass_varg(_value.value().rt_string.data);

		return 'u';
	case VT::STRING32:
		_passer.pass_varg(_value.value().rt_string.data);

		return 'U';
	case VT::WSTRING:
		_passer.pass_varg(_value.value().rt_string.data);

		return 'w';
	case VT::MEMBER:
		_passer.pass_varg(_value.value().rt_member);

		return 'M';
	case VT::TEMPORARY_MEMBER:
		_passer.pass_varg(machine::platform::toolset::to_temp_member(_value.value().rt_temp_member));

		return 'M';
	case VT::LOCAL_MEMBER:
		_passer.pass_varg(machine::platform::toolset::to_local_member(_value.value().rt_local_member));

		return 'M';
	case VT::TEST_VALUE_REGISTER:
		_passer.pass_varg(machine::platform::toolset::test_result_value());

		return 'i';
	default:
		BIA_IMPLEMENTATION_ERROR;
	}
}

const grammar::report * compiler::handle_value_expression(const grammar::report * _report)
{
	using JUMP = machine::platform::toolset::JUMP;

	const auto _end = _report->content.end;
	auto _test = false;
	///TODO
	do {
		// Handle expression
		_report = handle_condition_expression(_report + 1) + 1;

		// Create test result
		if (_test || _report < _end) {
			test_compiler_value();
		}

		_test = true;
	} while (_report < _end);

	return _report->content.end;
}

const grammar::report * compiler::handle_root(const grammar::report * _report)
{
	auto _scope_opened = false;

	switch (_report->rule_id) {
	case BGR_ROOT:
	{
		_scope_handler.open_scope();

		_scope_opened = true;
		++_report;
	}
	case BGR_ROOT_HELPER_0:
	{
		auto _end = _report->content.end;

		++_report;

		// Handle all reports
		while (_report < _end) {
			_report = handle_root(_report);
		}

		if (_scope_opened) {
			_scope_handler.close_scope();
		}

		return _end;
	}
	case BGR_VARIABLE_DECLARATION:
		return handle_variable_declaration(_report);
	case BGR_IF:
		return handle_if(_report);
	case BGR_PRINT:
		return handle_print(_report);
	case BGR_TEST_LOOP:
		return handle_test_loop(_report);
	case BGR_CONTROL_STATEMENT:
		return handle_loop_control(_report);
	case BGR_IMPORT:
		return handle_import(_report);
	case BGR_VALUE:
		_value.set_return();

		return handle_value<false>(_report, [] {});
	default:
		BIA_IMPLEMENTATION_ERROR;
	}
}

const grammar::report * compiler::handle_root_ignore(const grammar::report * _report)
{
	switch (_report->rule_id) {
	case BGR_ROOT:
		++_report;
	case BGR_ROOT_HELPER_0:
	/*{
		auto _end = _report->content.end;

		++_report;

		// Handle all reports
		while (_report < _end) {
			_report = handle_root_ignore(_report);
		}

		return _end;
	}*/
	case BGR_VARIABLE_DECLARATION:
	case BGR_IF:
	case BGR_PRINT:
	case BGR_TEST_LOOP:
	case BGR_IMPORT:
	case BGR_VALUE:
		break;
	default:
		BIA_IMPLEMENTATION_ERROR;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_math_expression_and_term_inner(const grammar::report * _report, handle_function _next)
{
	// Handle leftmost math term
	auto _old_counter = _counter.peek();
	auto i = (this->*_next)(_report + 1);
	auto _left = _value;

	// Pop if not used
	if (_value.type() != compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
		_counter.pop(_old_counter);
	}

	do {
		// Operator
		auto _operator = i->content.operator_code;

		// Handle right math term
		i = (this->*_next)(i + 1);

		// Pop if not used and set destination
		auto _right = _value;

		// Get the lower one
		if (_left.type() == compiler_value::VALUE_TYPE::TEMPORARY_MEMBER && _right.type() == compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
			_value.set_return_temp(_left.value().rt_temp_member < _right.value().rt_temp_member ? _left.value().rt_temp_member : _right.value().rt_temp_member);
		} else if (_left.type() == compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
			_value.set_return_temp(_left.value().rt_temp_member);
		} else if (_right.type() == compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
			_value.set_return_temp(_right.value().rt_temp_member);
		} else {
			//_counter.pop(_old_counter);
			_value.set_return_temp(_counter.next());
		}

		// Call operator
		compile_normal_operation(_toolset, _value).operate(_left, _operator, _right);

		// Update if used
		if (_value.type() == compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
			_old_counter = _value.value().rt_temp_member;

			_counter.update(_old_counter);
		}

		_left = _value;

		// Pop back
		_counter.pop(_old_counter);
	} while (i < _report->content.end);

	return _report->content.end;
}

const grammar::report * compiler::handle_condition_expression(const grammar::report * _report)
{
	// Handle left value
	auto _operator = handle_math_expression_and_term(_report + 1);

	// Operator is present
	if (_operator < _report->content.end) {
		auto _left = _value;

		// Handle right value
		handle_math_expression_and_term(_operator + 1);

		// Call operator
		///TODO: destination?
		compile_compare_operation(_toolset, _value).operate(_left, _operator->content.operator_code, _value);
	}

	return _report->content.end;
}

const grammar::report *  compiler::handle_number(const grammar::report * _report)
{
	using TYPE = report::TYPE;

	switch (static_cast<report::TYPE>(_report->type)) {
	case TYPE::INT_VALUE:
		_value.set_return(_report->content.int_value);

		break;
	case TYPE::BIG_INT_VALUE:
		_value.set_return(_report->content.big_int_value);

		break;
	case TYPE::DOUBLE_VALUE:
		_value.set_return(_report->content.double_value);

		break;
	default:
		BIA_IMPLEMENTATION_ERROR;
	}

	return _report;
}

const grammar::report * compiler::handle_raw_value(const grammar::report * _report)
{
	switch (_report[1].token_id) {
	case BV_NUMBER:
		handle_number(_report + 1);

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
		BIA_IMPLEMENTATION_ERROR;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_identifier(const grammar::report * _report, VARIABLE_TYPE _type)
{
	// 100% local
	if (_type == VARIABLE_TYPE::DEFINITELY_LOCAL) {
		_value.set_return_local(_scope_handler.declare(_report->content.member));

		return _report + 1;
	} // Unkown
	else if (!_scope_handler.no_open_scopes() && _type != VARIABLE_TYPE::DEFINITELY_GLOBAL) {
		auto _index = _scope_handler.variable_index(_report->content.member);

		// Local variable
		if (_index != scope_handler::not_found) {
			_value.set_return_local(_index);

			return _report + 1;
		}
	}

	// Global member
	_value.set_return(_context.address_of_member(_report->content.member));

	return _report + 1;
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
		BIA_IMPLEMENTATION_ERROR;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_member(const grammar::report * _report)
{
	const auto _end = _report->content.end;
	auto _destination = _value;

	if (_value.type() != compiler_value::VALUE_TYPE::MEMBER && _value.type() != compiler_value::VALUE_TYPE::LOCAL_MEMBER) {
		_destination.set_return();
	}

	++_report;

	// First member
	if (static_cast<report::TYPE>(_report->type) == report::TYPE::STRING) {
		_report = handle_string(_report);
	} else if (static_cast<report::TYPE>(_report->type) == report::TYPE::MEMBER) {
		member_function_signature<framework::member, void, framework::member*> _function = nullptr;

		// Ref of
		if (_report->custom_parameter == keyword_refof::string_id()) {
			_function = &framework::member::refer;
		} // Copy of
		else if (_report->custom_parameter == keyword_copyof::string_id()) {
			_function = &framework::member::copy;
		}

		_report = handle_identifier(_report);

		// Get refof/copyof
		if (_function) {
			_toolset.call_virtual(_function, _value.value().rt_member, machine::platform::toolset::to_temp_member(_counter.next()));
			_value.set_return_temp(_counter.current());
		}
	} else {
		BIA_IMPLEMENTATION_ERROR;
	}

	// Handle rest
	while (_report < _end) {
		// Handle parameter
		if (_report->rule_id == BGR_PARAMETER || _report->rule_id == BGR_PARAMETER_ITEM_ACCESS) {
			_report = handle_parameter(_report, _destination);
		} // Get member
		else if (static_cast<report::TYPE>(_report->type) == report::TYPE::MEMBER) {
			_value.expand_to_member(nullptr, [&](auto _member) {
				if (std::is_same<decltype(_member), std::nullptr_t>::value) {
					BIA_IMPLEMENTATION_ERROR;
				}

				_destination.expand_to_member(_member, [&](auto _dest) {
					if (std::is_same<decltype(_member), decltype(compiler_value::return_value::rt_member)>::value && std::is_same<decltype(_dest), std::nullptr_t>::value) {
						_value.set_return_temp(_counter.next());
						_toolset.call_virtual(&framework::member::object_member, _member, machine::platform::toolset::to_temp_member(_counter.current()), _report->content.member);
					} else {
						_value = _destination;

						_toolset.call_virtual(&framework::member::object_member, _member, _dest, _report->content.member);
					}
				});
			});

			++_report;
		}
	}

	return _end;
}

const grammar::report * compiler::handle_parameter(const grammar::report * _report, compiler_value _destination)
{
	using VT = compiler_value::VALUE_TYPE;

	auto _caller = _value;
	auto _passer = _toolset.create_varg_passer();
	uint32_t _count = 0;
	std::string _format;
	auto _mixed = false;

	if (static_cast<report::TYPE>(_report->type) != grammar::report::TYPE::EMPTY_CHILD) {
		// Save old counter
		auto _old = _counter.peek();

		for (auto i = _report + 1; i < _report->content.end; ++_count) {
			i = handle_value_insecure<false>(i);

			// Add type to format
			auto _type = handle_parameter_item(_passer);

			_format += _type;

			if (_type != 'M') {
				_mixed = true;
			}
		}

#if defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		// Reserve the last two integral registers
		_format.append("rr");
#endif

		_format.append(_passer.compensatory_pushes(), 'r');

		_counter.pop(_old);
	}

	// Call function
	_caller.expand_to_member(nullptr, [&](auto _member) {
		if (std::is_same<decltype(_member), std::nullptr_t>::value) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_destination.expand_to_member(nullptr, [&](auto _dest) {
			if (std::is_same<decltype(_dest), std::nullptr_t>::value) {
				_destination.set_return_temp(_counter.next());

				handle_parameter_execute(_member, machine::platform::toolset::to_temp_member(_counter.current()), _format, _mixed, _count, _passer);
			} else {
				handle_parameter_execute(_member, _dest, _format, _mixed, _count, _passer);
			}

			_value = _destination;
		});
	});

	return _report->content.end;
}

const grammar::report * compiler::handle_string(const grammar::report * _report)
{
	using S = stream::string_stream;

	auto _buffer = _report->content.string;

	switch (_report->custom_parameter) {
	case report::ASCII:
	case report::UTF8:
		_value.set_return(S::string<char>(_buffer), S::size(_buffer), S::length(_buffer));

		break;
	case report::UTF16:
	case report::UTF32:
	default:
		BIA_IMPLEMENTATION_ERROR;
	}

	return _report + 1;
}

const grammar::report * compiler::handle_variable_declaration(const grammar::report * _report)
{
	auto _local_variable = _report[1].content.keyword == grammar::keyword_var::string_id() && !_scope_handler.no_open_scopes();

	handle_identifier(_report + 2, _local_variable ? VARIABLE_TYPE::DEFINITELY_LOCAL : VARIABLE_TYPE::DEFINITELY_GLOBAL);

	auto _identifier = _value;

	// Handle value and prepare the result for a function call
	handle_value<false>(_report + 3, [&] {
		auto _expression = _value;

		// The result was already save to the identifier. See handle_value()
		if (_value == _identifier) {
			return;
		}

		_value = _identifier;

		// Local variable
		if (_local_variable) {
			handle_variable_declaration_helper(_expression, machine::platform::toolset::to_local_member(_value.value().rt_local_member));
		} else {
			handle_variable_declaration_helper(_expression, _value.value().rt_member);
		}

	});

	return _report->content.end;
}

const grammar::report * compiler::handle_if(const grammar::report * _report)
{
	std::vector<machine::platform::toolset::position_type> _end_jumps;

	for (auto i = _report + 1; i < _report->content.end;) {
		// Else statement
		if (i->rule_id == grammar::BGR_IF_HELPER_1) {
			// Set the results for compiling
			_value.set_return(true);

			// Move because the else statement is wrapped up
			++i;
		} // Handle condition
		else {
			_value.set_return();

			i = handle_value<true>(i, []() {});
		}

		// Compile statement
		if (_value.type() != compiler_value::VALUE_TYPE::TEST_VALUE_CONSTANT || _value.value().rt_test_result) {
			// Write jump
			auto _constant = _value.type() == compiler_value::VALUE_TYPE::TEST_VALUE_CONSTANT;
			auto _jump = _constant ? 0 : _toolset.jump(machine::platform::toolset::JUMP::JUMP_IF_FALSE);

			// Compile statement
			i = handle_root(i);

			// Jump to end if it has not been reached
			if (i < _report->content.end && !_constant) {
				_end_jumps.push_back(_toolset.jump(machine::platform::toolset::JUMP::JUMP));

				// Update test jump to next statement
				_toolset.jump(machine::platform::toolset::JUMP::JUMP_IF_FALSE, _toolset.output_stream().position(), _jump);
			} // End of ifs or condition is at compile time true
			else {
				// Update test jump to ent
				if (!_constant) {
					_toolset.jump(machine::platform::toolset::JUMP::JUMP_IF_FALSE, _toolset.output_stream().position(), _jump);
				}

				break;
			}
		} // Skip statements. These are conditions that are at compile time false
		else {
			i = handle_root_ignore(i);
		}
	}

	// Update end jump locations
	auto _end = _toolset.output_stream().position();

	for (auto & _jump : _end_jumps) {
		_toolset.jump(machine::platform::toolset::JUMP::JUMP, _end, _jump);
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_print(const grammar::report * _report)
{
	using VT = compiler_value::VALUE_TYPE;

	_value.set_return();

	// Handle value to print
	handle_value<false>(_report + 1, [this] {
		// Call print function
		switch (_value.type()) {
		case VT::INT:
		{
			// Can be int32
			if (_value.is_int32()) {
				_toolset.call_static(&machine::link::print_int32, static_cast<int32_t>(_value.value().rt_int));
			} else {
				_toolset.call_static(&machine::link::print_int64, _value.value().rt_int);
			}

			break;
		}
		case VT::BIG_INT:
			_toolset.call_static(&machine::link::print_big_int, _value.value().rt_big_int);

			break;
		case VT::DOUBLE:
			_toolset.call_static(&machine::link::print_double, _value.value().rt_double);

			break;
		case VT::STRING:
			_toolset.call_static(&machine::link::print_string, _value.value().rt_string.data);

			break;
		case VT::MEMBER:
			_toolset.call_virtual(&framework::member::print, _value.value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			_toolset.call_virtual(&framework::member::print, machine::platform::toolset::to_temp_member(_value.value().rt_temp_member));

			break;
		case VT::LOCAL_MEMBER:
			_toolset.call_virtual(&framework::member::print, machine::platform::toolset::to_local_member(_value.value().rt_local_member));

			break;
		case VT::TEST_VALUE_REGISTER:
			_toolset.call_static(&machine::link::print_bool, machine::platform::toolset::test_result_value());

			break;
		case VT::TEST_VALUE_CONSTANT:
		{
			if (_value.value().rt_test_result) {
				_toolset.call_static(&machine::link::print_true);
			} else {
				_toolset.call_static(&machine::link::print_false);
			}

			break;
		}
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	});

	return _report->content.end;
}

const grammar::report * compiler::handle_test_loop(const grammar::report * _report)
{
	using namespace machine::platform;

	const auto _end = _report->content.end;

	++_report;

	toolset::position_type _do_jump_update = -1;

	// Do loop
	if (_report->content.keyword == grammar::IS_DO) {
		_do_jump_update = _toolset.jump(toolset::JUMP::JUMP);

		++_report;
	}

	// Loop type
	auto _jump_type = _report++->content.keyword == grammar::IS_WHILE ? toolset::JUMP::JUMP_IF_FALSE : toolset::JUMP::JUMP_IF_TRUE;

	// Write loop condition
	auto _compile = true;
	toolset::position_type _condition_jump_update = -1;

	_loop_tracker.open_loop(_toolset.output_stream().position());
	_value.set_return();

	_report = handle_value<true>(_report, [&] {
		// Constant condition
		if (_value.type() == compiler_value::VALUE_TYPE::TEST_VALUE_CONSTANT) {
			// Don't compile this loop
			if (!_value.value().rt_test_result) {
				_compile = false;
			} // Change to unconditional jump
			else {
				_jump_type = toolset::JUMP::JUMP;
			}

			return;
		} // Not a test register
		else if (_value.type() != compiler_value::VALUE_TYPE::TEST_VALUE_REGISTER) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_condition_jump_update = _toolset.jump(_jump_type);
	});

	// Compile loop body
	if (_compile) {
		// Update first jump of do loops
		if (_do_jump_update != -1) {
			_toolset.jump(toolset::JUMP::JUMP, _toolset.output_stream().position(), _do_jump_update);
		}

		handle_root(_report);

		_toolset.jump(toolset::JUMP::JUMP, _loop_tracker.loop_start());

		// Update condition jump
		auto _destination = _toolset.output_stream().position();

		if (_condition_jump_update != -1) {
			_toolset.jump(_jump_type, _destination, _condition_jump_update);
		}

		// Update all end jump that occurred within the loop
		for (auto _jump_update : _loop_tracker.end_jump_updates()) {
			_toolset.jump(toolset::JUMP::JUMP, _destination, _jump_update);
		}

		_loop_tracker.close_loop();
	} // Discard do jump instruction since loop is not compiled
	else if (_do_jump_update != -1) {
		_toolset.output_stream().set_position(_do_jump_update);
	}

	return _end;
}

const grammar::report * compiler::handle_loop_control(const grammar::report * _report)
{
	if (_report->content.keyword == grammar::IS_DELETE) {
		// Reset temp member
		_finish_tasks.emplace_back(std::make_pair(_toolset.output_stream().position(), [this]() {
			_toolset.call_member(&machine::machine_context::recreate_range_on_stack, &_context, machine::platform::toolset::to_temp_member(1), uint32_t(_counter.max()));
		}));
		_toolset.call_member(&machine::machine_context::recreate_range_on_stack, &_context, machine::platform::toolset::to_temp_member(1), uint32_t(0));
	} else if (_loop_tracker.open_loops()) {
		if (_report->content.keyword == grammar::IS_BREAK) {
			_loop_tracker.add_end_update(_toolset.jump(machine::platform::toolset::JUMP::JUMP, 0));
		} else {
			_toolset.jump(machine::platform::toolset::JUMP::JUMP, _loop_tracker.loop_start());
		}
	}

	return _report + 1;
}

const grammar::report * compiler::handle_import(const grammar::report * _report)
{
	// Call import
	_toolset.call_member(&machine::machine_context::import_module, &_context, _report[1].content.member);

	return _report->content.end;
}

}
}
