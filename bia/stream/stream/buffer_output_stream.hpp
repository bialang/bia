#pragma once

#include "output_stream.hpp"

#include <cstdint>
#include <gc/memory_allocator.hpp>

namespace bia {
namespace stream {

class buffer_output_stream : public output_stream
{
public:
	buffer_output_stream(bia::gc::memory_allocator* allocator) noexcept;
	buffer_output_stream(const buffer_output_stream& copy) = delete;
	buffer_output_stream(buffer_output_stream&& move);
	virtual ~buffer_output_stream();
	virtual void write(const void* buffer, std::size_t size) override;
	virtual void reserve(std::size_t additional_size) override;
	const void* data() const noexcept;
	std::size_t size() const noexcept;

private:
	std::size_t current_size;
	std::size_t max_size;
	std::int8_t* buffer;
	gc::memory_allocator* allocator;
};

}
} // namespace bia