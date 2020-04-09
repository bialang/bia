#ifndef BIA_GC_GC_HPP_
#define BIA_GC_GC_HPP_

#include "detail/container.hpp"
#include "memory/allocator.hpp"
#include "object/base.hpp"
#include "object/header.hpp"
#include "stack.hpp"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <thread/lock/spin_mutex.hpp>
#include <type_traits>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace gc {

template<typename>
class gcable;

class stack;

class token;

/*
 A garbage collector highly optimized for the BVM. Using this collector for custom task is not recommended.

 @see memory::allocator
*/
class gc
{
public:
	/**
	 * Constructor.
	 *
	 * @param allocator provides the required memory for the allocations
	 */
	gc(util::not_null<std::shared_ptr<memory::allocator>> allocator) noexcept;
	/**
	 * Destructor.
	 */
	~gc();
	/**
	 *
	 */
	void thread_main();
	/**
	 * Blocks the current thread and runs the garbage collector. If an instance is already running, this
	 * function returns.
	 *
	 * @returns `true` if the gc was run, otherwise `false`
	 */
	bool run_once();
	/**
	 * Registeres the current thread. If this thread has already been registered, this function fails.
	 *
	 * @pre no active gc in the current thread
	 *
	 * @param count how much space the root should have
	 * @returns a token which deregisteres this thread upon destruction
	 */
	token register_thread(std::size_t count);
	/**
	 * Allocates gc monitorable memory. In order for this memory to be monitored by the garbage collector
	 * gcable::start_monitor() must be called.
	 *
	 * @param size the size of the memory
	 * @param zero (optional) whether the memory should be set to zero
	 * @returns the allocated buffer
	 * @throw see _allocate_impl()
	 */
	gcable<void> allocate(std::size_t size, bool zero = false);
	/**
	 * Allocates and constructs the given type with its arguments.
	 *
	 * @param args are forwarded to the constructor of *T*
	 * @returns the object
	 * @throw see _allocate_impl()
	 * @tparam T is the type that should be created
	 * @tparam Args are the argument types for the constructor
	 */
	template<typename T, typename... Args>
	typename std::enable_if<std::is_base_of<object::base, T>::value, gcable<T>>::type
	    construct(Args&&... args)
	{
		static_assert(alignof(T) == object::alignment, "cannot have a different object alignment");

		return { this, new (_allocate_impl(sizeof(T), false).get()) T(std::forward<Args>(args)...) };
	}
	/**
	 * Returns the memory allocator of this garbage collector. Memory allocated through this allocator will
	 * not be garbage collected.
	 *
	 * @returns the internally used memory allocator
	 */
	const std::shared_ptr<memory::allocator>& allocator() noexcept;
	/**
	 * Returns the active gc of the current thread.
	 *
	 * @returns the current gc if set, otherwise `nullptr`
	 */
	static gc* active_gc() noexcept;

private:
	friend token;
	template<typename T>
	friend class gcable;

	/** the currently active instance */
	static thread_local gc* _active_gc_instance;
	/** the memory allocator */
	std::shared_ptr<memory::allocator> _allocator;
	/** the current gc mark */
	bool _current_mark = false;
	/** the current miss index; this value is used to prevent misfreeing objects */
	std::atomic_uint32_t _miss_index;
	/** is for ensuring only one gc instance is running; using this because try_lock does not fail spuriously
	 */
	thread::lock::spin_mutex _mutex;
	/** holds every allocated element */
	detail::container<object::header*> _allocated;
	/** holds every created root */
	detail::container<stack> _roots;

	/**
	 * Allocates gc monitorable memory.
	 *
	 * @param size the size of the memory region
	 * @param leaf whether this gc object can have more gc monitored objects
	 * @returns the memory buffer
	 * @throw see memory::allocator::checked_allocate()
	 */
	util::not_null<void*> _allocate_impl(std::size_t size, bool leaf);
	/**
	 * Deallocates the pointer allocated by _allocate_impl().
	 *
	 * @param ptr the pointer
	 * @throw see memory::allocator::deallocate()
	 */
	void _free(util::not_null<void*> ptr);
	/**
	 * Starts monitoring this pointer.
	 *
	 * @pre `ptr` must be allocated by _allocate_impl() and not freed
	 *
	 * @param ptr the gcable pointer
	 */
	void _register_gcable(util::not_null<void*> ptr);
	stack _create_stack(std::size_t count);
	void _destroy_stack(stack stack);
};

} // namespace gc
} // namespace bia

#endif