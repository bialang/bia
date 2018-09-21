#pragma once

#include <cstdint>
#include <memory>

#include "config.hpp"
#include "output_stream.hpp"


namespace bia
{
namespace stream
{

class buffer_output_stream : public output_stream
{
public:
	BIA_EXPORT explicit buffer_output_stream();
	BIA_EXPORT virtual void set_position(cursor_type _position) override;
	BIA_EXPORT virtual void set_beginning(cursor_type _position) override;
	BIA_EXPORT virtual void append_stream(output_stream & _stream) override;
	BIA_EXPORT virtual void write(const void * _buffer, size_t _size) override;
	BIA_EXPORT virtual cursor_type position() const override;
	BIA_EXPORT cursor_type size() const;
	BIA_EXPORT const int8_t * buffer() const;

protected:
	BIA_EXPORT virtual void prepare(size_t _size) override;

private:
	std::unique_ptr<int8_t[]> _buffer;
	cursor_type _limit;
	cursor_type _size;
	cursor_type _beginning;
};
	
}
}