#include <gc/gc.hpp>
#include <stream/buffer_output_stream.hpp>
#include <cstring>

namespace bia {
namespace stream {

void buffer_output_stream::write(const void* buffer, std::size_t size)
{
	if (current_size + size > max_size) {
		reserve(size);
	}

	std::memcpy(this->buffer, buffer, size);
}

void buffer_output_stream::reserve(std::size_t additional_size)
{
}

const void* buffer_output_stream::data() const noexcept
{
	return buffer;
}

std::size_t buffer_output_stream::size() const noexcept
{
	return current_size;
}

} // namespace stream
} // namespace bia