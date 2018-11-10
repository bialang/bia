#pragma once

#include <type_traits>


namespace bia
{
namespace utility
{

template<typename Type>
inline constexpr Type max(Type _first, Type _second)
{
	return _first > _second ? _first : _second;
}

template<typename Type, typename... Arguments>
inline constexpr typename std::enable_if<(sizeof...(Arguments) > 1), Type>::type max(Type _first, Arguments... _arguments)
{
	return _first > max(_arguments...) ? _first : max(_arguments...);
}

}
}