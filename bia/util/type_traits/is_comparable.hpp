#ifndef BIA_UTIL_TYPE_TRAITS_IS_COMPARABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_COMPARABLE_HPP_

#include "void.hpp"

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename Left, typename Right, typename = Void<>>
struct Is_equal_comparable : std::false_type
{};

template<typename Left, typename Right>
struct Is_equal_comparable<Left, Right, Void<decltype(std::declval<Left>() == std::declval<Right>())>>
    : std::true_type
{};

template<typename Left, typename Right, typename = Void<>>
struct Is_unequal_comparable : std::false_type
{};

template<typename Left, typename Right>
struct Is_unequal_comparable<Left, Right, Void<decltype(std::declval<Left>() != std::declval<Right>())>>
    : std::true_type
{};

template<typename Left, typename Right, typename = Void<>>
struct Is_less_comparable : std::false_type
{};

template<typename Left, typename Right>
struct Is_less_comparable<Left, Right, Void<decltype(std::declval<Left>() < std::declval<Right>())>>
    : std::true_type
{};

template<typename Left, typename Right, typename = Void<>>
struct Is_less_equal_comparable : std::false_type
{};

template<typename Left, typename Right>
struct Is_less_equal_comparable<Left, Right, Void<decltype(std::declval<Left>() <= std::declval<Right>())>>
    : std::true_type
{};

template<typename Left, typename Right, typename = Void<>>
struct Is_greater_comparable : std::false_type
{};

template<typename Left, typename Right>
struct Is_greater_comparable<Left, Right, Void<decltype(std::declval<Left>() > std::declval<Right>())>>
    : std::true_type
{};

template<typename Left, typename Right, typename = Void<>>
struct Is_greater_equal_comparable : std::false_type
{};

template<typename Left, typename Right>
struct Is_greater_equal_comparable<Left, Right, Void<decltype(std::declval<Left>() >= std::declval<Right>())>>
    : std::true_type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
