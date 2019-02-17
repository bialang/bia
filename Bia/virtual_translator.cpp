#include "virtual_translator.hpp"
#include "exception.hpp"

#include <limits>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

virtual_translator::virtual_translator(stream::output_stream & _output)
{
	this->_output = &_output;

	_temp_member_pos = _output.position();

	op_code::write_int_type<member_index_t>(_output, OC_SETUP, 0);

	_setup_end_pos = _output.position();
}

void virtual_translator::open_scope()
{
}

void virtual_translator::finalize(member_index_t _temp_count)
{
	// Update first instruction
	if (_temp_count) {
		// Update
		auto _current_pos = _output->position();

		_output->set_position(_temp_member_pos);
		op_code::write_int_type<member_index_t>(*_output, OC_SETUP, _temp_count);
		_output->set_position(_current_pos);
	} // Skip temp member creation
	else {
		_output->set_beginning(_setup_end_pos);
	}

	_output->write_all(OC_RETURN);
}

void virtual_translator::instantiate_int(const index & _member, int64_t _value)
{
	// 8 bit
	if (_value >= std::numeric_limits<int8_t>::min() && _value <= std::numeric_limits<int8_t>::max()) {
		op_code::write_mi_type(*_output, OC_INSTANTIATE, _member, static_cast<int8_t>(_value));
	} else if (_value >= std::numeric_limits<int32_t>::min() && _value <= std::numeric_limits<int32_t>::max()) {
		op_code::write_mi_type(*_output, OC_INSTANTIATE, _member, static_cast<int32_t>(_value));
	} else {
		op_code::write_mi_type(*_output, OC_INSTANTIATE, _member, _value);
	}
}

void virtual_translator::test(const index & _member)
{
	op_code::write_m_type(*_output, OC_TEST, _member);
}

void virtual_translator::execute(const index & _member)
{
	op_code::write_m_type(*_output, OC_EXECUTE_VOID, _member);
}

void virtual_translator::execute_count(const index & _member, framework::member::parameter_count_t _count)
{
	op_code::write_m_type(*_output, OC_EXECUTE_COUNT_VOID, _member);

	_output->write_all(_count);
}

void virtual_translator::execute_format(const index & _member, const char * _format, framework::member::parameter_count_t _count)
{
	op_code::write_m_type(*_output, OC_EXECUTE_FORMAT_VOID, _member);

	_output->write_all(_count);
	_output->write(_format, _count);
}

void virtual_translator::pass_parameter(const index & _member)
{
	op_code::write_m_type(*_output, OC_PUSH, _member);
}

virtual_translator::position_t virtual_translator::jump(JUMP _type, position_t _destination, position_t _overwrite_pos)
{
	int32_t _pos = 0;
	OP_CODE _operation;

	switch (_type) {
	case JUMP::JUMP:
		_operation = OC_JUMP;

		break;
	case JUMP::JUMP_IF_TRUE:
		_operation = OC_JUMP_TRUE;

		break;
	case JUMP::JUMP_IF_FALSE:
		_operation = OC_JUMP_FALSE;

		break;
	default:
		BIA_IMPLEMENTATION_ERROR;
	}

	op_code::write_int_type(*_output, _operation, _pos);
}

stream::output_stream & virtual_translator::output_stream() noexcept
{
	return *_output;
}

const virtual_member_map & virtual_translator::virtual_member_map() noexcept
{
	return _member_map;
}

member_index virtual_translator::to_member(grammar::report::member_t _name)
{
	return _member_map.get_or_insert(_name);
}

temp_index virtual_translator::to_temp(member_index_t _index) noexcept
{
	return _index;
}

local_index virtual_translator::to_local(member_index_t _index) noexcept
{
	return _index;
}

}
}
}