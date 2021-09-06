#ifndef BIA_UTIL_TYPE_TRAITS_IS_FRAMEABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_FRAMEABLE_HPP_

#include "void.hpp"

#include <type_traits>

namespace bia {
namespace internal {
namespace type {

template<typename Type, typename>
struct Framer;

} // namespace type
} // namespace internal
namespace util {
namespace type_traits {

template<typename Type, typename = void>
struct Is_frameable : std::false_type
{};

template<typename Type>
struct Is_frameable<Type, Void<decltype(sizeof(internal::type::Framer<Type>))>> : std::true_type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
