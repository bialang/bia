#include "biaAllocator.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/mman.h>
#endif


namespace bia
{
namespace machine
{

void BiaAllocator::CommitReserveAllocate(universal_allocation p_allocation, size_t p_iSize)
{
}

void BiaAllocator::Deallocate(universal_allocation p_allocation, MEMORY_TYPE p_type)
{
	switch (p_type)
	{
	case MEMORY_TYPE::NORMAL:
		free(p_allocation.pAddress);

		break;
	case MEMORY_TYPE::EXECUTABLE_MEMORY:
#ifdef _WIN32
		VirtualFree(p_allocation.pAddress, 0, MEM_RELEASE);
#else
		munmap(p_allocation.pAddress, p_allocation.iSize);
#endif
		break;
	}
}

void BiaAllocator::DeallocateBlocks(universal_allocation p_allocation, MEMORY_TYPE p_type)
{
	switch (p_type)
	{
	case MEMORY_TYPE::NORMAL:
		free(p_allocation.pAddress);

		break;
	case MEMORY_TYPE::EXECUTABLE_MEMORY:
#ifdef _WIN32
		VirtualFree(p_allocation.pAddress, 0, MEM_RELEASE);
#else
		munmap(p_allocation.pAddress, p_allocation.iSize * BLOCK_SIZE);
#endif

		break;
	}
}

bool BiaAllocator::ChangeProtection(universal_allocation p_allocation, int p_fProtection)
{
#ifdef _WIN32
	//Protect memory
	DWORD oldProtect = 0;
	DWORD newProtect = 0;

	if (p_fProtection & P_READ_WRITE)
		newProtect |= PAGE_READWRITE;

	if (p_fProtection & P_EXECUTE)
		newProtect |= PAGE_EXECUTE;

	return VirtualProtect(p_allocation.pAddress, p_allocation.iSize, newProtect, &oldProtect);
#else
	int fProtection = 0;

	if (p_fProtection & P_READ_WRITE)
		fProtection |= PROT_READ | PROT_WRITE;

	if (p_fProtection & P_EXECUTE)
		fProtection |= PROT_EXEC;

	return mprotect(p_allocation.pAddress, p_allocation.iSize, PROT_EXEC) == 0;
#endif
}

BiaAllocator::universal_allocation BiaAllocator::Allocate(size_t p_iSize, MEMORY_TYPE p_type)
{
	switch (p_type)
	{
	case MEMORY_TYPE::NORMAL:
		return { malloc(p_iSize), p_iSize };
	case MEMORY_TYPE::EXECUTABLE_MEMORY:
	{
#ifdef _WIN32
		return { VirtualAlloc(nullptr, p_iSize, MEM_COMMIT, PAGE_READWRITE), p_iSize };
#else
		auto pAllocation = mmap(nullptr, p_iSize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (pAllocation != reinterpret_cast<void*>(-1))
			return { pAllocation, p_iSize };
#endif

		break;
	}
	}

	return { nullptr, 0 };
}

BiaAllocator::universal_allocation BiaAllocator::AllocateBlocks(size_t p_iBlockCount, MEMORY_TYPE p_type)
{
	return { Allocate(p_iBlockCount * BLOCK_SIZE, p_type).pAddress, p_iBlockCount };
}

BiaAllocator::universal_allocation BiaAllocator::ReserveAllocate(size_t p_iMaxSize, MEMORY_TYPE p_type)
{
	return Allocate(p_iMaxSize, p_type);

}

}
}