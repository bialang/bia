#ifndef BIA_MEMORY_SPACE_HPP_
#define BIA_MEMORY_SPACE_HPP_

#include "allocator.hpp"
#include "iterator.hpp"
#include "std_allocator.hpp"

#include <cstdint>
#include <limits>
#include <memory>
#include <bia/util/gsl.hpp>
#include <vector>

namespace bia {
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
	space(util::Not_null<std::shared_ptr<Allocator>> allocator, std::size_t page_size) noexcept;
	space(space&& move) noexcept;

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
	util::Not_null<util::Span<util::Byte*>> next_region(size_type size);
	iterator cursor(size_type pos = cpos) const;
	space& operator=(space&& move) noexcept;

private:
	/** the active memory allocator */
	std::shared_ptr<Allocator> _allocator;
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
} // namespace bia

#endif
