#pragma once

#include <type_traits>
#include <cstddef>


namespace bia
{
namespace utility
{

template<typename Type>
inline constexpr Type max(Type _first, Type _second) noexcept
{
	return _first > _second ? _first : _second;
}

template<typename Type, typename... Arguments>
inline constexpr typename std::enable_if<(sizeof...(Arguments) > 1), Type>::type max(Type _first, Arguments... _arguments) noexcept
{
	return _first > max(_arguments...) ? _first : max(_arguments...);
}

template<typename Type>
inline constexpr size_t max_sizeof() noexcept
{
	return sizeof(Type);
}

template<typename Type, typename... Types>
inline constexpr typename std::enable_if<(sizeof...(Types) > 0), size_t>::type max_sizeof() noexcept
{
	return sizeof(Type) > max_sizeof<Types...>() ? sizeof(Type) : max_sizeof<Types...>();
}

}
}