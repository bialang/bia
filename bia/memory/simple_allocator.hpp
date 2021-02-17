#ifndef BIA_MEMORY_SIMPLE_ALLOCATOR_HPP_
#define BIA_MEMORY_SIMPLE_ALLOCATOR_HPP_

#include "allocator.hpp"

#include <cstdlib>
#include <functional>

namespace bia {
namespace memory {

/// A simple implememntation of the @ref Allocator that uses the given allocator and free functions without
/// any additional synchronozation or caching.
class Simple_allocator : public Allocator
{
public:
	typedef std::function<void*(std::size_t)> Allocate;
	typedef std::function<void(void*)> Deallocate;

	Simple_allocator(Allocate allocate = &std::malloc, Deallocate deallocate = &std::free) noexcept
	    : _allocate{ std::move(allocate) }, _deallocate{ std::move(deallocate) }
	{}
	void deallocate(void* ptr) override
	{
		_deallocate(ptr);
	}
	void* allocate(std::size_t size) override
	{
		return _allocate(size);
	}

private:
	Allocate _allocate;
	Deallocate _deallocate;
};

} // namespace memory
} // namespace bia

#endif
