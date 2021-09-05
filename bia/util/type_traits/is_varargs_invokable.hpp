#ifndef BIA_UTIL_TYPE_TRAITS_IS_VARARGS_INVOKABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_VARARGS_INVOKABLE_HPP_

#include "invokable_info.hpp"
#include "type_at.hpp"

#include <type_traits>

namespace bia {
namespace member {
namespace function {

template<typename Type>
class Varargs;

} // namespace function
} // namespace member

namespace util {
namespace type_traits {

template<typename Type>
struct Is_varargs : std::false_type
{};

template<typename Type>
struct Is_varargs<member::function::Varargs<Type>> : std::true_type
{};

template<typename>
struct Is_varargs_compatible_container : std::false_type
{};

template<typename Type, typename... Types>
struct Is_varargs_compatible_container<type_container<Type, Types...>>
    : std::conditional<Is_varargs<Type>::value, std::integral_constant<bool, sizeof...(Types) == 0>,
                       Is_varargs_compatible_container<type_container<Types...>>>::type
{};

template<typename Invokable>
struct Is_varargs_invokable
    : std::integral_constant<bool, (Invokable_info<Invokable>::is_invokable &&
                                    Is_varargs_compatible_container<typename std::decay<
                                      decltype(Invokable_info<Invokable>::arguments)>::type>::value)>
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
