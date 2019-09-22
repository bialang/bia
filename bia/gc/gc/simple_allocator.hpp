#pragma once

#include "memory_allocator.hpp"

#include <cstdint>
#include <functional>

namespace bia {
namespace gc {

/*
 A simple implememntation of the @ref memory_allocator that uses the given allocator and free functions without any
 additional synchronozation/caching.
*/
class simple_allocator : public memory_allocator
{
public:
	typedef std::function<void*(std::size_t)> allocate_fun_type;
	typedef std::function<void(void*)> free_fun_type;

	simple_allocator(allocate_fun_type allocate_fun = &std::malloc, free_fun_type free_fun = &std::free) noexcept
	{
		this->allocate_fun = allocate_fun;
		this->free_fun	 = free_fun;
	}
	virtual void deallocate(void* ptr, std::size_t previous_size) override
	{
		free_fun(static_cast<int8_t*>(ptr) - aligned(previous_size));
	}
	virtual void* allocate(std::size_t size, std::size_t previous_size) override
	{
		auto x = aligned(previous_size);

		return static_cast<int8_t*>(allocate_fun(size + x)) + x;
	}

private:
	allocate_fun_type allocate_fun;
	free_fun_type free_fun;

	static std::size_t aligned(std::size_t x)
	{
		return (x + alignment - 1) / alignment * alignment;
		;
	}
};

} // namespace gc
} // namespace bia