#pragma once

#include <cstddef>
#include <utility>
#include <cstdint>

#include "config.hpp"
#include "exception.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

typedef size_t size_type;

/** An allocation with type. */
template<typename _Ty>
class allocation
{
public:
	_Ty * first;
	size_type second;

	allocation() noexcept
	{
		clear();
	}
	allocation(_Ty * _first, size_type _second) noexcept
	{
		first = _first;
		second = _second;
	}
	allocation(const allocation<_Ty> & _copy) noexcept = default;
	allocation(allocation<_Ty> && _move) noexcept
	{
		first = _move.first;
		second = _move.second;

		_move.clear();
	}
	void clear() noexcept
	{
		first = nullptr;
		second = 0;
	}
	operator bool() const noexcept
	{
		return first != nullptr;
	}
	operator _Ty*() noexcept
	{
		return first;
	}
	operator const _Ty*() const noexcept
	{
		return first;
	}
	_Ty * operator->() noexcept
	{
		return first;
	}
	const _Ty * operator->() const noexcept
	{
		return first;
	}
	_Ty ** operator&() noexcept
	{
		return &first;
	}
	_Ty * const* operator&() const noexcept
	{
		return &first;
	}
	allocation & operator=(const allocation<_Ty> & _copy) noexcept = default;
	allocation & operator=(allocation && _move) noexcept
	{
		first = _move.first;
		second = _move.second;

		_move.clear();

		return *this;
	}
};

/** An universal allocation. */
typedef allocation<void> universal_allocation;


/**
 * Casts an allocation to the defined type.
 *
 * @since 3.64.127.716
 * @date 7-Apr-18
 *
 * @tparam _Return The wanted type.
 * @tparam _Ty The passed type.
 *
 * @param _allocation Defines the allocation.
 *
 * @return The cast allocation.
*/
template<typename _Return, typename _Ty>
inline allocation<_Return> cast_allocation(allocation<_Ty> _allocation) noexcept
{
	return { static_cast<_Return*>(_allocation.first), _allocation.second };
}

