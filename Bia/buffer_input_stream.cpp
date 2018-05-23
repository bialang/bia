#include "buffer_input_stream.hpp"
#include "exception.hpp"

#include <cstdint>


namespace bia
{
namespace stream
{

buffer_input_stream::buffer_input_stream(const std::shared_ptr<const void> & _buffer, size_t _length) : _buffer(_buffer)
{
	if (!_length && _buffer.get()) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	this->_length = _length;
	_position = 0;
}

buffer_input_stream::buffer_input_stream(std::shared_ptr<const void> && _buffer, size_t _length) : _buffer(std::move(_buffer))
{
	if (!_length && _buffer.get()) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	this->_length = _length;
	_position = 0;
}

void buffer_input_stream::reset(cursor_type _mark)
{
	// Check reset position
	if (_mark < 0 || _mark > _length) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_position = _mark;
}

void buffer_input_stream::skip(cursor_type _length)
{
	// Check result position
	auto _result = _position + _length;

	if (_result < 0 || _result > _length) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_position = _result;
}

void buffer_input_stream::skip(buffer_type::first_type _ptr)
{
	// Check result position
	auto _result = _ptr - _buffer.get();

	if (_result < 0 || _result > _length) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_position = _result;
}

buffer_input_stream::cursor_type buffer_input_stream::mark() const
{
	return _position;
}

buffer_input_stream::cursor_type buffer_input_stream::available() const
{
	return _length - _position;
}

buffer_input_stream::buffer_type buffer_input_stream::get_buffer()
{
	return { static_cast<const int8_t*>(_buffer.get()) + _position, static_cast<const int8_t*>(_buffer.get()) + _length };
}

}
}