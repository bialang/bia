#ifndef BIA_UTIL_TYPE_TRAITS_MULTI_COMPARABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_MULTI_COMPARABLE_HPP_

#include "int_maker.hpp"
#include "is_comparable.hpp"
#include "type_select.hpp"

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

/// Equal.
template<std::size_t Index, typename Index_container, typename Right, typename... Lefts>
struct Multi_equal_comparable_impl;

template<std::size_t Index, typename Right, typename Left, typename... Others, std::size_t... Indices>
struct Multi_equal_comparable_impl<Index, Int_container<std::size_t, Indices...>, Right, Left, Others...>
    : std::conditional<Is_equal_comparable<Left, Right>::value,
                       Multi_equal_comparable_impl<Index + 1, Int_container<std::size_t, Indices..., Index>,
                                                   Right, Others...>,
                       Multi_equal_comparable_impl<Index + 1, Int_container<std::size_t, Indices...>, Right,
                                                   Others...>>::type
{};

template<std::size_t Index, typename Right, std::size_t... Indices>
struct Multi_equal_comparable_impl<Index, Int_container<std::size_t, Indices...>, Right>
{
	constexpr static Int_container<std::size_t, Indices...> indices{};
};

template<typename Right, typename... Lefts>
using Multi_equal_comparable = Multi_equal_comparable_impl<0, Int_container<std::size_t>, Right, Lefts...>;

/// Unequal.
template<std::size_t Index, typename Index_container, typename Right, typename... Lefts>
struct Multi_unequal_comparable_impl;

template<std::size_t Index, typename Right, typename Left, typename... Others, std::size_t... Indices>
struct Multi_unequal_comparable_impl<Index, Int_container<std::size_t, Indices...>, Right, Left, Others...>
    : std::conditional<Is_unequal_comparable<Left, Right>::value,
                       Multi_unequal_comparable_impl<Index + 1, Int_container<std::size_t, Indices..., Index>,
                                                     Right, Others...>,
                       Multi_unequal_comparable_impl<Index + 1, Int_container<std::size_t, Indices...>, Right,
                                                     Others...>>::type
{};

template<std::size_t Index, typename Right, std::size_t... Indices>
struct Multi_unequal_comparable_impl<Index, Int_container<std::size_t, Indices...>, Right>
{
	constexpr static Int_container<std::size_t, Indices...> indices{};
};

template<typename Right, typename... Lefts>
using Multi_unequal_comparable =
  Multi_unequal_comparable_impl<0, Int_container<std::size_t>, Right, Lefts...>;

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
