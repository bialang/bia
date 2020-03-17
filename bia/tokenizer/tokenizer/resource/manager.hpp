#ifndef BIA_TOKENIZER_RESOURCE_MANAGER_HPP_
#define BIA_TOKENIZER_RESOURCE_MANAGER_HPP_

#include "memory/streambuf.hpp"
#include "size.hpp"
#include "state.hpp"

#include <cstddef>
#include <gc/memory_allocator.hpp>
#include <gc/std_memory_allocator.hpp>
#include <memory>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace resource {

class manager
{
public:
	/**
	 * Constructor.
	 *
	 * @param allocator the memory allocator
	 * @param page_size the size of each page
	 */
	manager(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator, std::size_t page_size) noexcept;
	~manager();
	/**
	 * Starts a new memory sequence.
	 *
	 * @pre buf_active() must return `false`
	 *
	 * @param avoid_duplicates if `true` removes this memory sequence if it is a duplicate
	 * @throw
	 */
	memory::streambuf start_memory(bool avoid_duplicates);
	/**
	 * Saves the current state of the resource manager.
	 *
	 * @pre `buf_active() == false`
	 *
	 * @returns the current state
	 */
	state save_state() const;
	/**
	 * Restores an old state.
	 *
	 * @pre
	 */
	void restore_state(const state& old);
	/**
	 * Checks whether a streambuf is currently active.
	 *
	 * @returns `true` if a streambuf is currently active
	 */
	bool buf_active() const noexcept;

private:
	friend memory::streambuf;

	/** whether a streambuf is active */
	bool _buf_active = false;
	/** size of a single page */
	std::size_t _page_size;
	/** all currently allocated pages */
	std::vector<util::byte*, gc::std_memory_allocator<util::byte*>> _pages;
	/** the current state */
	state _state;
	/** the memory allocator */
	std::shared_ptr<gc::memory_allocator> _allocator;

	/**
	 * Allocates the next page if no more pages are available and returns its beginning and the end.
	 *
	 * @returns a pair with the beginning and the end for that page
	 * @throw see gc::memory_allocator::checked_allocate()
	 */
	std::pair<util::byte*, util::byte*> _next_page();
};

} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif