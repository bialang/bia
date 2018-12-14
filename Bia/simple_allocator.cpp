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

void simple_allocator::deallocate_member(allocation<framework::member> _allocation)
{
	deallocate(cast_allocation<void>(_allocation));
}

void simple_allocator::deallocate_big_int(big_int_allocation _allocation)
{
	deallocate(cast_allocation<void>(_allocation));
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

allocation<framework::member> simple_allocator::allocate_member()
{
	return cast_allocation<framework::member>(allocate(member_allocation_size));
}

big_int_allocation simple_allocator::allocate_big_int()
{
	return cast_allocation<dependency::big_int>(allocate(big_int_allocation_size));
}

universal_allocation simple_allocator::prepare(size_type _size)
{
	return allocate(_size);
}

}
}
}