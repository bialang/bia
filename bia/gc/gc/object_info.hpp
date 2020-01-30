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
	std::atomic_bool mark;
	/** whether this object is a leaf or a node */
	const bool leaf;
};

} // namespace gc
} // namespace bia