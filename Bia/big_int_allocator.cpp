#include "big_int_allocator.hpp"

#include <mpir/mpir.h>
#include <cstring>


namespace bia
{
namespace machine
{
namespace memory
{

std::shared_ptr<block_allocator<sizeof(dependency::big_int)>> big_int_allocator::_allocator;

void big_int_allocator::initialize(const std::shared_ptr<block_allocator<sizeof(dependency::big_int)>>& _allocator)
{
	big_int_allocator::_allocator = _allocator;

	// Set allocation functions
	mp_set_memory_functions(&big_int_allocator::allocate, &big_int_allocator::reallocate, &big_int_allocator::free);
}

void big_int_allocator::free_int(int_type _int)
{
	_allocator->destroy_block(_int);
}

big_int_allocator::int_type big_int_allocator::new_int()
{
	return _allocator->construct_block<dependency::big_int>();
}

void big_int_allocator::free(void * _ptr, size_t _size)
{
	// Free if memory is not provieded by big_int
	if (_size != dependency::big_int::reserved_space) {
		_allocator->deallocate({ _ptr, _size });
	}
}

void * big_int_allocator::allocate(size_t _size)
{
	return _allocator->allocate(_size);
}

void * big_int_allocator::reallocate(void * _buffer, size_t _old_size, size_t _new_size)
{
	if (_old_size == _new_size) {
		return _buffer;
	}

	// Memory is provided by big_int
	if (_old_size == dependency::big_int::reserved_space) {
		// Copy buffer to new location
		auto _new = allocate(_new_size);

		std::memcpy(_new, _buffer, _old_size);

		return _new;
	}

	return _allocator->reallocate({ _buffer, _old_size }, _new_size);
}

}
}
}