#ifndef BIA_GC_MEMORY_SPACE_HPP_
#define BIA_GC_MEMORY_SPACE_HPP_

#include "allocator.hpp"
#include "std_allocator.hpp"
#include "iterator.hpp"

#include <cstdint>
#include <memory>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace gc {
namespace memory {

class space
{
public:
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
	 * Moves the cursor back by `offset` bytes making the space effectively smaller.
	 *
	 * @pre valid()
	 * @pre `offset <= size()`
	 *
	 * @param offset the offset in bytes
	 */
	void move_back(std::size_t offset);
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
	std::size_t size() const;
	/**
	 * The capacity of this space. In other words the maximum size without more allocations.
	 *
	 * @pre valid()
	 *
	 * @returns the capacity in bytes
	 */
	std::size_t capacity() const;
	util::not_null<util::span<util::byte>> next_region(std::size_t size);
	iterator cursor() const;
	space& operator=(space&& move) noexcept;

private:
	/** the active memory allocator */
	std::shared_ptr<allocator> _allocator;
	/** all allocated pages */
	std::shared_ptr<page_container_type> _pages;
	/** size of every page */
	std::size_t _page_size;
	/** current page index */
	std::size_t _index = 0;
	/** offset of the current page */
	std::size_t _offset = 0;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif