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

simple_allocator::universal_allocation simple_allocator::commit(universal_allocation _allocation, size_t _size)
{
	return _allocation;
}

simple_allocator::universal_allocation simple_allocator::allocate(size_t _size)
{
	auto _ptr = std::malloc(_size);
	//printf("allocated %zi bytes at %p\n", _size, _ptr);
	if (!_ptr) {
		throw exception::memory_error(BIA_EM_FAILED_ALLOCATION);
	}

	return { _ptr, _size };
}

simple_allocator::universal_allocation simple_allocator::allocate_blocks(size_t _count)
{
	return { allocate(get_block_size() * _count).first, _count };
}

simple_allocator::universal_allocation simple_allocator::prepare(size_t _size)
{
	return allocate(_size);
}

}
}
}