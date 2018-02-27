max_args = 3

f = open("disguised.txt", "wb")

f.write(b"""inline void DisguisedCaller(void(*p_pFunction)(), framework::BiaMember * p_pDestination)
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

for template in ["static", "static_void", "member_void", "member_void_const", "member", "member_const"]:
	filler = {}

	if template == "static":
		filler["template_begin"] = "template<typename _RETURN"
		filler["template_end"] = ">"
		filler["return"] = "_RETURN"
		filler["pre_call"] = "framework::MemberCreator(p_pDestination, "
		filler["post_call"] = ")"
		filler["post_function"] = ""
		filler["instance_arg"] = ""
	elif template == "static_void":
		filler["template_begin"] = ""
		filler["template_end"] = ""
		filler["return"] = "void"
		filler["pre_call"] = ""
		filler["post_call"] = """;

	framework::MemberCreator(p_pDestination)"""
		filler["post_function"] = ""
		filler["instance_arg"] = ""
	elif template.startswith("member_void"):
		filler["template_begin"] = "template<typename _CLASS"
		filler["template_end"] = ">"
		filler["return"] = "void"
		filler["pre_call"] = "(p_pInstance->*"
		filler["post_call"] = """;

	framework::MemberCreator(p_pDestination)"""
		filler["post_function"] = ")"
		filler["instance_arg"] = (" const" if template == "member_void_const" else ",") + " _CLASS * p_pInstance"
	elif template.startswith("member"):
		filler["template_begin"] = "template<typename _RETURN, typename _CLASS"
		filler["template_end"] = ">"
		filler["return"] = "_RETURN"
		filler["pre_call"] = "framework::MemberCreator(p_pDestination, (p_pInstance->*"
		filler["post_call"] = ")"
		filler["post_function"] = ")"
		filler["instance_arg"] = (" const, const" if template == "member_const" else ",") + " _CLASS * p_pInstance"
		
	filler["args"] = ""
	filler["arg_count"] = 0
	filler["arg_pass"] = ""
	filler["template_middle"] = ""

	for i in range(0, max_args + 1):
		f.write("""{template_begin}{template_middle}{template_end}
inline void DisguisedCallerCount({return}(*p_pFunction)({args}){instance_arg}, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{{
	if (p_count != {arg_count})
		throw exception::ArgumentException("Argument count does not match.");

	{pre_call}p_pFunction{post_function}({arg_pass}){post_call};
}}

""".format(**filler).encode())

		filler["arg_count"] += 1
		filler["arg_pass"] += (", " if i != 0 else "") + "std::forward<_{0}>(*(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * {0}))->Cast<_{0}>())".format(i)
		filler["args"] += (", " if i != 0 else "") + "_" + str(i)
		filler["template_middle"] += ("" if not filler["template_begin"] else ", ") + "typename _" + str(i)

		if template == "static_void":
			filler["template_begin"] = "template<"
			filler["template_end"] = ">"

f.close()
