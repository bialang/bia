#pragma once

#include <cstdint>
#include <memory>

#include "output_stream.hpp"


namespace bia
{
namespace stream
{

class buffer_output_stream : public output_stream
{
public:
	explicit buffer_output_stream();
	virtual void set_position(cursor_type _position) override;
	virtual void set_beginning(cursor_type _position) override;
	virtual void append_stream(output_stream & _stream) override;
	virtual void write(const void * _buffer, size_t _size) override;
	virtual cursor_type position() const override;
	cursor_type size() const;
	const int8_t * buffer() const;

protected:
	virtual void prepare(size_t _size) override;

private:
	std::unique_ptr<int8_t[]> _buffer;
	cursor_type _limit;
	cursor_type _size;
	cursor_type _beginning;
};
	
}
}