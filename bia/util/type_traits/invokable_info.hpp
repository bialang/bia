#ifndef BIA_UTIL_TYPE_TRAITS_INVOKABLE_INFO_HPP_
#define BIA_UTIL_TYPE_TRAITS_INVOKABLE_INFO_HPP_

#include "type_select.hpp"
#include "void.hpp"

namespace bia {
namespace util {
namespace type_traits {

template<typename Invokeable, typename = void>
struct Invokable_info
{
	constexpr static bool is_invokable = false;
	constexpr static bool is_static    = false;
	constexpr static bool is_method    = false;
	constexpr static bool is_const     = false;
	constexpr static bool is_functor   = false;
	// TODO noexcept
};

template<typename Return_, typename... Arguments>
struct Invokable_info<Return_ (*)(Arguments...), void>
{
	constexpr static bool is_invokable = true;
	constexpr static bool is_static    = true;
	constexpr static bool is_method    = false;
	constexpr static bool is_const     = false;
	constexpr static bool is_functor   = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Return (*Signature)(Arguments...);
};

template<typename Return_, typename... Arguments>
struct Invokable_info<Return_(Arguments...), void>
{
	constexpr static bool is_invokable = true;
	constexpr static bool is_static    = true;
	constexpr static bool is_method    = false;
	constexpr static bool is_const     = false;
	constexpr static bool is_functor   = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Return(Signature)(Arguments...);
};

template<typename Class_, typename Return_, typename... Arguments>
struct Invokable_info<Return_ (Class_::*)(Arguments...), void>
{
	constexpr static bool is_invokable = true;
	constexpr static bool is_static    = false;
	constexpr static bool is_method    = true;
	constexpr static bool is_const     = false;
	constexpr static bool is_functor   = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Class_ Class;
	typedef Return (Class::*Signature)(Arguments...);
};

template<typename Class_, typename Return_, typename... Arguments>
struct Invokable_info<Return_ (Class_::*)(Arguments...) const, void>
{
	constexpr static bool is_invokable = true;
	constexpr static bool is_static    = false;
	constexpr static bool is_method    = true;
	constexpr static bool is_const     = true;
	constexpr static bool is_functor   = false;
	constexpr static type_container<Arguments...> arguments{};
	constexpr static std::size_t argument_count = sizeof...(Arguments);
	typedef Return_ Return;
	typedef Class_ Class;
	typedef Return (Class::*Signature)(Arguments...) const;
};

template<typename Functor>
struct Invokable_info<Functor, Void<decltype(&Functor::operator())>>
    : Invokable_info<decltype(&Functor::operator())>
{
	constexpr static bool is_functor = true;
};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
