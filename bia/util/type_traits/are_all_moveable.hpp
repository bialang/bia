#ifndef BIA_UTIL_TYPE_TRAITS_ARE_ALL_MOVEABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_ARE_ALL_MOVEABLE_HPP_

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename...>
struct are_all_move_constructible;

template<typename T>
struct are_all_move_constructible<T> : std::is_move_constructible<T>
{};

template<typename T, typename... Ts>
struct are_all_move_constructible<T, Ts...>
    : std::conditional<std::is_move_constructible<T>::value, are_all_move_constructible<Ts...>,
                       std::false_type>::type
{};

template<typename...>
struct are_all_move_assignable;

template<typename T>
struct are_all_move_assignable<T> : std::is_move_assignable<T>
{};

template<typename T, typename... Ts>
struct are_all_move_assignable<T, Ts...>
    : std::conditional<std::is_move_assignable<T>::value, are_all_move_assignable<Ts...>,
                       std::false_type>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif