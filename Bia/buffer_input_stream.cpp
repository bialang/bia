#include "buffer_input_stream.hpp"

#include <cstdint>


namespace bia
{
namespace stream
{

buffer_input_stream::buffer_input_stream(std::shared_ptr<const void> _buffer, size_t _length) : _buffer(std::move(_buffer))
{
	this->_length = _length;
	_position = 0;
}

void buffer_input_stream::reset(cursor_type _mark)
{
	// Check reset position
	if (_mark < 0 || _mark > _length) {
		throw;
	}

	_position = _mark;
}

void buffer_input_stream::skip(cursor_type _length)
{
	// Check result position
	auto _result = _position + _length;

	if (_result < 0 || _result > _length) {
		throw;
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

std::pair<const int8_t*, buffer_input_stream::cursor_type> buffer_input_stream::get_buffer()
{
	return { static_cast<const int8_t*>(_buffer.get()), available() };
}

}
}