#pragma once

#include <cstddef>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename... T>
struct size_of : std::integral_constant<std::size_t, 0>
{};

template<typename T>
struct size_of<T> : std::integral_constant<std::size_t, sizeof(T)>
{};

template<typename T0, typename... T>
struct size_of<T0, T...> : std::integral_constant<std::size_t, sizeof(T0) + size_of<T...>::value>
{};

} // namespace type_traits
} // namespace util
} // namespace bia