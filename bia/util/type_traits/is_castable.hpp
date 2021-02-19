#ifndef BIA_UTIL_TYPE_TRAITS_IS_CASTABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_CASTABLE_HPP_

#include "void_type.hpp"

#include <type_traits>
#include <utility>

namespace bia {
namespace util {
namespace type_traits {

template<typename From, typename To, typename = void>
struct Is_static_castable_t : std::false_type
{};

template<typename From, typename To>
struct Is_static_castable_t<From, To, void_type<decltype(static_cast<To>(std::declval<From>()))>>
    : std::true_type
{};

template<typename From, typename To>
using Is_static_castable = Is_static_castable_t<From, To>;

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
