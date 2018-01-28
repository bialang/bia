max_args = 3

f = open("disguised.txt", "wb")

f.write(b"""inline void DisguisedCaller(void(*p_pFunction)(), framework::BiaMember*)
{
    p_pFunction();
}

template<typename _RETURN>
inline void DisguisedCaller(_RETURN(*p_pFunction)(), framework::BiaMember * p_pDestination)
{
    p_pFunction();
}

template<typename _RETURN, typename... _ARGS>
inline void DisguisedCaller(_RETURN(*)(_ARGS...), framework::BiaMember*)
{
    throw exception::ArgumentException("Arguments expected.");
}

""")

for template in ["static", "static_void"]:
    filler = {}

    if template == "static":
        filler["template_begin"] = "template<typename _RETURN"
        filler["template_end"] = ">"
        filler["return"] = "_RETURN"
    elif template == "static_void":
        filler["template_begin"] = ""
        filler["template_end"] = ""
        filler["return"] = "void"
        
    filler["args"] = ""
    filler["arg_count"] = 0
    filler["arg_pass"] = ""
    filler["template_middle"] = ""

    for i in range(0, max_args + 1):

        f.write("""{template_begin}{template_middle}{template_end}
inline void DisguisedCallerCount({return}(*p_pFunction)({args}), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{{
    if (p_count != {arg_count})
        throw exception::ArgumentException("Argument count does not match.");

    p_pFunction({arg_pass});
}}

""".format(**filler).encode())

        filler["arg_count"] += 1
        filler["arg_pass"] += (", " if i != 0 else "") + "std::forward<_{0}>(*(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * {0}))->Cast<_{0}>())".format(i)
        filler["args"] += (", " if i != 0 else "") + "_" + str(i)
        filler["template_middle"] += (", " if i != 0 or template == "static" else "") + "typename _" + str(i)

        if template == "static_void":
            filler["template_begin"] = "template<"
            filler["template_end"] = ">"
