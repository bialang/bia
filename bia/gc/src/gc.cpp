#include "gc/gc.hpp"

#include "gc/token.hpp"
#include "gc/gcable.hpp"
#include "gc/stack.hpp"

#include <cstring>
#include <log/log.hpp>
#include <thread/lock/unique_lock.hpp>
#include <thread/thread.hpp>


using namespace bia::gc;

thread_local gc* gc::_active_gc_instance = nullptr;

gc::gc(bia::util::not_null<std::shared_ptr<memory::allocator>> allocator) noexcept
    : _allocator(allocator.get()), _allocated(allocator), _roots(allocator)
{}

gc::~gc()
{
	try {
		run_once();
	} catch (const exception::bia_error& e) {
		BIA_LOG_ERROR(CRITICAL, e);
	}

	// todo: free everything else
}

bool gc::run_once()
{
	BIA_LOG(INFO, "gc cycle requested");

	thread::lock::unique_lock<thread::lock::spin_mutex> lock(_mutex, thread::lock::try_to_lock);

	// an instance is already running
	if (!lock) {
		BIA_LOG(INFO, "gc instance already running");

		return false;
	}

	BIA_LOG(DEBUG, "preparing garbage collection");

	_current_mark = !_current_mark;

	auto miss_index      = _miss_index.fetch_add(1, std::memory_order_release) + 1;
	auto allocated_token = _allocated.begin_operation();
	auto roots_token     = _roots.begin_operation();

	BIA_LOG(DEBUG, "traversing all registered roots");

	// go through all roots and mark the objects
	for (auto& i : roots_token) {
		for (auto& j : i) {
			// mark
			if (const auto ptr = j.get()) {
				object::base::gc_mark(ptr, _current_mark);
			}
		}
	}

	// can only miss objects in multi thread environment
	if (thread::thread::supported()) {
		// go through all allocated objects and mark the missed ones
		for (auto& i : allocated_token) {
			// not marked
			if (i->mark != _current_mark) {
				// marked as miss
				if (i->miss_index.load(std::memory_order_consume) == miss_index) {
					object::base::gc_mark(&*i + 1, _current_mark);
				}
			}
		}
	}

	// go through all allocated objects and free the unmarked
	for (auto i = allocated_token.begin(); i != allocated_token.end();) {
		// not marked
		if ((*i)->mark != _current_mark) {
			if (!(*i)->leaf) {
				reinterpret_cast<object::base*>(*i + 1)->~base();
			}

			// deallocate
			(*i)->~header();

			_allocator->deallocate(*i);

			i = allocated_token.erase(i);
		} else {
			++i;
		}
	}

	return true;
}

token gc::register_thread(std::size_t count)
{
	BIA_EXPECTS(!_active_gc_instance);

	_active_gc_instance = this;

	return { this, count };
}

gcable<void> gc::allocate(std::size_t size, bool zero)
{
	auto ptr = _allocate_impl(size, true);

	if (zero) {
		std::memset(ptr.get(), 0, size);
	}

	return { this, ptr };
}

const std::shared_ptr<memory::allocator>& gc::allocator() noexcept
{
	return _allocator;
}

gc* gc::active_gc() noexcept
{
	return _active_gc_instance;
}

bia::util::not_null<void*> gc::_allocate_impl(std::size_t size, bool leaf)
{
	BIA_LOG(TRACE, "allocating {} bytes as {}", size, leaf ? "leaf" : "node");

	auto ptr =
	    static_cast<object::header*>(_allocator->checked_allocate(size + sizeof(object::header)).get());

	new (ptr) object::header{ _current_mark, leaf };

	BIA_LOG(DEBUG, "allocated gcable memory at info={} with {} bytes", static_cast<void*>(ptr), size);

	return ptr + 1;
}

void gc::_free(util::not_null<void*> ptr)
{
	auto info = static_cast<object::header*>(ptr.get()) - 1;

	info->~header();
	_allocator->deallocate(info);
}

void gc::_register_gcable(util::not_null<void*> ptr)
{
	_allocated.add(static_cast<object::header*>(ptr.get()) - 1);
}

stack gc::_create_stack(std::size_t count)
{
	auto buffer = static_cast<stack::element_type*>(
	    _allocator->checked_allocate(count * sizeof(stack::element_type)).get());

	// initialize all elements
	for (auto i = buffer, c = buffer + count; i < c; ++i) {
		new (i) stack::element_type{ nullptr };
	}

	stack s{ buffer, count };

	_roots.add(s);

	return s;
}

void gc::_destroy_stack(stack stack)
{
	_roots.remove(stack);

	for (auto& i : stack) {
		i.~pointer();
	}

	_allocator->deallocate(stack.data());
}
