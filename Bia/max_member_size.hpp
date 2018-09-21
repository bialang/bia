#pragma once

#include <type_traits>

#include "native_member.hpp"
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

template<typename _Ty>
inline constexpr _Ty max(_Ty _first, _Ty _second)
{
	return _first > _second ? _first : _second;
}

template<typename _Ty, typename... _Args>
inline constexpr typename std::enable_if<(sizeof...(_Args) > 1), _Ty>::type max(_Ty _first, _Args... _args)
{
	return _first > max(_args...) ? _first : max(_args...);
}

constexpr auto max_member_size = max(
	sizeof(native::cstring_member<char>),
	sizeof(native::int_member),
	sizeof(native::double_member),
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