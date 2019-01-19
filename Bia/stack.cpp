#include "stack.hpp"
#include "undefined_member.hpp"
#include "max_member_size.hpp"


namespace bia
{
namespace machine
{

stack::stack(memory::allocator * _allocator, size_t _size)
{
	_buffer = memory::cast_allocation<int8_t>(_allocator->allocate(_size));
	this->_allocator = _allocator;
	_cursor = 0;
}

stack::stack(stack && _move) noexcept
{
	_allocator = _move._allocator;
	_buffer = std::move(_move._buffer);
	_cursor = _move._cursor;

	_move._cursor = 0;
}

stack::~stack()
{
	if (_buffer) {
		_allocator->deallocate(memory::cast_allocation<void>(_buffer));
	}
}

void stack::pop(uint32_t _member_count)
{
	if (_cursor < _member_count * framework::max_member_size) {
		throw 1;
	}

	_cursor -= _member_count * framework::max_member_size;

	auto _ptr = _buffer.first + _cursor;

	// Destroy members
	while (_member_count--) {
		reinterpret_cast<framework::member*>(_ptr)->~member();
		_ptr += framework::max_member_size;
	}
}

void stack::recreate(uint32_t _member_count)
{
	if (_cursor < _member_count * framework::max_member_size) {
		throw 1;
	}

	auto _ptr = _buffer.first + _cursor - _member_count * framework::max_member_size;

	// Recreate members
	while (_member_count--) {
		reinterpret_cast<framework::member*>(_ptr)->undefine();
		_ptr += framework::max_member_size;
	}
}

void stack::recreate_range(framework::member * _begin, uint32_t _member_count)
{
	if (!_member_count) {
		return;
	}

	auto _ptr = reinterpret_cast<int8_t*>(_begin);
	auto _check = _ptr - _buffer.first;

	if (_check < 0 || _check + _member_count > _cursor || _check % framework::max_member_size) {
		throw 1;
	}

	// Recreate members
	while (_member_count--) {
		reinterpret_cast<framework::member*>(_ptr)->undefine();
		_ptr += framework::max_member_size;
	}
}

void stack::push(framework::member ** _destination, uint32_t _member_count)
{
	auto _ptr = _buffer.first + _cursor;

	if (_cursor + _member_count * framework::max_member_size > _buffer.second) {
		throw 1;
	}

	_cursor += _member_count * framework::max_member_size;

	// Create members
	while (_member_count--) {
		*_destination = new(_ptr) framework::undefined_member();
		_ptr += framework::max_member_size;
	}
}

}
}