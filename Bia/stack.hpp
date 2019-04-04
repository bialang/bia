#pragma once

#include <cstdint>
#include <type_traits>

#include "config.hpp"
#include "allocator.hpp"
#include "exception.hpp"
#include "member.hpp"
#include "type_traits.hpp"
#include "variant.hpp"


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
		_top_pointer = _base_pointer + _element_count;
	}
	stack(const stack & _copy) = delete;
	stack(stack && _move) noexcept
	{
		_base_pointer = _move._base_pointer;
		_stack_pointer = _move._stack_pointer;
		_top_pointer = _move._top_pointer;
		_allocator = _move._allocator;
		_buffer = std::move(_move._buffer);

		_move._base_pointer = nullptr;
		_move._stack_pointer = nullptr;
		_move._top_pointer = nullptr;
		_move._allocator = nullptr;
	}
	~stack()
	{
		if (_buffer) {
			_allocator->deallocate(memory::cast_allocation<void>(_buffer));
		}
	}
	void push(int8_t _value)
	{
		push(static_cast<int32_t>(_value));
	}
	template<typename Type>
	void push(Type _value)
	{
		static_assert(sizeof(Type) <= element_size(), "Size of Type must be less than the element size.");

		if (_stack_pointer + 1 > _top_pointer) {
			BIA_IMPLEMENTATION_ERROR;
		}

		*reinterpret_cast<Type*>(_stack_pointer++) = _value;
	}
	template<typename Type>
	void push(Type * _value)
	{
		push(reinterpret_cast<intptr_t>(_value));
	}
	void drop_stack_frame(const element_t * _stack_frame)
	{
		if (_stack_frame < _base_pointer || _stack_frame > _top_pointer) {
			BIA_IMPLEMENTATION_ERROR;
		}

		_stack_pointer = const_cast<element_t*>(_stack_frame);
	}
	size_t size() const noexcept
	{
		return _stack_pointer - _base_pointer;
	}
	constexpr static size_t element_size() noexcept
	{
		return sizeof(element_t);
	}
	void * allocate_space(size_t _size)
	{
		auto _elements = _size / element_size() + (_size % element_size() ? element_size() : 0);

		// Check bounds
		if (_stack_pointer + _elements > _top_pointer) {
			BIA_IMPLEMENTATION_ERROR;
		}

		auto _tmp = _stack_pointer;

		_stack_pointer += _elements;

		return _tmp;
	}
	const element_t * create_stack_frame() const noexcept
	{
		return _stack_pointer;
	}
	template<typename Type>
	Type cast(ptrdiff_t _offset) noexcept
	{
		return *reinterpret_cast<Type*>(_stack_pointer + _offset);
	}
	template<typename Type>
	Type format_cast(ptrdiff_t _offset, char _format)
	{
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
	/** The top pointer of the stack. */
	const element_t * _top_pointer;
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
	static typename std::enable_if<utility::is_variant<To>::value, To>::type checked_convert(From _from)
	{
		To _variant;

		if (!To::try_types([_from, &_variant](auto _type) {
			typedef typename decltype(_type)::type type;

			if (To::template type_id<From>()) {
				if (std::is_same<From, type>::value) {
					_variant.template reconstruct<type>(checked_convert<type>(_from));

					return true;
				}
			} else {
				if (std::is_convertible<From, type>::value) {
					_variant.template reconstruct<type>(checked_convert<type>(_from));

					return true;
				}
			}

			return false;
		})) {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}

		return _variant;
	}
	template<typename To, typename From>
	static typename std::enable_if<!std::is_convertible<From, To>::value && !utility::is_variant<To>::value, To>::type checked_convert(From _from)
	{
		throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
	}
};

}
}