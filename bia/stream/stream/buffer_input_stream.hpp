#pragma once

#include "input_stream.hpp"

namespace bia {
namespace stream {

class buffer_input_stream : public input_stream
{
public:
	buffer_input_stream(const std::int8_t* begin, const std::int8_t* end) noexcept;
	virtual void reset_to_mark(mark_type mark) override;
	virtual void drop_mark(mark_type mark) override;
	virtual void skip(std::size_t length) override;
	virtual bool supports_bufferless() const noexcept override;
	virtual std::size_t left_size() const override;
	virtual mark_type mark() override;
	virtual std::size_t read(void* buffer, std::size_t size) override;
	virtual std::pair<const std::int8_t*, const std::int8_t*> bufferless_read() override;

private:
	const std::int8_t* begin;
	const std::int8_t* end;
	const std::int8_t* cursor;
};

} // namespace stream
} // namespace bia