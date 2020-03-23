#ifndef BIA_TOKENIZER_RESOURCE_MANAGER_HPP_
#define BIA_TOKENIZER_RESOURCE_MANAGER_HPP_

#include "../config.hpp"
#include "bia_config.hpp"
#include "streambuf.hpp"

#include <cstddef>
#include <gc/memory/space.hpp>
#include <gc/memory/view.hpp>
#include <memory>
#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace resource {

class manager
{
public:
	typedef gc::memory::space::size_type state_type;

	/**
	 * Constructor.
	 *
	 * @param allocator the memory allocator
	 * @param page_size the size of each page
	 */
	manager(util::not_null<std::shared_ptr<gc::memory::allocator>> allocator,
	        std::size_t page_size = BIA_TOKENIZER_PAGE_SIZE) noexcept;
	~manager();
	/**
	 * Starts a new memory sequence.
	 *
	 * @pre buf_active() must return `false`
	 *
	 * @param avoid_duplicates if `true` removes this memory sequence if it is a duplicate
	 * @throw
	 */
	BIA_ATTR_NO_DISCARD
	streambuf start_memory(bool avoid_duplicates);
	/**
	 * Stops the currently active buffer.
	 *
	 * @pre `buf_active() == true`
	 * @post `buf_active() == false`
	 *
	 * @param[in] discard whether to discard the memory
	 * @returns the memory object describing the bytes
	 */
	BIA_ATTR_NO_DISCARD
	gc::memory::view stop_memory(streambuf& buf);
	void discard_memory(streambuf& buf);
	/**
	 * Saves the current state of the resource manager.
	 *
	 * @pre `buf_active() == false`
	 *
	 * @returns the current state
	 */
	state_type save_state() const;
	/**
	 * Restores an old state.
	 *
	 * @pre
	 */
	void restore_state(state_type old);
	/**
	 * Checks whether a streambuf is currently active.
	 *
	 * @returns `true` if a streambuf is currently active
	 */
	bool buf_active() const noexcept;

private:
	friend streambuf;

	/** whether a streambuf is active */
	bool _buf_active = false;
	/** the space where to put all the data */
	gc::memory::space _space;
};

} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif