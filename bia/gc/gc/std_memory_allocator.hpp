#pragma once

#include "memory_allocator.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <util/gsl.hpp>
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

	std_memory_allocator(util::not_null<std::shared_ptr<memory_allocator>> allocator) noexcept
	    : _allocator(std::move(allocator.get()))
	{}
	template<typename U>
	std_memory_allocator(const std_memory_allocator<U>& copy) noexcept : _allocator(copy._allocator)
	{}
	template<typename U, typename... Args>
	void construct(util::not_null<U*> ptr, Args&&... args)
	{
		new (ptr) U(std::forward<Args>(args)...);
	}
	template<typename U>
	void destroy(util::not_null<U*> ptr)
	{
		ptr->~U();
	}
	void deallocate(pointer ptr, size_type)
	{
		_allocator->deallocate(ptr);
	}
	pointer allocate(size_type n)
	{
		return static_cast<pointer>(_allocator->allocate(n * sizeof(T)));
	}
	template<typename U>
	bool operator==(const std_memory_allocator<U>& other) noexcept
	{
		return _allocator == other._allocator;
	}
	template<typename U>
	bool operator!=(const std_memory_allocator<U>& other) noexcept
	{
		return !operator==(other);
	}

private:
	template<typename U>
	friend class std_memory_allocator;

	std::shared_ptr<memory_allocator> _allocator;
};

} // namespace gc
} // namespace bia