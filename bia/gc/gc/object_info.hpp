#pragma once

#include <atomic>
#include <cstdint>

namespace bia {
namespace gc {

constexpr auto object_alignment = sizeof(std::intptr_t);

struct alignas(object_alignment) object_info
{
	/** an index for the garbage collector indicating if this value was missed */
	std::atomic_uint32_t miss_index;
	/** the current mark */
	bool mark;
	/** whether this object is a leaf or a node */
	const bool leaf;

	object_info(bool mark, bool leaf) noexcept : mark(mark), leaf(leaf)
	{}
};

} // namespace gc
} // namespace bia