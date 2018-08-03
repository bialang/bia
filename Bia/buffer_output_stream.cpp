#include "buffer_output_stream.hpp"
#include "exception.hpp"

#include <cstring>


namespace bia
{
namespace stream
{

buffer_output_stream::buffer_output_stream()
{
	_limit = 0;
	_size = 0;
	_beginning = 0;
}

void buffer_output_stream::set_position(cursor_type _position)
{
	if (_position < _beginning || _position > _limit) {
		throw;
	}

	_size = _position;
}

void buffer_output_stream::set_beginning(cursor_type _position)
{
	if (_position < 0 || _position > _size) {
		throw;
	}

	_beginning = _position;
}

void buffer_output_stream::append_stream(output_stream & _stream)
{
	if (auto _buffer_stream = dynamic_cast<buffer_output_stream*>(&_stream)) {
		prepare(_buffer_stream->_size);
		std::memcpy(_buffer.get() + _size, _buffer_stream->_buffer.get(), _buffer_stream->_size);

		_size += _buffer_stream->_size;
	} else {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

void buffer_output_stream::write(const void * _buffer, size_t _size)
{
	prepare(_size);

	std::memcpy(this->_buffer.get() + this->_size, _buffer, _size);
	
	this->_size += _size;
}

buffer_output_stream::cursor_type buffer_output_stream::position() const
{
	return _size;
}

buffer_output_stream::cursor_type buffer_output_stream::size() const
{
	return _size - _beginning;
}

const int8_t * buffer_output_stream::buffer() const
{
	return _buffer.get() + _beginning;
}

void buffer_output_stream::prepare(size_t _size)
{
	if (_limit < _size + this->_size) {
		_limit = (_limit + _size) * 2;

		auto _new = new int8_t[_limit];

		std::memcpy(_new, _buffer.get(), this->_size);

		_buffer.reset(_new);
	}
}

}
}