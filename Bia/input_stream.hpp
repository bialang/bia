#pragma once

#include <utility>
#include <cstdint>

#include "config.hpp"


namespace bia
{
namespace stream
{

/**
 * @brief An input stream interface.
 *
 * An interface for input streams.
 *
 * @see @ref file_input_stream, @ref buffer_input_stream
*/
class input_stream
{
public:
	/** The cursor type. */
	typedef long long cursor_type;
	/** The buffer type. */
	typedef std::pair<const int8_t*, const int8_t*> buffer_type;

	constexpr static cursor_type min_buffer_size = BIA_MIN_INPUT_BUFFER_SIZE;

	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~input_stream() = default;
	/**
	 * Resets the stream to the old mark.
	 *
	 * @remarks Moving forward can lead to undefined behavior. Look at the implementation for more details.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _mark The old mark.
	 *
	 * @throws exception::argument_error The mark is invalid.
	*/
	virtual void reset(cursor_type _mark) = 0;
	virtual void skip(cursor_type _length) = 0;
	virtual void skip(buffer_type::first_type _ptr) = 0;
	virtual cursor_type mark() const = 0;
	virtual cursor_type available() const = 0;
	virtual buffer_type buffer() = 0;
};

}
}