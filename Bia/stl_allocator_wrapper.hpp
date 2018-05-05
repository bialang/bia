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
	void deallocate(_Ty * _ptr, size_t _size)
	{
		_allocator->deallocate(allocator::cast_allocation<void>(allocator::allocation<_Ty>{ _ptr, _size }));
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
	_Ty * allocate(size_t _size)
	{
		return _allocator->allocate(_size).first;
	}
	/**
	 * Compares two allocators for equality.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _right The right operand.
	 *
	 * @return true if they both have the same underlying Bia allocator, otherwise false.
	*/
	bool operator==(const stl_allocator_wrapper & _right) const noexcept
	{
		return _allocator.get() == _right._allocator.get();
	}
	/**
	 * Compares two allocators for inequality.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _right The right operand.
	 *
	 * @return true if they both have the different underlying Bia allocator, otherwise false.
	*/
	bool operator!=(const stl_allocator_wrapper & _right) const noexcept
	{
		return _allocator.get() != _right._allocator.get();
	}


private:
	/** The underlying Bia allocator. */
	std::shared_ptr<allocator> _allocator;
};

}
}
}