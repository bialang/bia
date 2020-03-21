#ifndef BIA_TOKENIZER_RESOURCE_MANAGER_HPP_
#define BIA_TOKENIZER_RESOURCE_MANAGER_HPP_

#include "memory/streambuf.hpp"
#include "size.hpp"
#include "state.hpp"

#include <cstddef>
#include <gc/memory_allocator.hpp>
#include <memory>
#include <util/gsl.hpp>

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
	 * Stops the currently active buffer.
	 * 
	 * @pre `buf_active() == true`
	 * @post `buf_active() == false`
	 * 
	 * @param[in] discard whether to discard the memory
	 * @returns the memory object describing the bytes
	*/
	memory::memory stop_memory(memory::streambuf& buf);
	void discard_memory(memory::streambuf& buf);
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
	std::shared_ptr<memory::page_container_type> _pages;
	/** the current state; only updated when memory is stopped or a new page is allocated */
	state _state{};
	/** the state when a buffer was created; only valid if a buffer is active */
	state _buf_state;
	/** the memory allocator */
	std::shared_ptr<gc::memory_allocator> _allocator;

	/**
	 * Returns the next size.
	*/
	std::pair<size*, util::byte*> _next_size();
};

} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif