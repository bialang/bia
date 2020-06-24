#ifndef BIA_UTIL_TYPE_TRAITS_TYPE_MAKER_HPP_
#define BIA_UTIL_TYPE_TRAITS_TYPE_MAKER_HPP_

#include <cstddef>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename... T>
struct type_container
{
	constexpr static auto size = sizeof...(T);
};

template<typename... T>
struct type_wrapper
{
	constexpr static type_container<T...> values{};
};

template<std::size_t Count, typename... T>
struct type_select : type_select<Count, type_container<>, type_container<T...>>
{};

template<std::size_t Count, typename... T, typename Other, typename... Others>
struct type_select<Count, type_container<T...>, type_container<Other, Others...>>
    : std::conditional<Count == 0, type_wrapper<T...>,
                       type_select<Count - 1, type_container<T..., Other>, type_container<Others...>>>::type
{};

template<std::size_t Count, typename... T>
struct type_select<Count, type_container<T...>, type_container<>>
    : std::conditional<Count == 0, type_wrapper<T...>, void>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
