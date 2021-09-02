#ifndef BIA_UTIL_TYPE_TRAITS_IS_INVOKABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_INVOKABLE_HPP_

#include "void.hpp"

#include <type_traits>
#include <utility>

namespace bia {
namespace util {
namespace type_traits {

template<typename Callable, typename = void, typename... Arguments>
struct Is_invokable_t : std::false_type
{};

template<typename Callable, typename... Arguments>
struct Is_invokable_t<Callable, Void<decltype(std::declval<Callable>()(std::declval<Arguments>()...))>,
                      Arguments...> : std::true_type
{};

template<typename Callable, typename... Arguments>
using Is_invokable = Is_invokable_t<Callable, void, Arguments...>;

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
