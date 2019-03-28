#pragma once

#include "max.hpp"
#include "int_member.hpp"
#include "big_int_member.hpp"
#include "double_member.hpp"
#include "cstring_member_def.hpp"
#include "static_function.hpp"
#include "lambda_function_def.hpp"
#include "member_function_def.hpp"
#include "object_def.hpp"
#include "raw_object_def.hpp"
#include "class_template_def.hpp"
#include "namespace_member.hpp"


namespace bia
{
namespace framework
{

constexpr auto max_member_size = utility::max(
	sizeof(native::int_member),
	sizeof(native::big_int_member),
	sizeof(native::double_member),
	sizeof(native::cstring_member<char>),
	sizeof(executable::static_function<0, void>),
	//sizeof(executable::lambda_function),
	//sizeof(executable::member_function),
	sizeof(object::raw_object<int>),
	sizeof(object::object<int>),
	sizeof(object::class_template<int>),
	sizeof(object::namespace_member)
);

}
}
