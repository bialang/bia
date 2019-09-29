#pragma once

#include "output_stream.hpp"

#include <cstdint>

namespace bia {
namespace stream {

class buffer_output_stream : public output_stream
{
public:
	virtual void write(const void* buffer, std::size_t size) override;
	virtual void reserve(std::size_t additional_size) override;
	const void* data() const noexcept;
	std::size_t size() const noexcept;

private:
	std::size_t current_size;
	std::size_t max_size;
	std::int8_t* buffer;
};

}
} // namespace bia