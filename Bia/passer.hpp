#pragma once

#include <cstdint>

#include "output_stream.hpp"
#include "architecture.hpp"
#include "architecture_utils.hpp"


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

	passer(stream::output_stream & _output) noexcept : _output(_output)
	{
		_stack_offset = 0;
		_credit_entry = 0;
	}
	void prepare_pushing(pass_count_type _element_count, bool _caller_cleans)
	{
		auto _padding = align_stack(_stack_offset * element_size) - _stack_offset * element_size;

		// Write padding
		if (_padding) {
			instruction8<OP_CODE::SUB, stack_pointer>(_output, _padding);
			
			if (_caller_cleans) {
				_credit_entry += _padding / element_size;
			}
		}

		if (_caller_cleans) {
			_credit_entry += _element_count;
		}
	}
	void pop()
	{
		if (_credit_entry) {
			instruction8<OP_CODE::ADD, stack_pointer>(_output, _credit_entry * element_size);
		}
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
	stream::output_stream & _output;
};

}
}
}
