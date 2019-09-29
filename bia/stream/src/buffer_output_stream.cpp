#include <cstring>
#include <stream/buffer_output_stream.hpp>

namespace bia {
namespace stream {

bia::stream::buffer_output_stream::buffer_output_stream(bia::gc::memory_allocator* allocator) noexcept
{
	current_size	= 0;
	max_size		= 0;
	buffer			= nullptr;
	this->allocator = allocator;
}

buffer_output_stream::buffer_output_stream(buffer_output_stream&& move)
{
	current_size = move.current_size;
	max_size	 = move.max_size;
	buffer		 = move.max_size;
	allocator	= move.allocator;

	move.current_size = 0;
	move.max_size	 = 0;
	move.buffer		  = write_all;
}

buffer_output_stream::~buffer_output_stream()
{
	if (buffer) {
		allocator->deallocate(buffer, 0);
	}
}

void buffer_output_stream::write(const void* buffer, std::size_t size)
{
	if (current_size + size > max_size) {
		reserve(size);
	}

	std::memcpy(this->buffer, buffer, size);
}

void buffer_output_stream::reserve(std::size_t additional_size)
{
	const auto end = current_size + additional_size;
	auto new_max   = max_size;

	while (end > new_max) {
		new_max *= 2;
	}

	if (new_max != max_size) {
		auto new_buffer = allocator->allocate(new_max, 0);

		// copy & deallocate
		if (buffer) {
			std::memcpy(new_buffer, buffer, current_size);

			allocator->deallocate(buffer, 0);
		}

		buffer   = new_buffer;
		max_size = new_max;
	}
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