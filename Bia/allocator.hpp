#pragma once

#include <cstddef>
#include <utility>
#include <cstdint>

#include "config.hpp"


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
	/** An allocation with type. */
	template<typename _Ty>
	using allocation = std::pair<_Ty*, size_t>;
	/** An universal allocation. */
	typedef allocation<void> universal_allocation;

	/** The size of a block. Cannot be changed. */
	constexpr static auto block_size = BIA_MAX_MEMBER_SIZE;

	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~allocator() noexcept = default;
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

		// Destroy all elements
		for (size_t i = 0; i < _allocation.second; ++i) {
			reinterpret_cast<_Ty*>(_ptr + i * block_size)->~_Ty();
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
	virtual universal_allocation commit(universal_allocation _allocation, size_t _size) = 0;
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
	virtual universal_allocation allocate(size_t _size) = 0;
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
	virtual universal_allocation allocate_blocks(size_t _count) = 0;
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
	virtual universal_allocation prepare(size_t _size) = 0;
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
	 * @param _type The type of the memory.
	 * @param _args The arguments used to create the blocks.
	 *
	 * @throws See allocate_blocks().
	 * @throws See the constructor of @a _Deriviate.
	 *
	 * @return The allocated blocks.
	*/
	template<typename _Base, typename _Deriviate = _Base, typename... _Args>
	allocation<_Base> construct_blocks(size_t _count, _Args &&... _args)
	{
		static_assert(sizeof(_Deriviate) <= block_size, "Type exceeds block size.");

		auto _allocation = allocate_blocks(_count);
		auto _ptr = static_cast<int8_t*>(_allocation.first);

		// Construct all elements
		for (size_t i = 0; i < _count; ++i) {
			new(_ptr + i * block_size) _Deriviate(std::forward<_Args>(_args)...);
		}

		return cast_allocation<_Base>(_allocation);
	}
};

}
}
}