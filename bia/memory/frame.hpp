#ifndef BIA_MEMORY_FRAME_HPP_
#define BIA_MEMORY_FRAME_HPP_

#include "stack.hpp"

namespace bia {
namespace memory {

class Frame
{
public:
	Frame(Stack& stack, std::size_t offset) noexcept : _stack{ stack }, _offset{ offset }
	{}
	Frame(Frame& parent, std::size_t offset) noexcept
	    : _stack{ parent._stack }, _offset{ offset - parent._offset }
	{}
	template<typename Type>
	void store(std::int32_t offset, const Type& value, bool mark = false)
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		std::lock_guard<std::mutex> _{ _stack._mutex };
		const auto position = _stack._memory.begin() + offset + _offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _stack._memory.begin() || position + sizeof(Type) > _stack._memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		std::memcpy(position, &value, sizeof(value));
		if (mark) {
			_stack._meta[(offset + _offset) / sizeof(void*) / 8] |= 1 << (offset + _offset) / sizeof(void*) % 8;
		} else {
			_stack._meta[(offset + _offset) / sizeof(void*) / 8] &= ~(1 << (offset + _offset) / sizeof(void*) % 8);
		}
	}
	template<typename Type>
	Type load(std::int32_t offset) const
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		std::lock_guard<std::mutex> _{ _stack._mutex };
		const auto position = _stack._memory.begin() + offset + _offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _stack._memory.begin() || position + sizeof(Type) > _stack._memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		Type value{};
		std::memcpy(&value, position, sizeof(value));
		return value;
	}

private:
	Stack& _stack;
	std::size_t _offset;
};

} // namespace memory
} // namespace bia

#endif
