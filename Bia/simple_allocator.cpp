#include "simple_allocator.hpp"
#include "exception.hpp"

#include <cstdlib>


namespace bia
{
namespace machine
{
namespace memory
{

void simple_allocator::deallocate(universal_allocation _allocation)
{
	//printf("free %zi bytes at %p\n", _allocation.second, _allocation.first);
	std::free(_allocation.first);
}

void simple_allocator::deallocate_blocks(universal_allocation _blocks)
{
	deallocate(_blocks);
}

simple_allocator::universal_allocation simple_allocator::reallocate(universal_allocation _allocation, size_type _size)
{
	auto _ptr = std::realloc(_allocation.first, _size);

	if (!_ptr) {
		throw exception::memory_error(BIA_EM_FAILED_ALLOCATION);
	}

	return { _ptr, _size };
}

simple_allocator::universal_allocation simple_allocator::commit(universal_allocation _allocation, size_type _size)
{
	return _allocation;
}

simple_allocator::universal_allocation simple_allocator::allocate(size_type _size)
{
	auto _ptr = std::malloc(_size);
	//printf("allocated %zi bytes at %p\n", _size, _ptr);
	if (!_ptr) {
		throw exception::memory_error(BIA_EM_FAILED_ALLOCATION);
	}

	return { _ptr, _size };
}

simple_allocator::universal_allocation simple_allocator::allocate_blocks(size_type _count)
{
	return { allocate(block_size() * _count).first, _count };
}

simple_allocator::universal_allocation simple_allocator::prepare(size_type _size)
{
	return allocate(_size);
}

}
}
}