#pragma once

#include <cstdint>

#include "output_stream.hpp"
#include "architecture.hpp"
#include "architecture_utils.hpp"

#include <cstdio>
namespace bia
{
namespace machine
{
namespace platform
{

struct reserved_parameter
{
};

class static_passer;
class member_passer;
class varg_member_passer;

class passer
{
public:
	/** The passer count type. */
	typedef int32_t pass_count_type;

	passer(stream::output_stream * _output) noexcept : _output(_output)
	{
		_stack_offset = 0;
		_credit_entry = 0;
	}
	void prepare_pushing(pass_count_type _already_pushed, pass_count_type _to_be_pushed, bool _caller_pops_parameters, bool _caller_pops_padding)
	{
		// +1 because of call return address
		auto _padding = align_stack((_stack_offset + _to_be_pushed + 1) * element_size) - (_stack_offset + _to_be_pushed) * element_size - element_size;

		// Write padding
		if (_padding) {
			instruction8<OP_CODE::SUB, stack_pointer>(*_output, _padding);
			
			// Add padding
			if (_caller_pops_padding) {
				_stack_offset += _padding / element_size;
				_credit_entry += _padding / element_size;
			}
		}

		// Caller pops -> they can be used later -> credit entry
		if (_caller_pops_parameters) {
			_credit_entry += _already_pushed + _to_be_pushed;
		} // Callee pops -> can't be used
		else {
			_stack_offset -= _already_pushed + _to_be_pushed;
		}
	}
	void pop()
	{
		if (_credit_entry) {
			instruction8<OP_CODE::ADD, stack_pointer>(*_output, _credit_entry * element_size);
			
			_stack_offset -= _credit_entry;
			_credit_entry = 0;
		}
	}
	void set_output(stream::output_stream * _output)
	{
		this->_output = _output;
	}

private:
	friend static_passer;
	friend member_passer;
	friend varg_member_passer;

	typedef std::pair<pass_count_type, bool> entry_type;

	constexpr static pass_count_type _max_credit_entry = 0x7f / element_size;
	/** The offset (as elements) of the stack since the creation of this object. */
	pass_count_type _stack_offset;

	pass_count_type _credit_entry;
	/** The destination of the machine code. */
	stream::output_stream * _output;
};

}
}
}
