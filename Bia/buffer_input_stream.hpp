#pragma once

#include <memory>

#include "input_stream.hpp"


namespace bia
{
namespace stream
{

/**
 * @brief A buffer input stream.
 *
 * A input stream which receives the input from a fixed sized buffer.
 *
 * @see @ref buffered_input_stream
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
	 *
	 * @throws exception::argument_error If either the buffer or the length is invalid.
	*/
	buffer_input_stream(const std::shared_ptr<const int8_t> & _buffer, size_t _length);
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 18-Apr-18
	 *
	 * @param _buffer The input buffer.
	 * @param _length The length of the buffer.
	 *
	 * @throws exception::argument_error If either the buffer or the length is invalid.
	*/
	buffer_input_stream(std::shared_ptr<const int8_t> && _buffer, size_t _length);

	virtual void reset(cursor_type _mark) override;
	virtual void skip(cursor_type _length) override;
	virtual void skip(buffer_type::first_type _ptr) override;
	virtual void read(void * _destination, size_t _size) override;
	virtual cursor_type mark() const override;
	virtual cursor_type available() const override;
	virtual buffer_type buffer() override;

private:
	/** The buffer. */
	std::shared_ptr<const int8_t> _buffer;
	/** The length of the buffer. */
	size_t _length;
	/** The current position. */
	cursor_type _position;
};

}
}