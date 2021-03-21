#ifndef BIA_UTIL_TYPE_TRAITS_FUNCTION_INFO_HPP_
#define BIA_UTIL_TYPE_TRAITS_FUNCTION_INFO_HPP_

#include "type_select.hpp"
#include "void_type.hpp"

namespace bia {
namespace util {
namespace type_traits {

template<typename Function>
struct Function_info
{
	constexpr static bool is_function = false;
	constexpr static bool is_member   = false;
	constexpr static bool is_const    = false;
	// TODO noexcept
};

template<typename Return_, typename... Arguments>
struct Function_info<Return_ (*)(Arguments...)>
{
	constexpr static bool is_function = true;
	constexpr static bool is_member   = false;
	constexpr static bool is_const    = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Return (*Signature)(Arguments...);
};

template<typename Return_, typename... Arguments>
struct Function_info<Return_(Arguments...)>
{
	constexpr static bool is_function = true;
	constexpr static bool is_member   = false;
	constexpr static bool is_const    = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Return(Signature)(Arguments...);
};

template<typename Class_, typename Return_, typename... Arguments>
struct Function_info<Return_ (Class_::*)(Arguments...)>
{
	constexpr static bool is_function = true;
	constexpr static bool is_member   = true;
	constexpr static bool is_const    = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Class_ Class;
	typedef Return (Class::*Signature)(Arguments...);
};

template<typename Class_, typename Return_, typename... Arguments>
struct Function_info<Return_ (Class_::*)(Arguments...) const>
{
	constexpr static bool is_function = true;
	constexpr static bool is_member   = true;
	constexpr static bool is_const    = true;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Class_ Class;
	typedef Return (Class::*Signature)(Arguments...) const;
};

template<typename Functor, typename = void_type<>>
struct Functor_info
{
	constexpr static bool is_function = false;
	constexpr static bool is_member   = false;
	constexpr static bool is_const    = false;
	constexpr static bool is_functor  = false;
};

template<typename Functor>
struct Functor_info<Functor, void_type<decltype(&Functor::operator())>>
    : Function_info<decltype(&Functor::operator())>
{
	constexpr static bool is_functor = true;
};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
