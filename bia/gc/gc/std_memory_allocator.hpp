#pragma once

#include "memory_allocator.hpp"

#include <cstddef>
#include <cstdint>
#include <new>
#include <utility>

namespace bia {
namespace gc {

/*
 A memory allocator wrapper for the C++ STL.
*/
template<typename T>
class std_memory_allocator
{
public:
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template<typename U>
	struct rebind
	{
		typedef std_memory_allocator<U> other;
	};

	std_memory_allocator(memory_allocator* allocator) noexcept
		: allocator(allocator)
	{}
	template<typename U>
	std_memory_allocator(const std_memory_allocator<U>& copy) noexcept
		: allocator(copy.allocator)
	{}
	template<typename U, typename... Args>
	void construct(U* ptr, Args&&... args)
	{
		new (ptr) U(std::forward<Args>(args)...);
	}
	template<typename U>
	void destroy(U* ptr)
	{
		ptr->~U();
	}
	void deallocate(pointer ptr, size_type n)
	{
		allocator->deallocate(ptr, 0);
	}
	pointer allocate(size_type n)
	{
		return static_cast<pointer>(allocator->allocate(n * sizeof(T), 0));
	}
	template<typename U>
	bool operator==(const std_memory_allocator<U>& other) noexcept
	{
		return allocator == other.allocator;
	}
	template<typename U>
	bool operator!=(const std_memory_allocator<U>& other) noexcept
	{
		return !operator==(other);
	}

private:
	template<typename U>
	friend class std_memory_allocator;

	memory_allocator* const allocator;
};

} // namespace gc
} // namespace bia