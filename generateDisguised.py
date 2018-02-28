max_args = 3

f = open("disguised.txt", "wb")

f.write(b"""template<typename _RETURN>
inline _RETURN FormatCast(va_list & p_args, const char *& p_szFormat)
{
	switch (*p_szFormat++)
	{
	case 'i':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, int32_t>::type>(va_arg(p_args, int32_t));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'I':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, int64_t>::type>(va_arg(p_args, int64_t));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'f':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, float>::type>(va_arg(p_args, float));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'd':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, double>::type>(va_arg(p_args, double));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 's':
	{
		if (std::is_same<_RETURN, const char*>::value)
			return reinterpret_cast<_RETURN>(va_arg(p_args, const char*));
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

	for template in ["static", "static_void", "member_void", "member_void_const", "member", "member_const"]:
		filler = upper.copy()

		if template == "static":
			filler["template_begin"] = "template<typename _RETURN"
			filler["template_end"] = ">"
			filler["return"] = "_RETURN"
			filler["pre_call"] = "framework::MemberCreator(p_pDestination, "
			filler["post_call"] = ")"
			filler["post_function"] = ""
			filler["instance_arg"] = ""
			filler["class_signature"] = ""
		elif template == "static_void":
			filler["template_begin"] = ""
			filler["template_end"] = ""
			filler["return"] = "void"
			filler["pre_call"] = ""
			filler["post_call"] = """;

	framework::MemberCreator(p_pDestination)"""
			filler["post_function"] = ""
			filler["instance_arg"] = ""
			filler["class_signature"] = ""
		elif template.startswith("member_void"):
			filler["template_begin"] = "template<typename _CLASS"
			filler["template_end"] = ">"
			filler["return"] = "void"
			filler["pre_call"] = "(p_pInstance->*"
			filler["post_call"] = """;

	framework::MemberCreator(p_pDestination)"""
			filler["post_function"] = ")"
			filler["instance_arg"] = (" const, const" if template == "member_void_const" else ",") + " _CLASS * p_pInstance"
			filler["class_signature"] = "_CLASS::"
		elif template.startswith("member"):
			filler["template_begin"] = "template<typename _RETURN, typename _CLASS"
			filler["template_end"] = ">"
			filler["return"] = "_RETURN"
			filler["pre_call"] = "framework::MemberCreator(p_pDestination, (p_pInstance->*"
			filler["post_call"] = ")"
			filler["post_function"] = ")"
			filler["instance_arg"] = (" const, const" if template == "member_const" else ",") + " _CLASS * p_pInstance"
			filler["class_signature"] = "_CLASS::"
			
		filler["args"] = ""
		filler["arg_count"] = 0
		filler["arg_pass"] = ""
		filler["template_middle"] = ""

		for i in range(0, max_args + 1):
			f.write("""{template_begin}{template_middle}{template_end}
inline void {function_name}({return}({class_signature}*p_pFunction)({args}){instance_arg}, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count{format_param}, va_list p_args)
{{
	if (p_count != {arg_count})
		throw exception::ArgumentException("Argument count does not match.");
{preparations}

	{pre_call}p_pFunction{post_function}({arg_pass}){post_call};
}}

""".format(**filler).encode())

			filler["arg_count"] += 1
			filler["arg_pass"] += (", " if i != 0 else "") + "std::forward<_{0}>(v{0})".format(i)
			filler["args"] += (", " if i != 0 else "") + "_" + str(i)
			filler["template_middle"] += ("" if not filler["template_begin"] else ", ") + "typename _" + str(i)

			if type == "count":
				filler["preparations"] += """
	_{0} v{0} = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * {0}))->Cast<_{0}>();""".format(i)
			else:
				filler["preparations"] += """
	_{0} v{0} = FormatCast<_{0}>(p_args, p_pcFormat);""".format(i)
			
			if template == "static_void":
				filler["template_begin"] = "template<"
				filler["template_end"] = ">"

f.close()
