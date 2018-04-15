#pragma once

#include <cstdint>

#include "config.hpp"
#include "exception.hpp"


namespace bia
{
namespace compiler
{

class temp_counter
{
public:
	typedef int32_t counter_type;

	temp_counter() noexcept
	{
		_counter = _max = 0;
	}
	void pop(counter_type _old_counter)
	{
		if (_counter < _old_counter)
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid old counter.");

		_counter = _old_counter;
	}
	counter_type next()
	{
		if (_counter + 1 > BIA_MAX_TEMP_ADDRESSES)
			throw exception::LimitationException("Limitation exceeded.");

		return ++_counter;
	}
	counter_type current()
	{
		// Update max if counter is used
		if (_max < _counter) {
			_max = _counter;
		}

		return _counter;
	}
	counter_type peek()
	{
		return _counter;
	}
	counter_type max() const
	{
		return _max;
	}

private:
	counter_type _counter;
	counter_type _max;
};

}
}