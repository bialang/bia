#pragma once

#include <cstddef>

#include "config.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

class allocator
{
public:
	enum class MEMORY_TYPE
	{
		NORMAL,
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
		_Ty* address;
		size_t size;
	};

	typedef allocation<void> universal_allocation;

	constexpr static auto BLOCK_SIZE = BIA_MAX_MEMBER_SIZE;


	virtual ~allocator() = default;
	virtual void commit_allocation(universal_allocation _allocation, size_t _size) = 0;
	virtual void deallocate(universal_allocation _allocation, MEMORY_TYPE _type) = 0;
	virtual void deallocate_blocks(universal_allocation _allocation, MEMORY_TYPE _type) = 0;
	template<typename _Ty>
	void destroy_blocks(allocation<_Ty> _allocation, MEMORY_TYPE _type)
	{
		auto ptr = reinterpret_cast<int8_t*>(_allocation.address);

		//Destroy all elements
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
	 * Casts an allocation to an universal_allocation
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	allocaiton	Defines the allocation.
	 *
	 * @return	The universal_allocation.
	*/
	template<typename _Return, typename _Ty>
	static allocation<_Return> cast_allocation(allocation<_Ty> _allocation) noexcept
	{
		return { static_cast<_Return*>(_allocation.address), _allocation.size };
	}
	template<typename _Base, typename _Deriviate = _Base, typename... _Args>
	allocation<_Base> construct_blocks(size_t _count, MEMORY_TYPE _type, _Args&&... _args)
	{
		static_assert(sizeof(_Deriviate) <= BLOCK_SIZE, "Type exceeds block size.");

		auto allocation = allocate_blocks(_count, _type);
		auto ptr = static_cast<int8_t*>(allocation.address);

		//Construct all elements
		for (size_t i = 0; i < _count; ++i) {
			new(ptr + i * BLOCK_SIZE) _Deriviate(std::forward<_Args>(_args)...);
		}

		return cast_allocation<_Base>(allocation);
	}
};

}
}
}