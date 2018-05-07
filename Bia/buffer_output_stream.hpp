#pragma once

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
	virtual cursor_type get_position() const override;

protected:
	virtual void prepare(size_t _size) override;
	virtual void write(int8_t _value) override;
	virtual void write(int16_t _value) override;
	virtual void write(int32_t _value) override;
	virtual void write(int64_t _value) override;

private:
	std::unique_ptr<int8_t[]> _buffer;
	cursor_type _limit;
	cursor_type _size;
};
	
}
}