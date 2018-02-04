#pragma once

#include <utility>

#define BIA_MAX_MEMBER_SIZE 50


namespace bia
{
namespace machine
{

class BiaAllocator
{
public:
	enum FLAGS
	{
		F_NONE = 0
	};

	constexpr static auto BLOCK_SIZE = BIA_MAX_MEMBER_SIZE;


	virtual ~BiaAllocator() = default;

	virtual void CommitReserveAllocate(void * p_pAddress, size_t p_iSize);
	virtual void Deallocate(void * p_pAddress);
	virtual void DeallocateBlocks(void * p_pBlockBegin, size_t p_iBlockCount);
	template<typename T>
	inline void DestroyBlocks(T * p_pInstance, size_t p_iBlockCount)
	{
		auto pBlocks = reinterpret_cast<int8_t*>(p_pInstance);

		for (size_t i = 0; i < p_iBlockCount; ++i)
			reinterpret_cast<T*>(pBlocks + i * BLOCK_SIZE)->~T();

		DeallocateBlocks(p_pInstance, p_iBlockCount);
	}
	virtual void * Allocate(size_t p_iSize, int p_fOptions = F_NONE);
	virtual void * AllocateBlocks(size_t p_iBlockCount, int p_fOptions = F_NONE);
	virtual void * ReserveAllocate(size_t p_iMaxSize, int p_fOptions = F_NONE);
	template<typename T, typename... _ARGS>
	inline T * ConstructBlocks(size_t p_iBlockCount, int p_fOptions, _ARGS &&... p_args)
	{
		auto pBlocks = static_cast<int8_t*>(AllocateBlocks(p_iBlockCount, p_fOptions));

		for (size_t i = 0; i < p_iBlockCount; ++i)
			new(pBlocks + i * BLOCK_SIZE) T(std::forward<_ARGS>(p_args)...);

		return reinterpret_cast<T*>(pBlocks);
	}
};

}
}