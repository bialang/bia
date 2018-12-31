import re

max_args = 20

def move_position(s):
	def c(x):
		return " * " + str(next(c.counter)) + ")"

	is_numbers = []

	for n in range(1, max_args + 1):
		is_numbers.append(n)

	c.counter = iter(is_numbers)

	return re.sub(""" \* \d+\)""", c, s)


h = open("Bia/disguised_caller.hpp", "wb")
f = open("Bia/disguised_caller_source.hpp", "wb")

h.write(b"""#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "member.hpp"
#include "allocator.hpp"
#include "type_traits.hpp"


namespace bia
{
namespace force
{

struct va_list_wrapper
{
	std::va_list args;
};

template<typename Return>
Return format_cast(va_list_wrapper & _args, const char *& _format);

void disguised_caller(void(*_function)(), framework::member * _destination);

template<typename Return>
void disguised_caller(Return(*_function)(), framework::member * _destination);

template<typename Return, typename... Arguments>
void disguised_caller(Return(*)(Arguments...), framework::member * _destination);

template<typename Class>
void disguised_caller(void(Class::*_function)(), Class * _instance, framework::member * _destination);

template<typename Class>
void disguised_caller(void(Class::*_function)() const, const Class * _instance, framework::member * _destination);

template<typename Return, typename Class>
void disguised_caller(Return(Class::*_function)(), Class * _instance, framework::member * _destination);

template<typename Return, typename Class>
void disguised_caller(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination);

template<typename Return, typename Class, typename... Arguments>
void disguised_caller(Return(Class::*)(Arguments...), Class * _instance, framework::member * _destination);

template<typename Return, typename Class, typename... Arguments>
void disguised_caller(Return(Class::*)(Arguments...) const, const Class * _instance, framework::member * _destination);

template<typename Class>
machine::memory::allocation<Class> disguised_caller();

template<typename Class, typename... Arguments>
typename std::enable_if<(sizeof...(Arguments) > 0), machine::memory::allocation<Class>>::type disguised_caller();

""")
f.write(b"""#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "disguised_caller.hpp"
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

template<typename Return>
inline Return format_cast(va_list_wrapper & _args, const char *& _format)
{
	using namespace utility;
	using Real_return = typename std::remove_reference<Return>::type;

gt_redo:;

	switch (*_format++)
	{
	case 'i':
	{
		constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

		if (is_number) {
			return chooser<is_number, Return, int32_t>::choose(va_arg(_args.args, int32_t));
		} else {
			break;
		}
	}
	case 'I':
	{
		constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

		if (is_number) {
			return chooser<is_number, Return, int64_t>().choose(va_arg(_args.args, int64_t));
		} else {
			break;
		}
	}
	case 'd':
	{
		constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

		if (is_number) {
			auto _value = va_arg(_args.args, int64_t);

			return chooser<is_number, Return, double>().choose(*reinterpret_cast<double*>(&_value));
		} else {
			break;
		}
	}
	case 'a':
	{
		constexpr auto is_string = std::is_same<Real_return, const char*>::value;

		if (is_string) {
			return chooser<is_string, Return, const char*>().choose(va_arg(_args.args, const char*));
		} else {
			break;
		}
	}
	case 'M':
		return va_arg(_args.args, framework::member*)->cast<Return>();
	case 'r':
		va_arg(_args.args, void*);

		goto gt_redo;
	default:
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
	}

	throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
}

inline void disguised_caller(void(*_function)(), framework::member * _destination)
{
	_function();

	framework::create_member(_destination);
}

template<typename Return>
inline void disguised_caller(Return(*_function)(), framework::member * _destination)
{
	framework::create_member(_destination, _function());
}

template<typename Return, typename... Arguments>
inline void disguised_caller(Return(*)(Arguments...), framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Class>
inline void disguised_caller(void(Class::*_function)(), Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class>
inline void disguised_caller(void(Class::*_function)() const, const Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Return, typename Class>
inline void disguised_caller(Return(Class::*_function)(), Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Return, typename Class>
inline void disguised_caller(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Return, typename Class, typename... Arguments>
inline void disguised_caller(Return(Class::*)(Arguments...), Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Return, typename Class, typename... Arguments>
inline void disguised_caller(Return(Class::*)(Arguments...) const, const Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Class>
inline machine::memory::allocation<Class> disguised_caller()
{
	return machine::machine_context::active_allocator()->construct<Class>();
}

template<typename Class, typename... Arguments>
inline typename std::enable_if<(sizeof...(Arguments) > 0), machine::memory::allocation<Class>>::type disguised_caller()
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

""")

