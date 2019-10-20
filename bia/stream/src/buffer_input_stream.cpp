#include <stream/buffer_input_stream.hpp>
#include <cstring>
#include <algorithm>

namespace bia {
namespace stream {

buffer_input_stream::buffer_input_stream(const std::int8_t* begin, const std::int8_t* end) noexcept
{
	this->begin = begin;
	this->end   = end;
	cursor		= begin;
}

void buffer_input_stream::reset_to_mark(mark_type mark)
{
	auto new_mark = reinterpret_cast<const std::int8_t*>(mark);

	if (new_mark < begin || new_mark > end) {
		throw;
	}

	cursor = new_mark;
}

void buffer_input_stream::drop_mark(mark_type mark)
{
	auto new_mark = reinterpret_cast<const std::int8_t*>(mark);

	if (new_mark < begin || new_mark > end) {
		throw;
	}
}

void buffer_input_stream::skip(std::size_t length)
{
	auto new_mark = cursor + length;

	if (new_mark < begin || new_mark > end) {
		throw;
	}

	cursor = new_mark;
}

bool buffer_input_stream::supports_bufferless() const noexcept
{
	return true;
}

std::size_t buffer_input_stream::left_size() const
{
	return static_cast<std::size_t>(end - cursor);
}

buffer_input_stream::mark_type buffer_input_stream::mark()
{
	return reinterpret_cast<mark_type>(cursor);
}

std::size_t buffer_input_stream::read(void* buffer, std::size_t size)
{
	auto s = std::max(size, left_size());

	std::memcpy(buffer, cursor, s);

	return s;
}

std::pair<const std::int8_t*, const std::int8_t*> buffer_input_stream::bufferless_read()
{
	return { cursor, end };
}

} // namespace stream
} // namespace bia