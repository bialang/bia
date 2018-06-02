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
 * @see @ref allocator, @ref executable_allocator
*/
template<typename _Ty>
class stl_allocator_wrapper
{
public:
	/** The value type of this allocator. */
	typedef _Ty value_type;
	/** The type of the allocated pointers. */
	typedef _Ty* pointer;
	/** The type of the size of the pointers. */
	typedef allocator::size_type size_type;

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
	 * @tparam _T The type of the copy.
	 *
	 * @param _copy The object that should be copied.
	*/
	template<typename _T>
	explicit stl_allocator_wrapper(const stl_allocator_wrapper<_T> & _copy) noexcept : _allocator(_copy._allocator)
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
		_allocator->deallocate(allocator::cast_allocation<void>(allocator::allocation<_Ty>{ _ptr, _size * sizeof(_Ty) }));
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
		return static_cast<pointer>(_allocator->allocate(_size * sizeof(_Ty)).first);
	}

private:
	template<typename _T>
	friend class stl_allocator_wrapper;

	/** The underlying Bia allocator. */
	std::shared_ptr<allocator> _allocator;
};

}
}
}