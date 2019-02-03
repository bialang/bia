import re

max_args = 20

h = open("Bia/disguised_caller.hpp", "wb")
f = open("Bia/disguised_caller_source.hpp", "wb")

h.write(b"""#pragma once

#include <cstdint>
#include <type_traits>

#include "member.hpp"
#include "stack.hpp"
#include "allocator.hpp"
#include "type_traits.hpp"


namespace bia
{
namespace force
{

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

#include <cstdint>
#include <type_traits>

#include "disguised_caller.hpp"
#include "exception.hpp"
#include "create_member.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace force
{

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
		
	upper["preparations"] = ""

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
{function_return} {function_name}({param1}{param2}{param3}{format_param}framework::member::parameter_count _count, machine::stack * _stack);

""".format(**filler).encode())
			f.write("""{template_begin}{template_middle}{template_end}
inline {function_return} {function_name}({param1}{param2}{param3}{format_param}framework::member::parameter_count _count, machine::stack * _stack)
{{
	constexpr auto _arg_count = {arg_count};

	if (_count != _arg_count) {{
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}}
{preparations}

	_stack->pop_count(_arg_count);

	{body1}{body2}{body3}
}}

""".format(**filler).encode())

			filler["template_middle"] += ("" if not filler["template_begin"] else ", ") + "typename _" + str(i)

			if template != "initiator":
				filler["param2"] += (", " if i != 0 else "") + "_" + str(i)

			if type == "count":
				filler["body2"] += (", " if i != 0 else "") + "_v{0}".format(i)
				preptmp = """
	typename framework::converter<_{0}>::type _v{0} = _stack->cast<framework::member*>({0} - _arg_count)->cast<_{0}>();""".format(i)
			else:
				preptmp = """
	_{0} _v{0} = _stack->format_cast<_{0}>({0} - _arg_count, *_format++);""".format(i)
				filler["body2"] += (", " if i != 0 else "") + "std::forward<_{0}>(_v{0})".format(i)

			filler["preparations"] = filler["preparations"] + preptmp
				
			if template == "static_void":
				filler["template_begin"] = "template<"
				filler["template_end"] = ">"

h.write(b"}\n}")
f.write(b"}\n}")
h.close()
f.close()
