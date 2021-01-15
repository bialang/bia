#ifndef BIA_GC_STACK_HPP_
#define BIA_GC_STACK_HPP_

#include "memory/allocator.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/gsl.hpp>
#include <memory>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace bia {
namespace gc {

class Stack
{
public:
	Stack(std::shared_ptr<memory::Allocator> allocator, std::size_t size) : _allocator{ std::move(allocator) }
	{
		_memory = { static_cast<util::byte_type*>(_allocator->allocate(size)), size };
		_cursor = _memory.begin();
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
	void store(int offset, const Type& value)
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");

		const auto position = _cursor + offset;
		if (reinterpret_cast<std::intptr_t>(position) % alignof(Type)) {
			BIA_THROW(error::Code::bad_stack_alignment);
		} else if (position < _memory.begin() || position + sizeof(Type) > _memory.end()) {
			BIA_THROW(error::Code::out_of_stack);
		}
		std::memcpy(position, &value, sizeof(value));
	}

private:
	std::shared_ptr<memory::Allocator> _allocator;
	util::span<util::byte_type*> _memory;
	util::byte_type* _cursor;
};

} // namespace gc
} // namespace bia

#endif
