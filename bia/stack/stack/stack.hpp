#pragma once

#include <cstddef>
#include <cstdint>
#include <exception/stack_overflow_exception.hpp>
#include <gc/memory_allocator.hpp>
#include <type_traits>
#include <util/type_traits/type_at.hpp>
#include <util/type_traits/type_maker.hpp>

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
		frame(frame&& move) noexcept
		{
			s      = move.s;
			old    = move.old;
			move.s = nullptr;
		}
		void destroy()
		{
			if (s) {
				if (old > s->current_size) {
					BIA_THROW(exception::stack_overflow_exception, u"frame is corrupt");
				}

				s->current_size = old;
			}
		}
		~frame()
		{
			try {
				destroy();
			} catch (...) {
				// leave the stack corrupt instead of crashing
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
		current_size    = 0;
		max_size        = size / sizeof(buffer_type);
		buffer          = static_cast<buffer_type*>(allocator->allocate(max_size * sizeof(buffer_type), 0));
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
	template<typename... T>
	typename util::type_traits::type_at<sizeof...(T) - 1, T...>::type get(util::type_traits::type_container<T...>)
	{
		typedef typename util::type_traits::type_at<sizeof...(T) - 1, T...>::type type;
		constexpr auto size = size_of<T...>();

		if (current_size < size) {
			BIA_THROW(exception::stack_overflow_exception, u"cannot extract more elements from the stack (underflow)");
		}

		type value{};

		std::memcpy(&value, buffer + current_size - size, sizeof(type));

		return value;
	}

private:
	gc::memory_allocator* allocator;
	buffer_type* buffer;
	std::size_t current_size;
	std::size_t max_size;

	template<typename T>
	constexpr static typename std::enable_if<(sizeof(T) < sizeof(buffer_type)), std::size_t>::type size_of()
	{
		return 1;
	}
	template<typename T>
	constexpr static typename std::enable_if<(sizeof(T) >= sizeof(buffer_type) && sizeof(T) % sizeof(buffer_type) == 0),
	                                         std::size_t>::type
	    size_of()
	{
		return sizeof(T) / sizeof(buffer_type);
	}
	template<typename T, typename... Ts>
	constexpr static typename std::enable_if<sizeof...(Ts) != 0, std::size_t>::type size_of()
	{
		return size_of<T>() + size_of<Ts...>();
	}
	template<typename... Ts>
	constexpr static typename std::enable_if<sizeof...(Ts) == 0, std::size_t>::type size_of()
	{
		return 0;
	}
};

} // namespace stack
} // namespace bia