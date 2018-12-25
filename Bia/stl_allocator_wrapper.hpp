#pragma once

#include <memory>
#include <utility>
#include <cstddef>

#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

/**
 * @brief A STL compatible allocator wrapper.
 *
 * A STL compatible allocator for wrapping a Bia allocator.
 *
 * @tparam Type The type that should be allocated.
 *
 * @see @ref allocator, @ref executable_allocator
*/
template<typename Type>
class stl_allocator_wrapper
{
public:
	/** The value type of this allocator. */
	typedef Type value_type;
	/** The type of the allocated pointer. */
	typedef Type* pointer;
	/** The type of the allocated pointer as const. */
	typedef const Type* const_pointer;
	/** The reference type of the allocated object. */
	typedef Type& reference;
	/** The const reference type of the allocated object. */
	typedef const Type& const_reference;
	/** The type of the size of the pointers. */
	typedef memory::size_type size_type;
	/**
	 * @brief Rebinds the stl_allocator_wrapper to a new type.
	 *
	 * @tparam Ty The new type.
	*/
	template<typename Ty>
	struct rebind
	{
		/** The stl_allocator_wrapper with the new type. */
		typedef stl_allocator_wrapper<Ty> other;
	};

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocator The memory allocator.
	*/
	explicit stl_allocator_wrapper(const std::shared_ptr<allocator> & _allocator) noexcept : _allocator(_allocator)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocator The memory allocator.
	*/
	explicit stl_allocator_wrapper(std::shared_ptr<allocator> && _allocator) noexcept : _allocator(std::move(_allocator))
	{
	}
	/**
	 * Copy-Constructor.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @tparam Ty The type of the copy.
	 *
	 * @param _copy The object that should be copied.
	*/
	template<typename Ty>
	explicit stl_allocator_wrapper(const stl_allocator_wrapper<Ty> & _copy) noexcept : _allocator(_copy._allocator)
	{
	}
	/**
	 * Deallocates the memory address allocated by allocate().
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _ptr The allocated address.
	 * @param _size The size of the allocation.
	 *
	 * @throws See allocator::deallocate().
	*/
	void deallocate(pointer _ptr, size_type _size)
	{
		_allocator->deallocate(cast_allocation<void>(allocation<Type>{ _ptr, _size * sizeof(Type) }));
	}
	/**
	 * Allocates memory with the desired size.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _size The desired size.
	 *
	 * @throws See allocator::allocate().
	*/
	pointer allocate(size_type _size)
	{
		return static_cast<pointer>(_allocator->allocate(_size * sizeof(Type)).first);
	}

private:
	template<typename Ty>
	friend class stl_allocator_wrapper;

	/** The underlying Bia allocator. */
	std::shared_ptr<allocator> _allocator;
};

}
}
}
