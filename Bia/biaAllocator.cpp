#include "biaAllocator.hpp"


namespace bia
{
namespace machine
{

void BiaAllocator::CommitReserveAllocate(void * p_pAddress, size_t p_iSize)
{
}

void BiaAllocator::Deallocate(void * p_pAddress)
{
	free(p_pAddress);
}

void BiaAllocator::DeallocateBlocks(void * p_pBlockBegin, size_t p_iBlockCount)
{
	free(p_pBlockBegin);
}

void * BiaAllocator::Allocate(size_t p_iSize, int p_fOptions)
{
	return malloc(p_iSize);
}

void * BiaAllocator::AllocateBlocks(size_t p_iBlockCount, int p_fOptions)
{
	return malloc(p_iBlockCount * BLOCK_SIZE);
}

void * BiaAllocator::ReserveAllocate(size_t p_iMaxSize, int p_fOptions)
{
	return malloc(p_iMaxSize);
}

}
}