/**
 * @brief An allocator interface.
 *
 * An interface for allocating memory.
 *
 * @see @ref simple_allocator
*/
class allocator
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~allocator() noexcept = default;
	/**
	 * Destroys and deallocates the element created by construct().
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam _Base The returned type.
	 * @tparam _Deriviate The constructed type.
	 *
	 * @param _allocation The allocation.
	 *
	 * @throws See deallocate().
	 * @throws See the destructor of @a _Deriviate.
	*/
	template<typename _Base, typename _Deriviate = _Base>
	void destroy(allocation<_Base> _allocation)
	{
		// Destroy element
		if (_allocation) {
			_allocation.first->~_Deriviate();

			deallocate(cast_allocation<void>(_allocation));
		}
	}
	/**
	 * Destroys and deallocates the blocks created by allocate_blocks().
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam _Ty The allocation type.
	 *
	 * @param _allocation The allocation.
	 *
	 * @throws See deallocate_blocks().
	 * @throws See the destructor of @a _Ty.
	*/
	template<typename _Ty>
	void destroy_blocks(allocation<_Ty> _allocation)
	{
		auto _ptr = reinterpret_cast<int8_t*>(_allocation.first);
		auto _block_size = block_size();

		// Destroy all elements
		for (size_type i = 0; i < _allocation.second; ++i) {
			reinterpret_cast<_Ty*>(_ptr + i * _block_size)->~_Ty();
		}

		deallocate_blocks(cast_allocation<void>(_allocation));
	}
	/**
	 * Deallocates the allocation allocated by allocate().
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocation The allocation.
	 *
	 * @throws exception::memory_error If the specified allocation is invalid.
	*/
	virtual void deallocate(universal_allocation _allocation) = 0;
	/**
	 * Deallocates the blocks allocated by allocate_blocks().
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _blocks The allocation.
	 *
	 * @throws exception::memory_error If the specified allocation is invalid.
	*/
	virtual void deallocate_blocks(universal_allocation _blocks) = 0;
	/**
	 * Returns the required block size.
	 *
	 * @since 3.64.132.731
	 * @date 28-Jun-18
	 *
	 * @return The block size.
	*/
	BIA_EXPORT static size_t block_size() noexcept;
	/**
	 * Can be used to expand or shrinken an allocation.
	 *
	 * @remarks If a new memory is allocated, the data will be copied.
	 *
	 * @since 3.65.134.742
	 * @date 2-Aug-18
	 *
	 * @param _allocation The allocation that should be expanded or shrinken.
	 * @param _size The new size.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The reallocated allocation.
	*/
	virtual universal_allocation reallocate(universal_allocation _allocation, size_type _size) = 0;
	/**
	 * Commits the memory reserved by prepare().
	 *
	 * @remarks The returned allocation can have the same size as @a _allocation.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _allocation The allocation.
	 * @param _size The final size of the allocation.
	 *
	 * @throws exception::memory_error If the specified allocation or the size are invalid.
	 *
	 * @return The allocation with possibly adapted size parameter.
	*/
	virtual universal_allocation commit(universal_allocation _allocation, size_type _size) = 0;
	/**
	 * Allocates memory.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _size The size of the allocation in bytes.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The allocation.
	*/
	virtual universal_allocation allocate(size_type _size) = 0;
	/**
	 * Allocates the specified amount of blocks.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _count The amount of the blocks.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The blocks.
	*/
	virtual universal_allocation allocate_blocks(size_type _count) = 0;
	/**
	 * Prepares memory if the actual size can be smaller.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _size The maximum size of the allocation.
	 *
	 * @throws exception::memory_error If the memory could not be allocated.
	 *
	 * @return The allocation.
	 *
	 * @see For commiting the actual size use commit().
	*/
	virtual universal_allocation prepare(size_type _size) = 0;
	/**
	 * Allocates and constructs the desired type.
	 *
	 * @remarks @a _Deriviate must inherit @a _Base.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam _Base The returned type.
	 * @tparam _Deriviate The constructed type.
	 * @tparam _Args The arguments that will be used to construct the element.
	 *
	 * @param _args The arguments used to create the element.
	 *
	 * @throws See allocate().
	 * @throws See the constructor of @a _Deriviate.
	 *
	 * @return The allocated and constructed block.
	*/
	template<typename _Base, typename _Deriviate = _Base, typename... _Args>
	allocation<_Base> construct(_Args &&... _args)
	{
		auto _allocation = allocate(sizeof(_Deriviate));

		// Construct element
		new(_allocation.first) _Deriviate(std::forward<_Args>(_args)...);

		return cast_allocation<_Base>(_allocation);
	}
	/**
	 * Allocates and constructs blocks of the desired type.
	 *
	 * @remarks @a _Deriviate must inherit @a _Base and must be smaller than @ref block_size.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam _Base The returned type.
	 * @tparam _Deriviate The constructed type.
	 * @tparam _Args The arguments that will be used to construct the blocks.
	 *
	 * @param _count How many blocks should be constructed.
	 * @param _args The arguments used to create the blocks.
	 *
	 * @throws See allocate_blocks().
	 * @throws See the constructor of @a _Deriviate.
	 *
	 * @return The allocated blocks.
	*/
	template<typename _Base, typename _Deriviate = _Base, typename... _Args>
	allocation<_Base> construct_blocks(size_type _count, _Args &&... _args)
	{
		auto _block_size = block_size();

		if (sizeof(_Deriviate) > _block_size) {
			throw BIA_IMPLEMENTATION_EXCEPTION("Elements exceeds block size.");
		}

		auto _allocation = allocate_blocks(_count);
		auto _ptr = static_cast<int8_t*>(_allocation.first);

		// Construct all elements
		for (size_type i = 0; i < _count; ++i) {
			new(_ptr + i * _block_size) _Deriviate(std::forward<_Args>(_args)...);
		}

		return cast_allocation<_Base>(_allocation);
	}

};

}
}
}