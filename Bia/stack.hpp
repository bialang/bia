#pragma once

#include <cstdint>

#include "config.hpp"
#include "allocator.hpp"
#include "exception.hpp"


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
	typedef intptr_t element_t;

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
		return reinterpret_cast<Type>(_stack_pointer + _offset);
	}
	template<typename Type>
	Type format_cast(ptrdiff_t _offset, char _format)
	{
		BIA_NOT_IMPLEMENTED;
		/*using namespace utility;
		using Real_return = typename std::remove_reference<Type>::type;

	gt_redo:;

		switch (_format) {
		case 'i':
		{
			constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

			if (is_number) {
				return chooser<is_number, Type, int32_t>::choose(va_arg(_args.args, int32_t));
			} else {
				break;
			}
		}
		case 'I':
		{
			constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

			if (is_number) {
				return chooser<is_number, Type, int64_t>().choose(va_arg(_args.args, int64_t));
			} else {
				break;
			}
		}
		case 'd':
		{
			constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

			if (is_number) {
				auto _value = va_arg(_args.args, int64_t);

				return chooser<is_number, Type, double>().choose(*reinterpret_cast<double*>(&_value));
			} else {
				break;
			}
		}
		case 'a':
		{
			constexpr auto is_string = std::is_same<Real_return, const char*>::value;

			if (is_string) {
				return chooser<is_string, Type, const char*>().choose(va_arg(_args.args, const char*));
			} else {
				break;
			}
		}
		case 'M':
			return reinterpret_cast<framework::member*>(_stack_pointer)->cast<Return>();
		case 'r':
			va_arg(_args.args, void*);

			goto gt_redo;
		default:
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
		}

		throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);*/
	}

private:
	/** The base pointer of the stack. */
	intptr_t * _base_pointer;
	/** The stack pointer of the stack. */
	intptr_t * _stack_pointer;
	/** The used memory allocator. */
	memory::allocator * _allocator;
	/** The base pointer of the stack. */
	memory::allocation<element_t> _buffer;
};

}
}