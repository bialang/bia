#ifndef BIA_UTIL_TYPE_TRAITS_TYPE_MAKER_HPP_
#define BIA_UTIL_TYPE_TRAITS_TYPE_MAKER_HPP_

#include <cstddef>
#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename... Types>
struct Type_container
{
	constexpr static std::size_t size = sizeof...(Types);

	static_assert(size == 0, "Implementation error");
};

template<typename Type, typename... Types>
struct Type_container<Type, Types...>
{
	typedef Type First;
	constexpr static std::size_t size = sizeof...(Types) + 1;
};

template<std::size_t Offset, std::size_t Count, typename Selected_container, typename... Types>
struct Type_select_impl;

template<std::size_t Offset, std::size_t Count, typename Type, typename... Types, typename... Selected>
struct Type_select_impl<Offset, Count, Type_container<Selected...>, Type, Types...>
    : std::conditional<Offset == 0,
                       Type_select_impl<0, Count - 1, Type_container<Selected..., Type>, Types...>,
                       Type_select_impl<Offset - 1, Count, Type_container<Selected...>, Types...>>::type
{
	static_assert(Offset + Count <= sizeof...(Types) + 1, "Cannot select more types than given");
};

template<std::size_t Offset, typename Type, typename... Types, typename... Selected>
struct Type_select_impl<Offset, 0, Type_container<Selected...>, Type, Types...>
    : Type_select_impl<0, 0, Type_container<Selected...>>
{
	static_assert(Offset <= sizeof...(Types) + 1, "Offset cannot be beyond type set size");
};

template<typename... Selected>
struct Type_select_impl<0, 0, Type_container<Selected...>>
{
	constexpr static Type_container<Selected...> selected{};
};

template<std::size_t Offset, std::size_t Count, typename... Types>
using Type_select = Type_select_impl<Offset, Count, Type_container<>, Types...>;

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
