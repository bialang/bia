#pragma once

#include "memory_allocator.hpp"
#include "object.hpp"
#include "object_ptr.hpp"
#include "root.hpp"
#include "std_memory_allocator.hpp"

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstring>
#include <exception/implementation_error.hpp>
#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_set>
#include <util/data/synchronized_set.hpp>
#include <util/data/synchronized_stack.hpp>
#include <util/thread/phaser.hpp>
#include <util/thread/shared_lock.hpp>
#include <util/thread/shared_spin_mutex.hpp>
#include <util/thread/spin_mutex.hpp>
#include <util/thread/thread_pool.hpp>
#include <utility>
#include <vector>

namespace bia {
namespace gc {

/*
 A garbage collector highly optimized for the BVM. Using this collector for custom task is not recommended.

 @see memory_allocator
*/
class gc
{
public:
	class token;

	/*
	 Constructor.

	 @param allocator provides the required memory for the allocations
	 @param thread_pool (optional) launches the gc thread for concurrent
	 collection; this pool should be exclusively used by this collector
	*/
	gc(std::unique_ptr<memory_allocator> allocator, std::unique_ptr<bia::util::thread::thread_pool> thread_pool)
		: mem_allocator(std::move(allocator))
	{
		// Start gc main thread
		if (thread_pool && thread_pool->max_pool_size() > 0 && thread_pool->task_count() == 0) {
			thread_pool->execute(std::bind(&gc::main_thread, this));
		}
	}
	/*
	 Registeres the current thread. If this thread has already been registered, an exception is thrown.

	 @returns a token which deregisteres this thread upon destruction
	*/
	token register_thread()
	{
		// There is already a registered instance
		if (active_gc_instance) {
			throw exception::implementation_error(u"active gc instance detected");
		}

		active_gc_instance = this;
		registered_thread_count.fetch_add(1, std::memory_order_relaxed);

		return { this };
	}
	void force_synchronous_run(bia::util::thread::thread_pool* thread_pool)
	{
		// Wait for all threads that are using the gc to pause

		bool mark = false;

		if (thread_pool) {
		} else {
			// Mark
			for (std::size_t i = 0, c = roots.size(); i < c; ++i) {
				auto root = roots[i];

				for (std::size_t j = 0; j < root.size; ++j) {
					auto ptr = root.ptrs->get();

					if (ptr) {
						object::gc_mark(ptr, mark);
					}
				}
			}

			// Sweep
			for (std::size_t i = 0, c = allocated.size(); i < c; ++i) {
				auto info = allocated[i];

				if (info->marked.load(std::memory_order_acquire) != mark) {
					auto ptr = allocator->pointer(info);

					// Destroy
					if (!info->leaf) {
						static_cast<object*>(ptr)->~object();
					}

					// Deallocate
					allocator->deallocate(ptr, true);
				}
			}
		}
	}
	root create_root(std::size_t ptr_count)
	{
		auto ptr = static_cast<object_ptr*>(mem_allocator->checked_allocate(ptr_count * sizeof(object_ptr), 0));

		// Construct the pointer objects
		for (std::size_t i = 0; i < ptr_count; ++i) {
			new (ptr + i) object_ptr();
		}

		roots.insert({ ptr, ptr_count });

		return { ptr, ptr_count };
	}
	void free_root(root obj)
	{
		roots.erase(obj);

		// Destroy the pointer objects
		for (std::size_t i = 0; i < obj.size; ++i) {
			obj.ptrs[i].~object_ptr();
		}

		mem_allocator->deallocate(obj.ptrs, 0);
	}
	void* allocate(std::size_t size, bool zero = false)
	{
		auto ptr = allocate_impl(size, true);

		if (zero) {
			std::memset(ptr, 0, size);
		}

		return ptr;
	}
	/*
	 Allocates and constructs the given type with its arguments.

	 @param args are forwarded to the constructor of *T*
	 @returns the newly constructed object as a @ref object_ptr
	 @throws allocate_impl()
	 @tparam T is the type that should be created
	 @tparam Args are the argument types for the constructor
	*/
	template<typename T, typename... Args>
	typename std::enable_if<std::is_base_of<object, T>::value, T*>::type construct(Args&&... args)
	{
		static_assert(alignof(T) <= memory_allocator::alignment,
					  "the alignement cannot be greater than the max alignment "
					  "of the memory allocator");
		static_assert(alignof(object_info) <= memory_allocator::previous_data_alignment,
					  "the required alignment of object info is not met");

		return new (allocate_impl(sizeof(T), false)) T(std::forward<Args>(args)...);
	}
	/*
	 Returns the memory allocator of this garbage collector. Memory allocated
	 through this allocator will not be garbage collected.

	 @returns the internally used memory allocator
	*/
	memory_allocator* allocator() noexcept
	{
		return mem_allocator;
	}
	/*
	 Returns the active gc of the current thread.

	 @returns the current gc if set, otherwise `nullptr`
	*/
	static gc* active_gc() noexcept;

private:
	struct worker_context
	{
		/* manages the synchronization between the main thread and its workers
		 */
		util::thread::phaser phaser;
		/* contains every object that has not been marked and is free to
		 * deallocate */
		util::data::synchronized_stack<std::vector<void*, std_memory_allocator<void*>>, util::thread::spin_mutex>
			free_list;
		bool destroy;
		/* the current, as active considered, mark */
		bool mark;
	};

