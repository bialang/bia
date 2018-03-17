max_args = 3

f = open("disguised.txt", "wb")

f.write(b"""template<typename _RETURN>
inline _RETURN FormatCast(va_list & p_args, const char *& p_szFormat)
{
	using namespace utility;

	switch (*p_szFormat++)
	{
	case 'i':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return Chooser<NUMBER, _RETURN, int32_t>().Choose(va_arg(p_args, int32_t));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'I':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return Chooser<NUMBER, _RETURN, int64_t>().Choose(va_arg(p_args, int64_t));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'f':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return Chooser<NUMBER, _RETURN, float>().Choose(va_arg(p_args, float));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'd':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return Chooser<NUMBER, _RETURN, double>().Choose(va_arg(p_args, double));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 's':
	{
		constexpr auto STRING = std::is_same<_RETURN, const char*>::value;

		if (STRING)
			return Chooser<STRING, _RETURN, const char*>().Choose(va_arg(p_args, const char*));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'M':
	{
		if (auto pValue = va_arg(p_args, framework::BiaMember*)->Cast<_RETURN>())
			return *pValue;
		else
			throw exception::BadCastException("Invalid cast.");
	}
	default:
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
	}
}

inline void DisguisedCaller(void(*p_pFunction)(), framework::BiaMember * p_pDestination)
{
	p_pFunction();

	framework::MemberCreator(p_pDestination);
}

template<typename _RETURN>
inline void DisguisedCaller(_RETURN(*p_pFunction)(), framework::BiaMember * p_pDestination)
{
	framework::MemberCreator(p_pDestination, p_pFunction());
}

template<typename _RETURN, typename... _ARGS>
inline void DisguisedCaller(_RETURN(*)(_ARGS...), framework::BiaMember*)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _CLASS>
inline void DisguisedCaller(void(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS>
inline void DisguisedCaller(void(_CLASS::*p_pFunction)() const, _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCaller(_RETURN(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCaller(_RETURN(_CLASS::*p_pFunction)() const, _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS, typename... _ARGS>
inline void DisguisedCaller(_RETURN(_CLASS::*)(_ARGS...), _CLASS*, framework::BiaMember*)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _RETURN, typename _CLASS, typename... _ARGS>
inline void DisguisedCaller(_RETURN(_CLASS::*)(_ARGS...) const, _CLASS*, framework::BiaMember*)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _CLASS>
inline _CLASS * DisguisedCaller()
{
	return new _CLASS();
}

template<typename _CLASS, typename... _ARGS>
inline _CLASS * DisguisedCaller()
{
	throw exception::ArgumentException("Arguments expected.");
}

""")

for type in ["count", "format"]:
	upper = {}

	if type == "count":
		upper["function_name"] = "DisguisedCallerCount"
		upper["preparations"] = ""
		upper["format_param"] = ""
	else:
		upper["function_name"] = "DisguisedCallerFormat"
		upper["preparations"] = ""
		upper["format_param"] = ", const char * p_pcFormat"

	for template in ["static", "static_void", "member", "member_void", "member_const", "member_void_const", "initiator"]:
		filler = upper.copy()

		if template == "static":
			filler["template_begin"] = "template<typename _RETURN"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "_RETURN(*p_pFunction)("
			filler["param2"] = ""
			filler["param3"] = "), framework::BiaMember * p_pDestination, "
			filler["body1"] = "framework::MemberCreator(p_pDestination, p_pFunction("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "static_void":
			filler["template_begin"] = ""
			filler["template_middle"] = ""
			filler["template_end"] = ""
			filler["function_return"] = "void"
			filler["param1"] = "void(*p_pFunction)("
			filler["param2"] = ""
			filler["param3"] = "), framework::BiaMember * p_pDestination, "
			filler["body1"] = "p_pFunction("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::MemberCreator(p_pDestination);"""
		elif template == "member":
			filler["template_begin"] = "template<typename _CLASS, typename _RETURN"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "_RETURN(_CLASS::*p_pFunction)("
			filler["param2"] = ""
			filler["param3"] = "), _CLASS * p_pFunction, framework::BiaMember * p_pDestination, "
			filler["body1"] = "framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "member_void":
			filler["template_begin"] = "template<typename _CLASS"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "void(_CLASS::*p_pFunction)("
			filler["param2"] = ""
			filler["param3"] = "), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, "
			filler["body1"] = "(p_pInstance->*p_pFunction)("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::MemberCreator(p_pDestination);"""
		elif template == "member_const":
			filler["template_begin"] = "template<typename _CLASS, typename _RETURN"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "_RETURN(_CLASS::*p_pFunction)("
			filler["param2"] = ""
			filler["param3"] = ") const, const _CLASS * p_pFunction, framework::BiaMember * p_pDestination, "
			filler["body1"] = "framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)("
			filler["body2"] = ""
			filler["body3"] = "));"
		elif template == "member_void_const":
			filler["template_begin"] = "template<typename _CLASS"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "void"
			filler["param1"] = "void(_CLASS::*p_pFunction)("
			filler["param2"] = ""
			filler["param3"] = ") const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, "
			filler["body1"] = "(p_pInstance->*p_pFunction)("
			filler["body2"] = ""
			filler["body3"] = """);

	framework::MemberCreator(p_pDestination);"""
		elif template == "initiator":
			filler["template_begin"] = "template<typename _CLASS"
			filler["template_middle"] = ""
			filler["template_end"] = ">"
			filler["function_return"] = "_CLASS *"
			filler["param1"] = ""
			filler["param2"] = ""
			filler["param3"] = ""
			filler["body1"] = "return new _CLASS("
			filler["body2"] = ""
			filler["body3"] = ");"

		for i in range(0, max_args + 1):
			filler["arg_count"] = i

			f.write("""{template_begin}{template_middle}{template_end}
inline {function_return} {function_name}({param1}{param2}{param3}framework::BiaMember::parameter_count p_count{format_param}, va_list p_args)
{{
	if (p_count != {arg_count})
		throw exception::ArgumentException("Argument count does not match.");
{preparations}
	{body1}{body2}{body3}
}}

""".format(**filler).encode())

			filler["template_middle"] += ("" if not filler["template_begin"] else ", ") + "typename _" + str(i)
			
			if template != "initiator":
				filler["param2"] += (", " if i != 0 else "") + "_" + str(i)
			
			filler["body2"] += (", " if i != 0 else "") + "std::forward<_{0}>(v{0})".format(i)

			if type == "count":
				filler["preparations"] = """
	_{0} v{0} = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * {0}))->Cast<_{0}>();""".format(i) + filler["preparations"]
			else:
				filler["preparations"] = """
	_{0} v{0} = FormatCast<_{0}>(p_args, p_pcFormat);""".format(i) + filler["preparations"]
			
			if template == "static_void":
				filler["template_begin"] = "template<"
				filler["template_end"] = ">"

f.close()
