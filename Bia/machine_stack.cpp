#include "machine_stack.hpp"
#include "undefined_member.hpp"


namespace bia
{
namespace machine
{

machine_stack::machine_stack(memory::allocator * _allocator, size_t _size)
{
	this->_allocator = _allocator;
	

	auto _allocation = _allocator->allocate(_size);

	_buffer = static_cast<int8_t*>(_allocation.first);
	_max_size = _allocation.second;
	_cursor = 0;
}

machine_stack::~machine_stack()
{
	_allocator->deallocate(memory::allocator::universal_allocation(_buffer, _max_size));
}

void machine_stack::pop(uint32_t _member_count, uint32_t _address_count)
{
	auto _member_size = memory::allocator::get_block_size();

	if (_cursor < _member_count * _member_size + _address_count * sizeof(void*)) {
		throw 1;
	}

	_cursor -= _member_count * _member_size + _address_count * sizeof(void*);

	auto _ptr = _buffer + _cursor;

	// Destroy members
	while (_member_count--) {
		reinterpret_cast<framework::member*>(_ptr)->~member();
		_ptr += _member_size;
	}
}

void * machine_stack::push(uint32_t _member_count, uint32_t _address_count)
{
	auto _ptr = _buffer + _cursor;
	const auto _begin = _ptr;
	auto _member_size = memory::allocator::get_block_size();

	if (_cursor + _member_count * _member_size + _address_count * sizeof(void*) > _max_size) {
		throw 1;
	}

	_cursor += _member_count * _member_size + _address_count * sizeof(void*);

	// Create members
	while (_member_count--) {
		new(_ptr) framework::undefined_member();
		_ptr += _member_size;
	}

	return _begin;
}

}
}