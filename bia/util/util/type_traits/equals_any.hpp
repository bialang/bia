#ifndef BIA_UTIL_TYPE_TRAITS_EQUALS_ANY_HPP_
#define BIA_UTIL_TYPE_TRAITS_EQUALS_ANY_HPP_

#include <cstddef>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

/* equals any */
template<std::size_t Index, typename T, T Value, T... Others>
struct equals_any_t;

template<std::size_t Index, typename T, T Value, T Other>
struct equals_any_t<Index, T, Value, Other> : std::integral_constant<bool, Value == Other>
{};

template<std::size_t Index, typename T, T Value, T Other, T... Others>
struct equals_any_t<Index, T, Value, Other, Others...>
    : std::conditional<Value == Other, std::true_type, equals_any_t<Index + 1, T, Value, Others...>>::type
{};

template<typename T, T Value, T... Other>
using equals_any = equals_any_t<1, T, Value, Other...>;

/* equals any type */
template<std::size_t Index, typename T, typename... Others>
struct equals_any_type_t;

template<std::size_t Index, typename T, typename Other>
struct equals_any_type_t<Index, T, Other> : std::integral_constant<bool, std::is_same<T, Other>::value>
{};

template<std::size_t Index, typename T, typename Other, typename... Others>
struct equals_any_type_t<Index, T, Other, Others...>
    : std::conditional<std::is_same<T, Other>::value, std::true_type,
                       equals_any_type_t<Index + 1, T, Others...>>::type
{};

template<typename T, typename... Others>
using equals_any_type = equals_any_type_t<1, T, Others...>;

} // namespace type_traits
} // namespace util
} // namespace bia

#endif