#ifndef BIA_UTIL_TYPE_TRAITS_HPP_
#define BIA_UTIL_TYPE_TRAITS_HPP_

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<bool...>
struct conjunction : std::false_type
{};

template<bool B>
struct conjunction<B> : std::conditional<B, std::true_type, std::false_type>::type
{};

template<bool B0, bool... B>
struct conjunction<B0, B...>
    : std::conditional<B0 && conjunction<B...>::value, std::true_type, std::false_type>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif