#pragma once

#include <cstddef>
#include <cstdint>
#include <exception/stack_overflow_exception.hpp>
#include <gc/memory_allocator.hpp>
#include <type_traits>

namespace bia {
namespace stack {

class stack
{
public:
	typedef std::int32_t buffer_type;

	class frame
	{
	public:
		frame(const frame& copy) = delete;
		frame(frame&& move)
		{
			s	  = move.s;
			old	= move.old;
			move.s = nullptr;
		}
		~frame()
		{
			if (s) {
				if (old > s->current_size) {
					BIA_THROW(exception::stack_overflow_exception, u"frame is corrupt");
				}

				s->current_size = old;
			}
		}

	private:
		friend stack;

		stack* s;
		std::size_t old;

		frame(stack* s, std::size_t old) : s(s), old(old)
		{}
	};

	stack(gc::memory_allocator* allocator, std::size_t size) noexcept
	{
		this->allocator = allocator;
		current_size	= 0;
		max_size		= size / sizeof(buffer_type) * sizeof(buffer_type);
		buffer			= static_cast<buffer_type*>(allocator->allocate(max_size, 0));
	}
	frame create_frame() noexcept
	{
		return frame(this, current_size);
	}
	void pop(std::size_t count)
	{
		if (count > current_size) {
			BIA_THROW(exception::stack_overflow_exception, u"pop count exceeds stack size");
		}

		current_size -= count;
	}
	template<typename T>
	typename std::enable_if<(sizeof(T) < sizeof(buffer_type)), std::size_t>::type push(T value)
	{
		if (current_size + 1 > max_size) {
			BIA_THROW(exception::stack_overflow_exception, u"stack overflowed during push");
		}

		buffer[current_size] = 0;

		std::memcpy(buffer + current_size++, &value, sizeof(T));

		return 1;
	}
	template<typename T>
	typename std::enable_if<(sizeof(T) >= sizeof(buffer_type) && sizeof(T) % sizeof(buffer_type) == 0),
							std::size_t>::type
		push(T value)
	{
		constexpr auto size = sizeof(T) / sizeof(buffer_type);

		if (current_size + size > max_size) {
			BIA_THROW(exception::stack_overflow_exception, u"stack overflowed during push");
		}

		std::memcpy(buffer + current_size, &value, sizeof(T));

		current_size += size;

		return size;
	}
	template<typename T>
	std::size_t push(T* pointer)
	{
		return push(reinterpret_cast<std::intptr_t>(pointer));
	}

private:
	gc::memory_allocator* allocator;
	buffer_type* buffer;
	std::size_t current_size;
	std::size_t max_size;
};

} // namespace stack
} // namespace bia