#ifndef BIA_UTIL_TYPE_TRAITS_IS_VARIANT_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_VARIANT_HPP_

#include "../variant.hpp"

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {
namespace detail {

template<typename Type>
struct is_variant : std::false_type
{};

template<typename... Types>
struct is_variant<variant<Types...>> : std::true_type
{};

} // namespace detail

template<typename Type>
using is_variant = detail::is_variant<typename std::decay<Type>::type>;

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
