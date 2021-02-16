#ifndef BIA_GC_STACK_HPP_
#define BIA_GC_STACK_HPP_

#include "memory/allocator.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/gsl.hpp>
#include <cstdint>
#include <cstring>
#include <memory>
#include <type_traits>

namespace bia {
namespace gc {

class Stack
{
public:
	Stack(std::shared_ptr<memory::Allocator> allocator, std::size_t size) : _allocator{ std::move(allocator) }
	{
		_memory = { static_cast<util::Byte*>(_allocator->allocate(size)), size };
		_cursor = _memory.begin();
		std::memset(_memory.begin(), 0, _memory.size_bytes());
	}
	void increment(std::size_t bytes)
	{
		_cursor += bytes;
	}
	void decrement(std::size_t bytes)
	{
		_cursor -= bytes;
	}
	template<typename Type>
	void store(std::int32_t offset, const Type& value)
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		const auto position = _cursor + offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			// TODO
			// BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _memory.begin() || position + sizeof(Type) > _memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		std::memcpy(position, &value, sizeof(value));
	}
	template<typename Type>
	Type load(std::int32_t offset) const
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		const auto position = _cursor + offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			// TODO
			// BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _memory.begin() || position + sizeof(Type) > _memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		Type value{};
		std::memcpy(&value, position, sizeof(value));
		return value;
	}

private:
	std::shared_ptr<memory::Allocator> _allocator;
	util::Span<util::Byte*> _memory;
	util::Byte* _cursor;
};

} // namespace gc
} // namespace bia

#endif
