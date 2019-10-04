#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>

namespace bia {
namespace stream {

class input_stream
{
public:
	typedef std::int64_t mark_type;

	virtual ~input_stream()														= default;
	virtual void reset_to_mark(mark_type mark)									= 0;
	virtual void drop_mark(mark_type mark)										= 0;
	virtual void skip(std::size_t length)										= 0;
	virtual bool supports_bufferless() const noexcept							= 0;
	virtual std::size_t left_size() const										= 0;
	virtual mark_type mark()													= 0;
	virtual std::size_t read(void* buffer, std::size_t size)					= 0;
	virtual std::pair<const std::int8_t*, const std::int8_t*> bufferless_read() = 0;
};

} // namespace stream
} // namespace bia