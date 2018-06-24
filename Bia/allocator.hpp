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
	typedef size_t size_type;
	/** An allocation with type. */
	template<typename _Ty>
	using allocation = std::pair<_Ty*, size_type>;
	/** An universal allocation. */
	typedef allocation<void> universal_allocation;

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
		_allocation.first->~_Deriviate();

		deallocate(cast_allocation<void>(_allocation));
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
		auto _block_size = get_block_size();

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
	size_t get_block_size() const noexcept;
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
	 * Casts an allocation to an @ref universal_allocation.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @tparam _Return The wanted type.
	 * @tparam _Ty The passed type.
	 *
	 * @param _allocaiton Defines the allocation.
	 *
	 * @return The @ref universal_allocation.
	*/
	template<typename _Return, typename _Ty>
	static allocation<_Return> cast_allocation(allocation<_Ty> _allocation) noexcept
	{
		return { static_cast<_Return*>(_allocation.first), _allocation.second };
	}
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
		auto _block_size = get_block_size();

		if (sizeof(_Deriviate) > _block_size) {
			BIA_COMPILER_DEV_INVALID("Elements exceeds block size.");
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