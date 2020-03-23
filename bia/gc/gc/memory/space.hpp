#ifndef BIA_GC_MEMORY_SPACE_HPP_
#define BIA_GC_MEMORY_SPACE_HPP_

#include "allocator.hpp"
#include "iterator.hpp"
#include "std_allocator.hpp"

#include <cstdint>
#include <limits>
#include <memory>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace gc {
namespace memory {

class space
{
public:
	typedef std::size_t size_type;

	/** describes the current position */
	constexpr static size_type cpos = std::numeric_limits<std::size_t>::max();

	/**
	 * Constructor.
	 *
	 * @param allocator the memory allocator
	 * @param page_size the size of each memory page in bytes
	 */
	space(util::not_null<std::shared_ptr<allocator>> allocator, std::size_t page_size) noexcept;
	space(const space& copy) = delete;
	space(space&& move) noexcept;
	~space();

	/**
	 * Truncates the space and making it effectively smaller.
	 *
	 * @pre valid()
	 * @pre `s <= size()`
	 *
	 * @param s the new size in bytes
	 */
	void truncate(size_type s);
	/**
	 * Checks whether this space is valid.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept;
	/**
	 * The size of this space.
	 *
	 * @pre valid()
	 *
	 * @returns the size in bytes
	 */
	size_type size() const;
	/**
	 * The capacity of this space. In other words the maximum size without more allocations.
	 *
	 * @pre valid()
	 *
	 * @returns the capacity in bytes
	 */
	size_type capacity() const;
	util::not_null<util::span<util::byte>> next_region(size_type size);
	iterator cursor(size_type pos = cpos) const;
	space& operator=(space&& move) noexcept;

private:
	/** the active memory allocator */
	std::shared_ptr<allocator> _allocator;
	/** all allocated pages */
	std::shared_ptr<page_container_type> _pages;
	/** size of every page */
	size_type _page_size;
	/** current page index */
	size_type _index = 0;
	/** offset of the current page */
	size_type _offset = 0;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif