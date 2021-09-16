#ifndef BIA_UTIL_TYPE_TRAITS_IS_VARIANT_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_VARIANT_HPP_

#include "../variant.hpp"

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename Type>
struct Is_variant : std::false_type
{};

template<typename... Types>
struct Is_variant<Variant<Types...>> : std::true_type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
