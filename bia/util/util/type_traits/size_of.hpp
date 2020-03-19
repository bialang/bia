#ifndef BIA_UTIL_TYPE_TRATIS_SIZE_OF_HPP_
#define BIA_UTIL_TYPE_TRATIS_SIZE_OF_HPP_

#include <cstddef>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename...>
struct size_of;

template<>
struct size_of<> : std::integral_constant<std::size_t, 0>
{};

template<typename T>
struct size_of<T> : std::integral_constant<std::size_t, sizeof(T)>
{};

template<typename T, typename... Ts>
struct size_of<T, Ts...> : std::integral_constant<std::size_t, sizeof(T) + size_of<Ts...>::value>
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif