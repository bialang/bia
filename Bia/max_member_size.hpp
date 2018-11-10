#pragma once

#include "max.hpp"
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