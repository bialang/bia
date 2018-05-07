#include "buffer_output_stream.hpp"

#include <cstring>


namespace bia
{
namespace stream
{

buffer_output_stream::buffer_output_stream()
{
	_limit = _size = 0;
}

void buffer_output_stream::set_position(cursor_type _position)
{
	if (_position < 0 || _position > _limit) {
		throw;
	}

	_size = _position;
}

buffer_output_stream::cursor_type buffer_output_stream::get_position() const
{
	return _size;
}

void buffer_output_stream::prepare(size_t _size)
{
	if (_limit < _size + this->_size) {
		_limit = (_limit + _size) * 2;

		auto _new = new int8_t[_limit];

		memcpy(_new, _buffer.get(), this->_size);

		_buffer.reset(_new);
	}
}

void buffer_output_stream::write(int8_t _value)
{
	_buffer[_size++] = _value;
}

void buffer_output_stream::write(int16_t _value)
{
	memcpy(_buffer.get() + _size, &_value, 2);

	_size += 2;
}

void buffer_output_stream::write(int32_t _value)
{
	memcpy(_buffer.get() + _size, &_value, 4);

	_size += 4;
}

void buffer_output_stream::write(int64_t _value)
{
	memcpy(_buffer.get() + _size, &_value, 8);

	_size += 8;
}

}
}