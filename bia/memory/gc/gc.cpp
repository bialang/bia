#include "gc.hpp"

#include <bia/log/log.hpp>
#include <chrono>
#include <set>

using namespace bia::memory::gc;

GC::GC(util::Not_null<std::shared_ptr<Allocator>> allocator) : _allocator{ std::move(allocator.get()) }
{}

GC::~GC() noexcept
{
	BIA_LOG(DEBUG, "Freeing {} missed pointers.", _pointers.size());
	// free all pointers
	for (auto ptr : _pointers) {
		_sweep(ptr);
	}
}

GC_able<void*> GC::allocate(std::size_t size)
{
	std::is_trivial<GC_able<void*>>::value;
	const auto ptr = _allocator->allocate(size);
	BIA_LOG(TRACE, "GC allocated ptr={}", ptr);
	try {
		std::lock_guard<std::mutex> _{ _mutex };
		_pointers.push_back(ptr);
	} catch (...) {
		BIA_LOG(CRITICAL, "Failed to append newly create GC able object to the pointers list.");
		_allocator->deallocate(ptr);
		throw;
	}
	return { ptr };
}

void GC::run()
{
	BIA_LOG(DEBUG, "Starting GC cycle");
	std::lock_guard<std::mutex> _{ _mutex };
	std::set<void*> reachable;
#if BIA_LOG_IS(DEBUG)
	const auto start = std::chrono::high_resolution_clock::now();
#endif

	// marking phase
	for (const auto& root : _roots) {
		std::lock_guard<std::mutex> _{ root->_mutex };
		for (std::size_t i = 0; i < root->_memory.size_bytes() / sizeof(void*); ++i) {
			if (root->_meta[i / 8] & (1 << i % 8)) {
				void* ptr = *reinterpret_cast<void**>(root->_memory.begin() + i * sizeof(void*));
				BIA_LOG(TRACE, "ptr={} is reachable", ptr);
				reachable.insert(ptr);
			}
		}
	}

	// sweep
	std::size_t reclaimed = 0;
	for (auto it = _pointers.begin(); it != _pointers.end();) {
		if (reachable.find(*it) == reachable.end()) {
			_sweep(*it);
			it = _pointers.erase(it);
			reclaimed++;
		} else {
			++it;
		}
	}

	BIA_LOG(DEBUG, "GC finished (live={}, reclaimed={}, time={})", _pointers.size(), reclaimed,
	        std::chrono::high_resolution_clock::now() - start);
}

void GC::register_stack(Stack& stack)
{
	BIA_LOG(TRACE, "registering stack with base={}", static_cast<void*>(stack._memory.begin()));
	std::lock_guard<std::mutex> _{ _mutex };
	_roots.push_back(&stack);
}

void GC::unregister_stack(Stack& stack)
{
	std::lock_guard<std::mutex> _{ _mutex };
	for (auto i = _roots.begin(); i != _roots.end(); ++i) {
		if (*i == &stack) {
			_roots.erase(i);
			break;
		}
	}
}

bia::util::Not_null<std::shared_ptr<bia::memory::Allocator>> GC::allocator() noexcept
{
	return _allocator;
}

void GC::_sweep(util::Not_null<GC_able<void*>> ptr)
{
	BIA_LOG(TRACE, "Sweeping ptr={} (object: {})", ptr.get().get(), ptr.get().is_object());
	if (ptr.get().is_object()) {
		static_cast<Base*>(ptr.get())->~Base();
	}
	_allocator->deallocate(ptr.get());
}
