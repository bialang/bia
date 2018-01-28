max_args = 50

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

#Static functions
for i in range(0, max_args + 1):
    f.write(b"template<typename _RETURN")

    for x in range(0, i):
        f.write(", typename _{0}".format(x).encode())

    f.write(b""">
inline void DisguisedCallerCount(_RETURN(*p_pFunction)(""")

    for x in range(0, i):
        f.write("_{0}".format(x).encode())

        if x + 1 < i:
            f.write(b", ")
    
    f.write("""), framework::BiaMember * p_pDestination, uint32_t p_unCount, va_list p_args)
{{
    if (p_unCount != {0})
        throw exception::ArgumentException("Argument count is invalid.");

""".format(i).encode())

    #Call function
    f.write(b"\tp_pFunction(")

    for x in range(0, i):
        f.write("std::forward<_{0}>(*reinterpret_cast<framework::BiaMember*>(p_args".format(x).encode())

        if x != 0:
            f.write(" + sizeof(framework::BiaMember*) * {0}".format(x).encode())

        f.write(")->Cast<_{0}>())".format(x).encode())

        if x + 1 < i:
            f.write(b", ")

    f.write(b""");
}

""")