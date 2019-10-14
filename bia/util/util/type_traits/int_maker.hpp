#pragma once

#include <cstdint>

namespace bia {
namespace util {
namespace type_traits {

template<typename T, T... Ints>
struct int_container
{};

template<typename T, std::size_t Count, T Value, T... Ints>
struct int_maker : int_maker<T, Count - 1, Value, Ints..., Value>
{};

/* starter */
template<typename T, std::size_t Count, T Value>
struct int_maker<T, Count, Value> : int_maker<T, Count - 1, Value, Value>
{
	constexpr static auto count = Count;
	typedef T int_type;
};

/* stopper */
template<typename T, T Value, T... Ints>
struct int_maker<T, 0, Value, Ints...>
{
	constexpr static int_container<T, Ints...> values{};
};

} // namespace type_traits
} // namespace util
} // namespace bia