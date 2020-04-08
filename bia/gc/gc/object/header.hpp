#ifndef BIA_GC_OBJECT_HEADER_HPP_
#define BIA_GC_OBJECT_HEADER_HPP_

#include <atomic>
#include <cstdint>

namespace bia {
namespace gc {
namespace object {

constexpr auto object_alignment = sizeof(std::intptr_t);

struct alignas(object_alignment) header
{
	/** an index for the garbage collector indicating if this value was missed */
	std::atomic_uint32_t miss_index;
	/** the current mark */
	bool mark;
	/** whether this object is a leaf or a node */
	const bool leaf;

	header(bool mark, bool leaf) noexcept : mark(mark), leaf(leaf)
	{}
};

} // namespace object
} // namespace gc
} // namespace bia

#endif