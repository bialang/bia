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

void simple_allocator::block_allocator<framework::max_member_size>::deallocate_block(universal_allocation _block)
{
	deallocate(_block);
}

void simple_allocator::block_allocator<sizeof(dependency::big_int)>::deallocate_block(universal_allocation _block)
{
	deallocate(_block);
}

universal_allocation simple_allocator::reallocate(universal_allocation _allocation, size_type _size)
{
	auto _ptr = std::realloc(_allocation.first, _size);

	if (!_ptr) {
		throw exception::memory_error(BIA_EM_FAILED_ALLOCATION);
	}

	return { _ptr, _size };
}

universal_allocation simple_allocator::commit(universal_allocation _allocation, size_type _size)
{
	return _allocation;
}

universal_allocation simple_allocator::allocate(size_type _size)
{
	auto _ptr = std::malloc(_size);
	//printf("allocated %zi bytes at %p\n", _size, _ptr);
	if (!_ptr) {
		throw exception::memory_error(BIA_EM_FAILED_ALLOCATION);
	}

	return { _ptr, _size };
}

universal_allocation simple_allocator::block_allocator<framework::max_member_size>::allocate_block()
{
	return allocate(framework::max_member_size);
}

universal_allocation simple_allocator::block_allocator<sizeof(dependency::big_int)>::allocate_block()
{
	return allocate(sizeof(dependency::big_int));
}

universal_allocation simple_allocator::prepare(size_type _size)
{
	return allocate(_size);
}

}
}
}