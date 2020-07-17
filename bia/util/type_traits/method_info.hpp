#ifndef BIA_UTIL_TYPE_TRAITS_METHOD_INFO_HPP_
#define BIA_UTIL_TYPE_TRAITS_METHOD_INFO_HPP_

#include "type_select.hpp"
#include "void_type.hpp"

namespace bia {
namespace util {
namespace type_traits {

template<typename Type>
struct method_info
{
	constexpr static auto is_method = false;
};

template<typename Class, typename Return, typename... Args>
struct method_info<Return (Class::*)(Args...)>
{
	typedef Class class_type;
	typedef Return return_type;
	typedef Return (Class::*function_type)(Args...);

	constexpr static auto is_method = true;
	constexpr static auto is_const  = false;
	constexpr static auto arg_count = sizeof...(Args);
	constexpr static type_container<Args...> args{};
};

template<typename Class, typename Return, typename... Args>
struct method_info<Return (Class::*)(Args...) const>
{
	typedef Class class_type;
	typedef Return return_type;
	typedef Return (Class::*function_type)(Args...) const;

	constexpr static auto is_method = true;
	constexpr static auto is_const  = true;
	constexpr static auto arg_count = sizeof...(Args);
	constexpr static type_container<Args...> args{};
};

template<typename Functor, typename = void_type<>>
struct functor_info
{
	constexpr static auto is_functor = false;
};

template<typename Functor>
struct functor_info<Functor, void_type<decltype(&Functor::operator())>>
    : method_info<decltype(&Functor::operator())>
{
	constexpr static auto is_functor = true;
};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
