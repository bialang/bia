#pragma once

#include <memory>

#include "input_stream.hpp"


namespace bia
{
namespace stream
{

/**
 * A buffered input which streams from a constant memory address with a fixed size.
*/
class buffer_input_stream : public input_stream
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 18-Apr-18
	 *
	 * @param _buffer The input buffer.
	 * @param _length The length of the buffer.
	*/
	buffer_input_stream(std::shared_ptr<const void> _buffer, size_t _length);

	virtual void reset(cursor_type _mark) override;
	virtual void skip(cursor_type _length) override;
	virtual cursor_type mark() const override;
	virtual cursor_type available() const override;
	virtual std::pair<const int8_t*, cursor_type> get_buffer() override;

private:
	/** The buffer. */
	std::shared_ptr<const void> _buffer;
	/** The length of the buffer. */
	size_t _length;
	/** The current position. */
	cursor_type _position;
};

}
}