#pragma once

#include <cstdint>
#include <type_traits>

#include "config.hpp"
#include "allocator.hpp"
#include "exception.hpp"
#include "member.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief A simple stack.
 *
 * A simple stack used by the generated (virtual/real) machine code.
 *
 * @see @ref machine_context
*/
class stack
{
public:
	typedef int64_t element_t;
	typedef ptrdiff_t index_t;

	stack(memory::allocator * _allocator, size_t _element_count)
	{
		this->_allocator = _allocator;
		_buffer = memory::cast_allocation<element_t>(_allocator->allocate(_element_count * element_size()));
		_base_pointer = _buffer.first;
		_stack_pointer = _base_pointer;
	}
	stack(const stack & _copy) = delete;
	stack(stack && _move) noexcept
	{
		_allocator = _move._allocator;
		_buffer = std::move(_move._buffer);
		_base_pointer = _move._base_pointer;
		_stack_pointer = _move._stack_pointer;

		_move._allocator = nullptr;
		_move._base_pointer = nullptr;
		_move._stack_pointer = nullptr;
	}
	~stack()
	{
		if (_buffer) {
			_allocator->deallocate(memory::cast_allocation<void>(_buffer));
		}
	}
	template<typename Type>
	void push(Type _value)
	{
		static_assert(sizeof(Type) <= element_size(), "Size of Type must be less than the element size.");

		if (_stack_pointer + 1 > _buffer.first + _buffer.second) {
			BIA_IMPLEMENTATION_ERROR;
		}

		*reinterpret_cast<Type*>(_stack_pointer++) = _value;
	}
	template<typename Type>
	void push(Type * _value)
	{
		push(reinterpret_cast<intptr_t>(_value));
	}
	void push_count(size_t _count)
	{
		if (_stack_pointer + _count > _buffer.first + _buffer.second) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_stack_pointer += _count;
	}
	void pop_count(size_t _count)
	{
		if (_stack_pointer - _count < _base_pointer) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_stack_pointer -= _count;
	}
	size_t size() const noexcept
	{
		return _stack_pointer - _base_pointer;
	}
	constexpr static size_t element_size() noexcept
	{
		return sizeof(element_t);
	}
	template<typename Type>
	Type cast(ptrdiff_t _offset) noexcept
	{
		return *reinterpret_cast<Type*>(_stack_pointer + _offset);
	}
	template<typename Type>
	Type format_cast(ptrdiff_t _offset, char _format)
	{
		using namespace utility;
		using Real_return = typename std::remove_reference<Type>::type;

		switch (_format) {
		case 'i':
			return checked_convert<Type>(cast<int32_t>(_offset));
		case 'I':
			return checked_convert<Type>(cast<int64_t>(_offset));
		case 'd':
			return checked_convert<Type>(cast<double>(_offset));
		case 'a':
			return checked_convert<Type>(reinterpret_cast<const char*>(_stack_pointer + _offset));
		case 'M':
			return reinterpret_cast<framework::member*>(cast<intptr_t>(_offset))->cast<Type>();
		default:
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
		}

		throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
	}

private:
	/** The base pointer of the stack. */
	element_t * _base_pointer;
	/** The stack pointer of the stack. */
	element_t * _stack_pointer;
	/** The used memory allocator. */
	memory::allocator * _allocator;
	/** The base pointer of the stack. */
	memory::allocation<element_t> _buffer;

	template<typename To, typename From>
	static typename std::enable_if<std::is_convertible<From, To>::value, To>::type checked_convert(From _from)
	{
		return static_cast<To>(_from);
	}
	template<typename To, typename From>
	static typename std::enable_if<!std::is_convertible<From, To>::value, To>::type checked_convert(From _from)
	{
		throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
	}
};

}
}