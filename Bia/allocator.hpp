#pragma once

#include <cstddef>

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
 * An interface for allocation executable and 'normal' memory.
 *
 * @see @ref simple_allocator
*/
class allocator
{
public:
	enum class MEMORY_TYPE
	{
		/** 'Normal' memory just needs to be read-write memory. */
		NORMAL,
		/** Memory which is read-only and can be executed. */
		EXECUTABLE_MEMORY
	};

	enum PROTECTION
	{
		P_READ_WRITE = 0x1,
		P_EXECUTE = 0x2
	};

	template<typename _Ty>
	struct allocation
	{
		/** The allocated memory address. */
		_Ty * address;
		/** The size of the buffer or the count of the blocks. */
		size_t size;
	};

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
	virtual void commit_allocation(universal_allocation _allocation, size_t _size) = 0;
	virtual void deallocate(universal_allocation _allocation, MEMORY_TYPE _type) = 0;
	virtual void deallocate_blocks(universal_allocation _allocation, MEMORY_TYPE _type) = 0;
	template<typename _Ty>
	void destroy_blocks(allocation<_Ty> _allocation, MEMORY_TYPE _type)
	{
		auto ptr = reinterpret_cast<int8_t*>(_allocation.address);

		// Destroy all elements
		for (size_t i = 0; i < _allocation.size; ++i) {
			reinterpret_cast<_Ty*>(ptr + i * BLOCK_SIZE)->~_Ty();
		}

		deallocate_blocks(cast_allocation<void>(_allocation), _type);
	}
	virtual void change_protection(universal_allocation _allocation, int _protection) = 0;
	virtual universal_allocation allocate(size_t _size, MEMORY_TYPE _type) = 0;
	virtual universal_allocation allocate_blocks(size_t _count, MEMORY_TYPE _type) = 0;
	virtual universal_allocation reserve_allocation(size_t _max_size, MEMORY_TYPE _type) = 0;
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
		return { static_cast<_Return*>(_allocation.address), _allocation.size };
	}
	/**
	 * Constructs blocks of the desired type.
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
	 *
	 * @return The allocated blocks.
	*/
	template<typename _Base, typename _Deriviate = _Base, typename... _Args>
	allocation<_Base> construct_blocks(size_t _count, MEMORY_TYPE _type, _Args&&... _args)
	{
		static_assert(sizeof(_Deriviate) <= block_size, "Type exceeds block size.");

		auto allocation = allocate_blocks(_count, _type);
		auto ptr = static_cast<int8_t*>(allocation.address);

		// Construct all elements
		for (size_t i = 0; i < _count; ++i) {
			new(ptr + i * block_size) _Deriviate(std::forward<_Args>(_args)...);
		}

		return cast_allocation<_Base>(allocation);
	}
};

}
}
}