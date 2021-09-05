#ifndef BIA_UTIL_TYPE_TRAITS_TYPE_INDEX_HPP_
#define BIA_UTIL_TYPE_TRAITS_TYPE_INDEX_HPP_

#include "../config.hpp"

#include <cstddef>
#include <limits>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename...>
struct type_index;

template<>
struct type_index<> : std::integral_constant<std::size_t, std::numeric_limits<std::size_t>::max()>
{};

template<typename T, typename V>
struct type_index<T, V> : std::conditional<std::is_same<T, V>::value, std::integral_constant<std::size_t, 0>,
                                           std::integral_constant<std::size_t, npos>>::type
{};

template<typename T, typename V, typename... Ts>
struct type_index<T, V, Ts...>
    : std::conditional<
        std::is_same<T, V>::value, std::integral_constant<std::size_t, 0>,
        std::integral_constant<std::size_t, type_index<T, Ts...>::value +
                                              (type_index<T, Ts...>::value == npos ? 0 : 1)>>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
