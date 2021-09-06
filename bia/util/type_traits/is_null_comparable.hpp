#ifndef BIA_UTIL_TYPE_TRAITS_IS_NULL_COMPARABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_NULL_COMPARABLE_HPP_

#include "void.hpp"

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename T, typename = Void<>>
struct is_equal_null_comparable : std::false_type
{};

template<typename T>
struct is_equal_null_comparable<T, Void<decltype(std::declval<T>() == nullptr)>> : std::true_type
{};

template<typename T, typename = Void<>>
struct is_unequal_null_comparable : std::false_type
{};

template<typename T>
struct is_unequal_null_comparable<T, Void<decltype(std::declval<T>() != nullptr)>> : std::true_type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