	/* the currently active instance */
	static thread_local gc* active_gc_instance;
	/* the memory allocator */
	std::unique_ptr<memory_allocator> mem_allocator;
	/* a list of all gc monitored objects */
	util::data::synchronized_set<std::unordered_set<object_info*, std::hash<object_ptr*>, std::equal_to<object_ptr*>,
													std_memory_allocator<object_info*>>,
								 util::thread::spin_mutex>
		allocated;
	/* a list of all created roots */
	util::data::synchronized_set<
		std::unordered_set<root, std::hash<root>, std::equal_to<object_ptr*>, std_memory_allocator<root>>,
		util::thread::spin_mutex>
		roots;
	/* a stack which stores all (potentially) missed objects while the gc was
	 concurrently collecting */
	util::data::synchronized_stack<std::vector<void*, std_memory_allocator<void*>>, util::thread::spin_mutex>
		missed_objects;
	/* locks shared when allocating memory */
	util::thread::shared_spin_mutex gc_mutex;
	/* the current gc mark; this is only set by the main gc thread and is locked by gc_mutex */
	bool current_mark;
	/* the count of registered threads */
	std::atomic_size_t registered_thread_count;
	/* the count of reported threads */
	std::atomic_size_t reported_thread_count;
	/* marks whether the gc is currently in the marking phase */
	std::atomic_bool gc_active;
	std::atomic_bool first_marking_phase;

	void* allocate_impl(std::size_t size, bool leaf)
	{
		auto ptr  = mem_allocator->checked_allocate(size + sizeof(object_info), sizeof(object_info));
		auto info = new (ptr) object_info(){};

		info->leaf = leaf;

		// synchronize with the gc thread
		util::thread::shared_lock<decltype(gc_mutex)> lock(gc_mutex);

		allocated.insert(info);

		return ptr + sizeof(object_info);
	}
	void main_thread(std::unique_ptr<bia::util::thread::thread_pool> thread_pool)
	{
		{
			{
				// signal that gc is active and reset the reported thread count
				std::unique_lock<decltype(gc_mutex)> lock(gc_mutex);

				reported_thread_count.store(0, std::memory_order_relaxed);
				current_mark = !current_mark;
				gc_active.store(true, std::memory_order_release);
			}

			// wait for acknowlegement from the user threads; if new threads are registered after this check completes
			// there will be no problem since they must update their state either way
			while (reported_thread_count.load(std::memory_order_consume) <
				   registered_thread_count.load(std::memory_order_consume))
				;

			// start workers
			worker_context context{};
			auto phase = context.phaser.register_party(2);

			context.mark = current_mark;

			for (auto i = thread_pool->task_count(), c = thread_pool->max_pool_size(); i < c; ++i) {
				context.phaser.register_party();
				thread_pool->execute(std::bind(&gc::worker_thread, this, std::ref(context)));
			}

			// Work through own work

			// Synchronize with worker threads
			context.phaser.arrive();

			// Synchronize with user threads
			gc_active.store(false, std::memory_order_release);

			// Wait for acknowlegement from the user threads

			// Advance to next phase

			// Work through items in the missed list
			void* ptr = nullptr;

			while (missed_objects.pop(ptr)) {
				object::gc_mark(ptr, context.mark);
			}

			// Synchronize with workers
			context.phaser.arrive_and_wait();

			// Signal user threads that they don't have to mind the gc anymore
			gc_active.store(false, std::memory_order_release);

			// Wait for acknowlegement from the user threads

			// Start sweeping
		}
	}
	void worker_thread(worker_context& context)
	{
		// Work through the available work

		// Signal the main thread that marking is done
		context.phaser.arrive_and_wait();

		// Work through remaining items in the list
		void* ptr = nullptr;

		while (missed_objects.pop(ptr)) {
			object::gc_mark(ptr, context.mark);
		}

		context.phaser.arrive_and_wait();

		// Destroy the object
		if (context.destroy) {
		}
		switch (context.sweep_mode) {
		case worker_context::SWEEP_MODE::LEAF_ONLY: break;
		}
	}
};

class gc::token
{
public:
	token(const token& copy) = delete;
	token(token&& move) noexcept : g(move.g)
	{
		move.g	= nullptr;
		is_active = move.is_active;
	}
	/*
	 Destructor.
	*/
	~token() noexcept
	{
		// deregister from gc
		if (g) {
			g->registered_thread_count.fetch_sub(1, std::memory_order_consume);
			active_gc_instance = nullptr;
		}
	}
	/*
	 Sets the destination pointer to the source pointer. If the gc is active, additional work is done.

	 @param[out] dest defines the destination
	 @param src defines the source
	*/
	void set_object_ptr(object_ptr& dest, const object_ptr& src)
	{
		auto ptr = src.get();

		if (is_active) {
			g->missed_objects.push(ptr);
		}

		dest.set(ptr);
	}
	/*
	 Sets the destination pointer to the source pointer. If the gc is active, additional work is done.

	 @param[out] dest defines the destination
	 @param src defines the source
	*/
	void set_object_ptr(object_ptr& dest, const void* src)
	{
		if (is_active) {
			g->missed_objects.push(src);
		}

		dest.set(src);
	}
	/*
	 Gc monitored memory may only be allocated after an update. The time between updates should be minimal in order to
	 avoid long waiting times on the gc threads.

	 @returns `true` if the gc is currently in the marking phase, otherwise
	 `false`
	*/
	void update() noexcept
	{
		// check if gc is active
		if (is_active != g->gc_active.load(std::memory_order_consume)) {
			// tell gc that the status has been acknowledged
			g->reported_thread_count.fetch_add(1, std::memory_order_relaxed);

			is_active = !is_active;
		}

		return is_active;
	}

private:
	/* the parent gc */
	gc* g;
	/* the last status of the gc */
	bool is_active;

	token(gc* g) noexcept : g(g)
	{
		is_active = false;
	}
};

} // namespace gc
} // namespace bia