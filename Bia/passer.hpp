#pragma once

#include <cstdint>

#include "output_stream.hpp"
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
		auto _padding = align_stack(_element_count * element_size) - _element_count * element_size;

		// Write padding
		if (_padding) {

		}

		_push_tracker.push(std::make_pair(_padding / element_size, _caller_cleans));
	}
	void pop()
	{

	}
	pass_count_type stack_offset() const noexcept
	{
		return _stack_offset;
	}
	stream::output_stream & output() noexcept
	{
		return _output;
	}

private:
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
