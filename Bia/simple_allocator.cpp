#include "simple_allocator.hpp"

#if defined(BIA_OS_WINDOWS)
#include <windows.h>
#elif defined(BIA_OS_LINUX)
#include <sys/mman.h>
#endif

#include <cstdlib>


namespace bia
{
namespace machine
{
namespace memory
{

void simple_allocator::commit_allocation(universal_allocation _allocation, size_t _size)
{
}

void simple_allocator::deallocate(universal_allocation _allocation, MEMORY_TYPE _type)
{
	switch (_type) {
	case MEMORY_TYPE::NORMAL:
		free(_allocation.address);

		break;
	case MEMORY_TYPE::EXECUTABLE_MEMORY:
#if defined(BIA_OS_WINDOWS)
		VirtualFree(_allocation.address, 0, MEM_RELEASE);
#elif defined(BIA_OS_LINUX)
		munmap(_allocation.address, _allocation.size);
#endif
		break;
	}
}

void simple_allocator::deallocate_blocks(universal_allocation _allocation, MEMORY_TYPE _type)
{
	switch (_type) {
	case MEMORY_TYPE::NORMAL:
		free(_allocation.address);

		break;
	case MEMORY_TYPE::EXECUTABLE_MEMORY:
#if defined(BIA_OS_WINDOWS)
		VirtualFree(_allocation.address, 0, MEM_RELEASE);
#elif defined(BIA_OS_LINUX)
		munmap(_allocation.address, _allocation.size * BLOCK_SIZE);
#endif

		break;
	}
}

void simple_allocator::change_protection(universal_allocation _allocation, int _protection)
{
#if defined(BIA_OS_WINDOWS)
	//Set protections flags
	DWORD _old = 0;
	DWORD _new = 0;

	if (_protection & P_READ_WRITE)
		_new |= PAGE_READWRITE;

	if (_protection & P_EXECUTE)
		_new |= PAGE_EXECUTE;

	VirtualProtect(_allocation.address, _allocation.size, _new, &_old);
#elif defined(BIA_OS_LINUX)
	int _new = 0;

	if (_protection & P_READ_WRITE)
		_new |= PROT_READ | PROT_WRITE;

	if (_protection & P_EXECUTE)
		_new |= PROT_EXEC;

	return mprotect(_allocation.address, _allocation.size, _new) == 0;
#endif
}

simple_allocator::universal_allocation simple_allocator::allocate(size_t _size, MEMORY_TYPE _type)
{
	switch (_type) {
	case MEMORY_TYPE::NORMAL:
		return { malloc(_size), _size };
	case MEMORY_TYPE::EXECUTABLE_MEMORY:
	{
#if defined(BIA_OS_WINDOWS)
		return { VirtualAlloc(nullptr, _size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE), _size };
#elif defined(BIA_OS_LINUX)
		auto _ptr = mmap(nullptr, _size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (_ptr != reinterpret_cast<void*>(-1))
			return { _ptr, _size };
#endif

		break;
	}
	}

	return { nullptr, 0 };
}

simple_allocator::universal_allocation simple_allocator::allocate_blocks(size_t _count, MEMORY_TYPE _type)
{
	return { allocate(_count * BLOCK_SIZE, _type).address, _count };
}

simple_allocator::universal_allocation simple_allocator::reserve_allocation(size_t _max_size, MEMORY_TYPE _type)
{
	return allocate(_max_size, _type);

}

}
}
}