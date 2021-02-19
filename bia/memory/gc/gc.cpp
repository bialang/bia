#include "gc.hpp"

#include <bia/log/log.hpp>
#include <chrono>
#include <set>

using namespace bia::memory::gc;

GC::GC(util::Not_null<std::shared_ptr<Allocator>> allocator) : _allocator{ std::move(allocator.get()) }
{}

GC_able<void*> GC::allocate(std::size_t size)
{
	auto ptr = _allocator->allocate(size);
	BIA_LOG(TRACE, "GC allocated ptr={}", ptr);
	std::lock_guard<std::mutex> _{ _mutex };
	_pointers.push_back(ptr);
	return { ptr };
}

void GC::run()
{
	BIA_LOG(DEBUG, "starting GC cycle");
	const auto start = std::chrono::high_resolution_clock::now();
	std::lock_guard<std::mutex> _{ _mutex };
	std::set<void*> reachable;

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
	for (auto i = _pointers.begin(); i != _pointers.end();) {
		if (reachable.find(*i) == reachable.end()) {
			GC_able<void*> ptr{ *i };
			BIA_LOG(TRACE, "sweeping ptr={} (object: {})", ptr.get(), ptr.is_object());
			if (ptr.is_object()) {
				static_cast<Base*>(ptr)->~Base();
			}
			_allocator->deallocate(ptr);
			i = _pointers.erase(i);
			reclaimed++;
		} else {
			++i;
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

bia::util::Not_null<std::shared_ptr<bia::memory::Allocator>> GC::allocator() noexcept
{
	return _allocator;
}
