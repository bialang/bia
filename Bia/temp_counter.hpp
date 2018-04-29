#pragma once

#include <cstdint>
#include <limits>

#include "exception.hpp"
#include "toolset.hpp"


namespace bia
{
namespace compiler
{

/**
 * @brief A counter for the compiler.
 *
 * A counter used to track the amount of used temporary variables.
 *
 * @see @ref compiler
*/
class temp_counter
{
public:
	typedef machine::platform::toolset::temp_index_type counter_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	*/
	temp_counter() noexcept
	{
		_counter = _max = 0;
	}
	/**
	 * Pops counts until the counter equals the old counter.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @param _old_counter The old counter.
	 *
	 * @throws exception::argument_error If the old counter is invalid.
	*/
	void pop(counter_type _old_counter)
	{
		// Check counter
		if (_counter < _old_counter) {
			throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
		}

		_counter = _old_counter;
	}
	/**
	 * Increments the current counter by one.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @throws exception::limitation_error If the maximum supported counter value has been reached.
	 *
	 * @return The new current counter.
	*/
	counter_type next()
	{
		if (_counter == std::numeric_limits<counter_type>::max()) {
			throw exception::limitation_error(BIA_EM_LIMITATION_EXCEEDED);
		}

		return ++_counter;
	}
	/**
	 * Returns the current counter and possibly updates the max counter.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @return The current counter.
	*/
	counter_type current() noexcept
	{
		// Update max if counter is used
		if (_max < _counter) {
			_max = _counter;
		}

		return _counter;
	}
	/**
	 * Returns the current counter without updating the max counter.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @return The current counter.
	*/
	counter_type peek() const noexcept
	{
		return _counter;
	}
	/**
	 * Returns the max counter.
	 *
	 * @since 3.64.127.716
	 * @date 22-Apr-18
	 *
	 * @return The max counter.
	*/
	counter_type max() const noexcept
	{
		return _max;
	}

private:
	/** The current counter. */
	counter_type _counter;
	/** The max counted value. */
	counter_type _max;
};

}
}