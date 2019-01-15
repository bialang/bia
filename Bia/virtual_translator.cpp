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

	_output.write_all(OC_CREATE_TEMP_MEMBERS, member_index_t(0));

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
		_output->write_all(OC_CREATE_TEMP_MEMBERS, _temp_count);
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

	// Fits into an int32
	if (_value <= std::numeric_limits<int32_t>::max() && _value >= std::numeric_limits<int32_t>::min()) {
		switch (_value) {
		case 0:
			_output->write_all(OC_INSTANTIATE_0, _destination.value);

			break;
		default:
			BIA_NOT_IMPLEMENTED;
		}
	} else {
		BIA_NOT_IMPLEMENTED;
	}
}

void virtual_translator::test(const index & _member)
{
	auto _write = [&](OP_CODE _op_code) {
		if (_member.value <= std::numeric_limits<tiny_member_index_t>::max()) {
			_output->write_all(static_cast<OP_CODE>(_op_code | OCF_TINY), static_cast<tiny_member_index_t>(_member.value));
		} else {
			_output->write_all(_op_code, _member.value);
		}
	};

	// Pass member
	if (dynamic_cast<const member_index*>(&_member)) {
		_write(OC_TEST_M);
	} else if (dynamic_cast<const temp_index*>(&_member)) {
		_write(OC_TEST_T);
	} else if (dynamic_cast<const local_index*>(&_member)) {
		_write(OC_TEST_L);
	} else {
		BIA_IMPLEMENTATION_ERROR;
	}
}

void virtual_translator::pass_parameter(const index & _index)
{
	auto _write = [&](OP_CODE _op_code) {
		if (_index.value <= std::numeric_limits<tiny_member_index_t>::max()) {
			_output->write_all(static_cast<OP_CODE>(_op_code | OCF_TINY), static_cast<tiny_member_index_t>(_index.value));
		} else {
			_output->write_all(_op_code, _index.value);
		}
	};

	// Pass member
	if (dynamic_cast<const member_index*>(&_index)) {
		_write(OC_PARAM_M);
	} else if (dynamic_cast<const temp_index*>(&_index)) {
		_write(OC_PARAM_T);
	} else if (dynamic_cast<const local_index*>(&_index)) {
		_write(OC_PARAM_L);
	} else {
		BIA_IMPLEMENTATION_ERROR;
	}
}

virtual_translator::position_t virtual_translator::jump(JUMP _type, position_t _destination, position_t _overwrite_pos)
{
	BIA_NOT_IMPLEMENTED;
}

stream::output_stream & virtual_translator::output_stream() noexcept
{
	return *_output;
}

virtual_translator::member_index virtual_translator::to_member(grammar::report::member_t _name)
{
	auto _result = _member_index.find(_name);

	if (_result == _member_index.end()) {
		auto _index = _member_index.size();

		_member_index.insert({ _name, _index });

		return _index;
	}

	return _result->second;
}

virtual_translator::temp_index virtual_translator::to_temp(member_index_t _index) noexcept
{
	return _index;
}

virtual_translator::local_index virtual_translator::to_local(member_index_t _index) noexcept
{
	return _index;
}

}
}
}