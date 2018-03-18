#pragma once

#include <utility>

#include "biaConfig.hpp"

#define BIA_MAX_MEMBER_SIZE 50


namespace bia
{
namespace machine
{

class BiaAllocator
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

	template<typename T>
	struct Allocation
	{
		T * pAddress;
		size_t iSize;
	};

	typedef Allocation<void> universal_allocation;

	constexpr static auto BLOCK_SIZE = BIA_MAX_MEMBER_SIZE;


	virtual ~BiaAllocator() = default;

	virtual void CommitReserveAllocate(universal_allocation p_allocation, size_t p_iSize);
	virtual void Deallocate(universal_allocation p_allocation, MEMORY_TYPE p_type);
	virtual void DeallocateBlocks(universal_allocation p_allocation, MEMORY_TYPE p_type);
	template<typename T>
	inline void DestroyBlocks(Allocation<T> p_allocation, MEMORY_TYPE p_type)
	{
		auto pBlocks = reinterpret_cast<int8_t*>(p_allocation.pAddress);
		auto iBlockCount = p_allocation.iSize;

		for (size_t i = 0; i < iBlockCount; ++i)
			reinterpret_cast<T*>(pBlocks + i * BLOCK_SIZE)->~T();

		DeallocateBlocks({ static_cast<void*>(p_allocation.pAddress), p_allocation.iSize }, p_type);
	}
	virtual bool ChangeProtection(universal_allocation p_allocation, int p_fProtection);
	virtual universal_allocation Allocate(size_t p_iSize, MEMORY_TYPE p_type);
	virtual universal_allocation AllocateBlocks(size_t p_iBlockCount, MEMORY_TYPE p_type);
	virtual universal_allocation ReserveAllocate(size_t p_iMaxSize, MEMORY_TYPE p_type);
	template<typename T>
	inline static universal_allocation ToUniversalAllocation(Allocation<T> p_allocation)
	{
		return { p_allocation.pAddress, p_allocation.iSize };
	}
	template<typename _BASE, typename _DERIVIATE = _BASE, typename... _ARGS>
	inline Allocation<_BASE> ConstructBlocks(size_t p_iBlockCount, MEMORY_TYPE p_type, _ARGS &&... p_args)
	{
		static_assert(sizeof(_DERIVIATE) <= BLOCK_SIZE, "Type exceeds block size.");

		auto allocation = AllocateBlocks(p_iBlockCount, p_type);
		auto pBlocks = static_cast<int8_t*>(allocation.pAddress);

		for (size_t i = 0; i < p_iBlockCount; ++i)
			new(pBlocks + i * BLOCK_SIZE) _DERIVIATE(std::forward<_ARGS>(p_args)...);

		return { static_cast<_BASE*>(allocation.pAddress), allocation.iSize };
	}
};

}
}