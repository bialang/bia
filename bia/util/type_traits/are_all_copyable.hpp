#ifndef BIA_UTIL_TYPE_TRAITS_ARE_ALL_COPYABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_ARE_ALL_COPYABLE_HPP_

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename...>
struct are_all_copy_constructible;

template<typename T>
struct are_all_copy_constructible<T> : std::is_copy_constructible<T>
{};

template<typename T, typename... Ts>
struct are_all_copy_constructible<T, Ts...>
    : std::conditional<std::is_copy_constructible<T>::value, are_all_copy_constructible<Ts...>,
                       std::false_type>::type
{};

template<typename...>
struct are_all_copy_assignable;

template<typename T>
struct are_all_copy_assignable<T> : std::is_copy_assignable<T>
{};

template<typename T, typename... Ts>
struct are_all_copy_assignable<T, Ts...>
    : std::conditional<std::is_copy_assignable<T>::value, are_all_copy_assignable<Ts...>,
                       std::false_type>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif