#pragma once

#include <type_traits>

#include "int_member.hpp"
#include "double_member.hpp"
#include "cstring_member.hpp"
#include "static_function.hpp"
#include "lambda_function.hpp"
#include "member_function.hpp"
#include "raw_object.hpp"
#include "object.hpp"
#include "class_template.hpp"
#include "namespace_member.hpp"


namespace bia
{
namespace framework
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

constexpr auto max_member_size = max(
	sizeof(native::int_member),
	sizeof(native::double_member),
	sizeof(native::cstring_member<char>),
	sizeof(executable::static_function<void>),
	//sizeof(executable::lambda_function),
	//sizeof(executable::member_function),
	sizeof(object::raw_object<int>),
	sizeof(object::object<int>),
	sizeof(object::class_template<int>),
	sizeof(object::namespace_member)
);

}
}