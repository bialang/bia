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

	op_code::write_setup(_output, 0);

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
		op_code::write_setup(*_output, _temp_count);
		_output->set_position(_current_pos);
	} // Skip temp member creation
	else {
		_output->set_beginning(_setup_end_pos);
	}

	_output->write_all(OC_RETURN);
}

void virtual_translator::instantiate_int(const index & _destination, int64_t _value)
{
	if (!dynamic_cast<const member_index*>(&_destination)) {
		BIA_NOT_IMPLEMENTED;
	}

}

void virtual_translator::test(const index & _member)
{
	BIA_NOT_IMPLEMENTED;
}

void virtual_translator::execute(const index & _member)
{
	op_code::write_m_type(*_output, OC_EXECUTE_VOID, _member);
}

void virtual_translator::pass_parameter(const index & _member)
{
	op_code::write_m_type(*_output, OC_PUSH, _member);
}

virtual_translator::position_t virtual_translator::jump(JUMP _type, position_t _destination, position_t _overwrite_pos)
{
	BIA_NOT_IMPLEMENTED;
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