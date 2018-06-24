#pragma once

#include "native_member.hpp"
#include "cstring_member.hpp"
#include "static_function.hpp"
#include "lambda_function.hpp"
#include "member_function.hpp"


namespace bia
{
namespace framework
{

template<typename _Ty>
inline constexpr _Ty max(_Ty && _first, _Ty && _second)
{
	return _first > _second ? _first : _second;
}

constexpr auto max_member_size = max(sizeof(native::cstring_member),
	max(sizeof(native::int_member),
		max(sizeof(executable::static_function<void>), size_t(0))));

}
}