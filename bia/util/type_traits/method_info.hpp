#ifndef BIA_UTIL_TYPE_TRAITS_METHOD_INFO_HPP_
#define BIA_UTIL_TYPE_TRAITS_METHOD_INFO_HPP_

#include "type_maker.hpp"

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

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
