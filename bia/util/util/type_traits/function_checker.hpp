#pragma once

#include "void_t.hpp"

#include <type_traits>
#include <utility>

namespace bia {
namespace util {
namespace type_traits {

template<typename T, typename, typename... Args>
struct is_functor_t : std::false_type
{};

template<typename Class, typename... Args>
struct is_functor_t<Class, void_t<decltype(std::declval<Class>()(std::declval<Args>()...))>, Args...> : std::true_type
{};

template<typename T, typename... Args>
using is_functor = is_functor_t<T, void_t<>, Args...>;

} // namespace type_traits
} // namespace util
} // namespace bia