#include <gc/gc.hpp>

namespace bia {
namespace gc {

thread_local gc* gc::active_gc_instance = nullptr;

gc::gc(std::unique_ptr<memory_allocator> allocator, std::unique_ptr<bia::thread::thread_pool> thread_pool)
    : mem_allocator(std::move(allocator)),
      missed_objects(std::vector<void*, std_memory_allocator<void*>>(mem_allocator.get()))
{
	// Start gc main thread
	/*if (thread_pool && thread_pool->max_pool_size() > 0 && thread_pool->task_count() == 0) {
	    thread_pool->execute(std::bind(&gc::main_thread, this));
	}*/
}

void gc::run_synchronously()
{
	main_thread();
}

void* gc::allocate(std::size_t size, bool zero)
{
	auto ptr = allocate_impl(size, true);

	if (zero) {
		std::memset(ptr, 0, size);
	}

	return ptr;
}

memory_allocator* gc::allocator() noexcept
{
	return mem_allocator.get();
}

gc* gc::active_gc() noexcept
{
	return active_gc_instance;
}

void* gc::allocate_impl(std::size_t size, bool leaf)
{
	auto ptr  = mem_allocator->checked_allocate(size + sizeof(object_info), sizeof(object_info));
	auto info = new (ptr) object_info();

	info->leaf = leaf;

	mutex.lock_shared();
	info->marked.store(current_mark, std::memory_order_relaxed);
	mutex.unlock_shared();

	std::unique_lock<decltype(allocated_mutex)> lock(allocated_mutex);

	allocated.insert(info);

	return static_cast<int8_t*>(ptr) + sizeof(object_info);
}

root gc::create_root(std::size_t ptr_count)
{
	auto ptr = static_cast<object_ptr*>(mem_allocator->checked_allocate(ptr_count * sizeof(object_ptr), 0));

	// Construct the pointer objects
	for (std::size_t i = 0; i < ptr_count; ++i) {
		new (ptr + i) object_ptr();
	}

	std::unique_lock<decltype(roots_mutex)> lock(roots_mutex);

	roots.insert({ ptr, ptr_count });

	return { ptr, ptr_count };
}

void gc::free_root(root obj)
{
	{
		std::unique_lock<decltype(roots_mutex)> lock(roots_mutex);

		roots.erase(obj);
	}

	// Destroy the pointer objects
	for (std::size_t i = 0; i < obj.size(); ++i) {
		obj.ptrs[i].~object_ptr();
	}

	mem_allocator->deallocate(obj.ptrs, 0);
}

void gc::main_thread()
{
	mutex.lock();
	is_active    = true;
	current_mark = !current_mark;
	mutex.unlock();

	// mark
	{
		std::unique_lock<decltype(roots_mutex)> lock(roots_mutex);

		for (auto r : roots) {
			for (std::size_t i = r.size(); i-- > 0;) {
				object::gc_mark(r[i], current_mark);
			}
		}
	}

	// finished
	mutex.lock();
	is_active = false;
	mutex.unlock();

	// mark missed
	void* missed = nullptr;

	while (missed_objects.pop(missed)) {
		object::gc_mark(missed, current_mark);
	}
	printf("Size of roots: %zi\n", roots.size());
	printf("Size of allocated: %zi\n", allocated.size());
	// sweep
	{
		std::unique_lock<decltype(allocated_mutex)> lock(allocated_mutex);

		for (auto i = allocated.begin(); i != allocated.end();) {
			auto info = *i;

			if (info->marked.load(std::memory_order_consume) != current_mark) {
				if (!info->leaf) {
					reinterpret_cast<object*>(info + 1)->~object();
				}

				printf("GCing %p\n", info + 1);

				mem_allocator->deallocate(info, sizeof(object_info));
				i = allocated.erase(i);
			} else {
				++i;
				printf("Not marked %p\n", info + 1);
			}
		}
	}
}

} // namespace gc
} // namespace bia