#ifndef BIA_GC_MEMORY_STD_ALLOCATOR_HPP_
#define BIA_GC_MEMORY_STD_ALLOCATOR_HPP_

#include "allocator.hpp"

#include <bia/util/gsl.hpp>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <utility>

namespace bia {
namespace gc {
namespace memory {

/// A memory allocator wrapper for the C++ STL.
template<typename Type>
class Std_allocator
{
public:
	typedef Type* pointer;
	typedef const Type* const_pointer;
	typedef Type& reference;
	typedef const Type& const_reference;
	typedef Type value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template<typename Other>
	struct rebind
	{
		typedef Std_allocator<Other> other;
	};

	Std_allocator(util::Not_null<std::shared_ptr<Allocator>> allocator) noexcept
	    : _allocator(std::move(allocator.get()))
	{}
	template<typename Other>
	Std_allocator(const Std_allocator<Other>& copy) noexcept : _allocator(copy._allocator)
	{}
	template<typename Other, typename... Args>
	void construct(util::Not_null<Other*> ptr, Args&&... args)
	{
		new (ptr) Other(std::forward<Args>(args)...);
	}
	template<typename Other>
	void destroy(util::Not_null<Other*> ptr)
	{
		ptr->~Other();
	}
	void deallocate(pointer ptr, size_type)
	{
		_allocator->deallocate(ptr);
	}
	pointer allocate(size_type n)
	{
		return static_cast<pointer>(_allocator->allocate(n * sizeof(Type)));
	}
	template<typename Other>
	bool operator==(const Std_allocator<Other>& other) noexcept
	{
		return _allocator == other._allocator;
	}
	template<typename Other>
	bool operator!=(const Std_allocator<Other>& other) noexcept
	{
		return !operator==(other);
	}

private:
	template<typename Other>
	friend class Std_allocator;

	std::shared_ptr<Allocator> _allocator;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif
