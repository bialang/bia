#pragma once

#include "member.hpp"
#include "exception.hpp"
#include "stack.hpp"
#include "member_array_view.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class parameter_setter
{
public:
	typedef framework::member::parameter_count_t parameter_count_t;

	parameter_setter() noexcept
	{
		_count = 0;
	}
	void add_parameter(const char * _name)
	{
		++_count;
	}
	void setup(stack & _stack, member_array_view & _temps, const char * _format, parameter_count_t _count)
	{
		if (this->_count != _count) {
			throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
		}

		// Formatted input
		if (_format) {
			for (parameter_count_t i = 0; i < _count; ++i) {
				_stack.format_cast(i - _count, _format[i], _temps[-i - 1]);
			}
		} else {
			for (parameter_count_t i = 0; i < _count; ++i) {
				_stack.cast<framework::member*>(i - _count)->refer(_temps[-i - 1]);
			}
		}
	}
private:
	parameter_count_t _count;
};

}
}
}