#include "virtual_machine_code.hpp"
#include "op_code.hpp"
#include "create_member.hpp"

#include <cstring>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

virtual_machine_code::virtual_machine_code(memory::universal_allocation _code, virtual_machine_schein && _schein, bool _take_ownership) : _schein(std::move(_schein))
{
	// Copy buffer
	if (!_take_ownership) {
		auto _tmp = this->_schein.allocator()->allocate(_code.second);

		std::memcpy(_tmp.first, _code.first, _code.second);

		_code = _tmp;
	}

	this->_code = memory::cast_allocation<uint8_t>(_code);
}

virtual_machine_code::virtual_machine_code(virtual_machine_code && _move) : _schein(std::move(_move._schein))
{
	_code = std::move(_move._code);

	_move.clear();
}

virtual_machine_code::~virtual_machine_code()
{
	clear();
}

void virtual_machine_code::execute()
{
	auto & _globals = _schein.globals();
	auto & _stack = _schein.stack();
	const auto _end = _code.first + _code.second;
	const uint8_t * _cursor = _code.first;
	framework::member::test_result_t _test_register = 0;

	// Helper functions
	const auto _read_int_param = [&](op_code_t _operation) { return _operation & op_code::tiny_bit ? read<int8_t>(_cursor) : read<int32_t>(_cursor); };
	const auto _expand_i_type = [&](op_code_t _operation, auto _lambda) {
		_operation >>= op_code::parameter_offset;

		switch (_operation >> op_code::immediate_offset & op_code::immediate_mask) {
		case IOCO_INT32:
			_lambda(read<int32_t>(_cursor));

			break;
		case IOCO_INT8:
			_lambda(read<int8_t>(_cursor));

			break;
		case IOCO_INT64:
			_lambda(read<int64_t>(_cursor));

			break;
		case IOCO_FLOAT:
			_lambda(read<double>(_cursor));

			break;
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	};
	const auto _expand_m_type = [&](op_code_t _operation) {
		_operation >>= op_code::parameter_offset;

		auto _index = _operation & op_code::tiny_bit ? read<tiny_member_index_t>(_cursor) : read<member_index_t>(_cursor);

		switch (_operation >> op_code::member_offset & op_code::member_mask) {
		case MOCO_MEMBER:
			return _globals[_index];
		case MOCO_LOCAL:
		case MOCO_TEMP:
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	};
	const auto _expand_mi_type = [&](op_code_t _operation, auto _lambda) {
		auto _member = _expand_m_type(_operation);

		_expand_i_type(_operation << op_code::member_bit_count, [&](auto _value) { _lambda(_member, _value); });
	};
	const auto _expand_mm_type = [&](op_code_t _operation, auto _lambda) {
		auto _left = _expand_m_type(_operation);

		_lambda(_left, _expand_m_type(_operation << op_code::member_bit_count));
	};

	while (_cursor < _end) {
		auto _operation = read<op_code_t>(_cursor);

		switch (_operation & op_code::op_code_mask) {
		/** P-Type instructions */
		case OC_RETURN:
			goto gt_return;
		/** I-Type instructions */
		case OC_SETUP:
		{
			auto _count = read<member_index_t>(_cursor);

			break;
		}
		case OC_JUMP:
			_cursor += _read_int_param(_operation);

			break;
		case OC_JUMP_TRUE:
		{
			if (_test_register) {
				_cursor += _read_int_param(_operation);
			}

			break;
		}
		case OC_JUMP_FALSE:
		{
			if (!_test_register) {
				_cursor += _read_int_param(_operation);
			}

			break;
		}
		case OC_PUSH_IMMEDIATE:
			_expand_i_type(_operation, [&](auto _value) { _stack.push(_value); });

			break;
		/** M-Type instructions */
		case OC_PUSH:
			_stack.push(_expand_m_type(_operation));

			break;
		case OC_TEST:
			_test_register = _expand_m_type(_operation)->test();

			break;
		case OC_UNDEFINE:
			_expand_m_type(_operation)->undefine();

			break;
		case OC_EXECUTE_VOID:
			_expand_m_type(_operation)->execute(nullptr);

			break;
		/** MI-Type instructions */
		case OC_INSTANTIATE:
			_expand_mi_type(_operation, [&](framework::member * _member, auto _value) { framework::create_member(_member, _value); });

			break;
		/** MM-Type instructions */
		case OC_EXECUTE:
			_expand_mm_type(_operation, [&](framework::member * _src, framework::member * _dest) { _src->execute(_dest); });

			break;
		case OC_CLONE:
			_expand_mm_type(_operation, [&](framework::member * _src, framework::member * _dest) { _src->clone(_dest); });

			break;
		case OC_REFER:
			_expand_mm_type(_operation, [&](framework::member * _src, framework::member * _dest) { _src->refer(_dest); });

			break;
		case OC_COPY:
			_expand_mm_type(_operation, [&](framework::member * _src, framework::member * _dest) { _src->copy(_dest); });

			break;
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	}

gt_return:;
}

void virtual_machine_code::clear()
{
	if (_code) {
		_schein.allocator()->deallocate(memory::cast_allocation<void>(_code));
		_code.clear();
	}
}

bool virtual_machine_code::is_executable() const noexcept
{
	return _code;
}

}
}
}