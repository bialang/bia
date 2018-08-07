import re

max_args = 3

def move_position(s):
	def c(x):
		return " * " + str(next(c.counter)) + ")"
		
	is_numbers = []
	
	for n in range(1, max_args + 1):
		is_numbers.append(n)
		
	c.counter = iter(is_numbers)
	
	return re.sub(""" \* \d+\)""", c, s)


f = open("Bia/disguised_caller.hpp", "wb")

f.write(b"""#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "member.hpp"
#include "allocator.hpp"
#include "exception.hpp"
#include "create_member.hpp"
#include "type_traits.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace force
{

template<typename _Return>
inline _Return format_cast(va_list & _args, const char *& _format)
{
	using namespace utility;

	switch (*_format++)
	{
	case 'i':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, int32_t>::choose(va_arg(_args, int32_t));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'I':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, int64_t>().choose(va_arg(_args, int64_t));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'd':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, double>().choose(va_arg(_args, double));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'a':
	{
		constexpr auto is_string = std::is_same<_Return, const char*>::value;

		if (is_string) {
			return chooser<is_string, _Return, const char*>().choose(va_arg(_args, const char*));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'M':
	{
		if (auto _ptr = va_arg(_args, framework::member*)->cast<_Return>()) {
			return *_ptr;
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	default:
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
	}
}

inline void disguised_caller(void(*_function)(), framework::member * _destination)
{
	_function();

	framework::create_member(_destination);
}

template<typename _Return>
inline void disguised_caller(_Return(*_function)(), framework::member * _destination)
{
	framework::create_member(_destination, _function());
}

template<typename _Return, typename... _Args>
inline void disguised_caller(_Return(*)(_Args...), framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename _Class>
inline void disguised_caller(void(_Class::*_function)(), _Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class>
inline void disguised_caller(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Return, typename _Class>
inline void disguised_caller(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Return, typename _Class>
inline void disguised_caller(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Return, typename _Class, typename... _Args>
inline void disguised_caller(_Return(_Class::*)(_Args...), _Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename _Return, typename _Class, typename... _Args>
inline void disguised_caller(_Return(_Class::*)(_Args...) const, const _Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename _Class>
inline machine::memory::allocator::allocation<_Class> disguised_caller()
{
	return machine::machine_context::active_allocator()->construct<_Class>();
}

template<typename _Class, typename... _Args>
inline typename std::enable_if<(sizeof...(_Args) > 0), machine::memory::allocator::allocation<_Class>>::type disguised_caller()
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

""")

for type in ["count", "format"]:
	upper = {}

	if type == "count":
		upper["function_name"] = "disguised_caller_count"
		upper["preparations"] = ""
		upper["format_param"] = ""
	else:
		upper["function_name"] = "disguised_caller_format"
		upper["preparations"] = ""
		upper["format_param"] = "const char * _format, "

	for template in ["static", "static_void", "member", "member_void", "member_const", "member_void_const", "initiator"]:
		filler = upper.copy()

		if template == "static":
			filler["template_begin"] = "template<typename _Return"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "_Return(*_function)("
			filler["param2"] = ""
			filler["param3"] = "), framework::member * _destination, "
			filler["body1"] = "framework::create_member(_destination, _function("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "static_void":
			filler["template_begin"] = ""
			filler["template_middle"] = ""
			filler["template_end"] = ""
			filler["function_return"] = "void"
			filler["param1"] = "void(*_function)("
			filler["param2"] = ""
			filler["param3"] = "), framework::member * _destination, "
			filler["body1"] = "_function("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::create_member(_destination);"""
		elif template == "member":
			filler["template_begin"] = "template<typename _Class, typename _Return"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "_Return(_Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = "), _Class * _instance, framework::member * _destination, "
			filler["body1"] = "framework::create_member(_destination, (_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "member_void":
			filler["template_begin"] = "template<typename _Class"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "void(_Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = "), _Class * _instance, framework::member * _destination, "
			filler["body1"] = "(_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::create_member(_destination);"""
		elif template == "member_const":
			filler["template_begin"] = "template<typename _Class, typename _Return"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "_Return(_Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = ") const, const _Class * _instance, framework::member * _destination, "
			filler["body1"] = "framework::create_member(_destination, (_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "member_void_const":
			filler["template_begin"] = "template<typename _Class"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "void(_Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = ") const, const _Class * _instance, framework::member * _destination, "
			filler["body1"] = "(_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::create_member(_destination);"""
		elif template == "initiator":
			filler["template_begin"] = "template<typename _Class"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "machine::memory::allocator::allocation<_Class>"
			filler["param1"] = ""
			filler["param2"] = ""
			filler["param3"] = ""
			filler["body1"] = "return machine::machine_context::active_allocator()->construct<_Class>("
			filler["body2"] = ""
			filler["body3"] = ");"

		for i in range(0, max_args + 1):
			filler["arg_count"] = i

			f.write("""{template_begin}{template_middle}{template_end}
inline {function_return} {function_name}({param1}{param2}{param3}{format_param}framework::member::parameter_count _count, va_list _args)
{{
	if (_count != {arg_count}) {{
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}}{preparations}

	{body1}{body2}{body3}
}}

""".format(**filler).encode())

			filler["template_middle"] += ("" if not filler["template_begin"] else ", ") + "typename _" + str(i)
			
			if template != "initiator":
				filler["param2"] += (", " if i != 0 else "") + "_" + str(i)
		
			if type == "count":
				filler["body2"] += (", " if i != 0 else "") + "*_v{0}".format(i)
				filler["preparations"] = """
	auto _v{0} = va_arg(_args, framework::member*)->cast<_{0}>();""".format(i) + move_position(filler["preparations"])
			else:
				filler["preparations"] = """
	auto _v{0} = format_cast<_{0}>(_args, _format);""".format(i) + filler["preparations"]
				filler["body2"] += (", " if i != 0 else "") + "std::forward<_{0}>(_v{0})".format(i)
			
			if template == "static_void":
				filler["template_begin"] = "template<"
				filler["template_end"] = ">"

f.write(b"}\n}")
f.close()