for type in ["count", "format"]:
	upper = {}

	if type == "count":
		upper["function_name"] = "disguised_caller_count"
		upper["format_param"] = ""
	else:
		upper["function_name"] = "disguised_caller_format"
		upper["format_param"] = "const char * _format, "
		
	upper["pre_preparations"] = ""
	upper["preparations"] = ""	
	upper["post_preparations"] = ""

	for template in ["static", "static_void", "member", "member_void", "member_const", "member_void_const", "initiator"]:
		filler = upper.copy()

		if template == "static":
			filler["template_begin"] = "template<typename Return"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "Return(*_function)("
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
			filler["template_begin"] = "template<typename Class, typename Return"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "Return(Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = "), Class * _instance, framework::member * _destination, "
			filler["body1"] = "framework::create_member(_destination, (_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "member_void":
			filler["template_begin"] = "template<typename Class"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "void(Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = "), Class * _instance, framework::member * _destination, "
			filler["body1"] = "(_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::create_member(_destination);"""
		elif template == "member_const":
			filler["template_begin"] = "template<typename Class, typename Return"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "Return(Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = ") const, const Class * _instance, framework::member * _destination, "
			filler["body1"] = "framework::create_member(_destination, (_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "member_void_const":
			filler["template_begin"] = "template<typename Class"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "void(Class::*_function)("
			filler["param2"] = ""
			filler["param3"] = ") const, const Class * _instance, framework::member * _destination, "
			filler["body1"] = "(_instance->*_function)("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::create_member(_destination);"""
		elif template == "initiator":
			filler["template_begin"] = "template<typename Class"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "machine::memory::allocation<Class>"
			filler["param1"] = ""
			filler["param2"] = ""
			filler["param3"] = ""
			filler["body1"] = "return machine::machine_context::active_allocator()->construct<Class>("
			filler["body2"] = ""
			filler["body3"] = ");"

		for i in range(0, max_args + 1):
			filler["arg_count"] = i

			h.write("""{template_begin}{template_middle}{template_end}
{function_return} {function_name}({param1}{param2}{param3}{format_param}framework::member::parameter_count _count, va_list_wrapper & _args);

""".format(**filler).encode())
			f.write("""{template_begin}{template_middle}{template_end}
inline {function_return} {function_name}({param1}{param2}{param3}{format_param}framework::member::parameter_count _count, va_list_wrapper & _args)
{{
	if (_count != {arg_count}) {{
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}}
#if defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG)){pre_preparations}
#endif
	{preparations}
#if !(defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))){post_preparations}
#endif

	{body1}{body2}{body3}
}}

""".format(**filler).encode())

			filler["template_middle"] += ("" if not filler["template_begin"] else ", ") + "typename _" + str(i)

			if template != "initiator":
				filler["param2"] += (", " if i != 0 else "") + "_" + str(i)

			if type == "count":
				filler["body2"] += (", " if i != 0 else "") + "_v{0}".format(i)
				preptmp = """
	typename framework::converter<_{0}>::type _v{0} = va_arg(_args.args, framework::member*)->cast<_{0}>();""".format(i)
			else:
				preptmp = """
	_{0} _v{0} = format_cast<_{0}>(_args, _format);""".format(i)
				filler["body2"] += (", " if i != 0 else "") + "std::forward<_{0}>(_v{0})".format(i)

			if i < 2:
				filler["pre_preparations"] += preptmp
				filler["post_preparations"] = preptmp + filler["post_preparations"]
			else:
				filler["preparations"] = preptmp + filler["preparations"]
				
			if template == "static_void":
				filler["template_begin"] = "template<"
				filler["template_end"] = ">"

h.write(b"}\n}")
f.write(b"}\n}")
h.close()
f.close()
