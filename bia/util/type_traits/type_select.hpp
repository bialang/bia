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

template<std::size_t Offset, std::size_t Count, typename... Types>
struct type_select : type_select<Offset, Count, type_container<>, type_container<Types...>>
{};

template<std::size_t Offset, std::size_t Count, typename... Selected, typename Next, typename... Others>
struct type_select<Offset, Count, type_container<Selected...>, type_container<Next, Others...>>
    : type_select<Offset - 1, Count, type_container<>, type_container<Others...>>
{};

template<std::size_t Count, typename... Selected, typename Next, typename... Others>
struct type_select<0, Count, type_container<Selected...>, type_container<Next, Others...>>
    : std::conditional<
          Count == 0, type_wrapper<Selected...>,
          type_select<0, Count - 1, type_container<Selected..., Next>, type_container<Others...>>>::type
{};

template<std::size_t Offset, std::size_t Count, typename... Selected>
struct type_select<Offset, Count, type_container<Selected...>, type_container<>>
    : std::conditional<Offset == 0 && Count == 0, type_wrapper<Selected...>, void>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
