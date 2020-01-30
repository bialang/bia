#pragma once

#include "output_stream.hpp"

#include <cstdint>
#include <gc/memory_allocator.hpp>
#include <tuple>

namespace bia {
namespace stream {

/*
 A stream that writes the output to an underlying buffer. This stream is not thread-safe.
*/
class buffer_output_stream : public output_stream
{
public:
	/*
	 Constructor.

	 @param[in] allocator is the memory allocator
	*/
	buffer_output_stream(bia::gc::memory_allocator& allocator) noexcept;
	buffer_output_stream(const buffer_output_stream& copy) = delete;
	buffer_output_stream(buffer_output_stream&& move) noexcept;
	virtual ~buffer_output_stream();
	virtual void write(const void* buffer, std::size_t size) override;
	virtual void reserve(std::size_t additional_size) override;
	/*
	 Returns the used memory allocator.

	 @return the memory allocator
	*/
	gc::memory_allocator& memory_allocator() noexcept;
	/*
	 Takes the buffer and transfers the ownership. The buffer must be manually deallocated after use with the given
	 memory_allocator().

	 @return (buffer, size, max_size)
	*/
	std::tuple<void*, std::size_t, std::size_t> take_buffer() noexcept;

private:
	std::size_t current_size;
	std::size_t max_size;
	std::int8_t* buffer;
	gc::memory_allocator& allocator;
};

} // namespace stream
} // namespace bia