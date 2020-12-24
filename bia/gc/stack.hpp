#ifndef BIA_GC_STACK_HPP_
#define BIA_GC_STACK_HPP_

#include "memory/allocator.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/gsl.hpp>
#include <memory>
#include <type_traits>

namespace bia {
namespace gc {

template<typename Element>
class Stack
{
public:
	static_assert(std::is_integral<Element>::value, "Element must be of integral type");
	typedef Element Type;

	Stack(std::shared_ptr<memory::allocator> allocator) : _allocator{ std::move(allocator) }
	{}
	template<typename Type>
	void push(const Type& value)
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		constexpr auto size = sizeof(Type) / sizeof(Element) + (sizeof(Type) % sizeof(Element) ? 1 : 0);
		if (_cursor + size > _memory.end()) {
			BIA_THROW(error::code::out_of_stack);
		}
		reinterpret_cast<Type*>(_cursor) = value;
		_cursor += size;
	}
	void pop(std::size_t count)
	{
		const auto tmp = _cursor - count;
		if (tmp < _memory.begin() || tmp > _memory.end()) {
			BIA_THROW(error::code::out_of_stack);
		}
		_cursor = tmp;
	}

private:
	std::shared_ptr<memory::allocator> _allocator;
	util::span<Element*> _memory;
	Element* _cursor;
};

} // namespace gc
} // namespace bia

#endif
