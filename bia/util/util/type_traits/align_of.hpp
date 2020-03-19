#ifndef BIA_UTIL_TYPE_TRAITS_ALIGN_OF_HPP_
#define BIA_UTIL_TYPE_TRAITS_ALIGN_OF_HPP_

#include <cstddef>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename...>
struct align_of;

template<>
struct align_of<> : std::integral_constant<std::size_t, 0>
{};

template<typename T>
struct align_of<T> : std::integral_constant<std::size_t, alignof(T)>
{};

template<typename T, typename... Ts>
struct align_of<T, Ts...> : std::integral_constant<std::size_t, alignof(T) + align_of<Ts...>::value>
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif