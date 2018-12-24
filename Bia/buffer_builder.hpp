#pragma once

#include <cstdint>
#include <cstring>

#include "allocator.hpp"


namespace bia
{
namespace utility
{

class buffer_builder
{
public:
	typedef machine::memory::size_type size_type;

	buffer_builder(machine::memory::allocator * _allocator) : _allocator(_allocator)
	{
		_buffer = _allocator->allocate(32);
		_size = 0;
	}
	buffer_builder(const buffer_builder & _copy) = delete;
	buffer_builder(buffer_builder && _copy) = default;
	~buffer_builder()
	{
		if (_buffer) {
			_allocator->deallocate(_buffer);
		}
	}
	void resize(size_type _new_size)
	{
		if (_new_size > capacity()) {
			auto _new = _allocator->allocate(_new_size + 16);

			std::memcpy(_new, _buffer, _size);

			_allocator->deallocate(_buffer);

			_buffer = _new;
		}

		_size = _new_size;
	}
	size_type capacity() const noexcept
	{
		return _buffer.second;
	}
	size_type size() const noexcept
	{
		return _size;
	}
	template<typename Type = void>
	Type * buffer() noexcept
	{
		return reinterpret_cast<Type*>(_buffer.first);
	}
	template<typename Type = void>
	const Type * buffer() const noexcept
	{
		return reinterpret_cast<const Type*>(_buffer.first);
	}

private:
	machine::memory::allocator * _allocator;
	machine::memory::universal_allocation _buffer;
	size_type _size;
};

}
}