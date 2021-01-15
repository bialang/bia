#ifndef BIA_GC_MEMORY_SIMPLE_ALLOCATOR_HPP_
#define BIA_GC_MEMORY_SIMPLE_ALLOCATOR_HPP_

#include "allocator.hpp"

#include <cstdlib>
#include <functional>

namespace bia {
namespace gc {
namespace memory {

/**
 * A simple implememntation of the @ref allocator that uses the given allocator and free functions without any
 * additional synchronozation/caching.
 */
class simple_allocator : public Allocator
{
public:
	typedef std::function<void*(std::size_t)> allocate_fun_type;
	typedef std::function<void(void*)> free_fun_type;

	simple_allocator(allocate_fun_type allocate_fun = &std::malloc,
	                 free_fun_type free_fun         = &std::free) noexcept
	    : _allocate_fun{ std::move(allocate_fun) }, _free_fun{ std::move(free_fun) }
	{}
	void deallocate(void* ptr) override
	{
		_free_fun(ptr);
	}
	void* allocate(std::size_t size) override
	{
		return _allocate_fun(size);
	}

private:
	allocate_fun_type _allocate_fun;
	free_fun_type _free_fun;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif
