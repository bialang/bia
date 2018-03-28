#pragma once

#include <cstring>


inline int foo1()
{
	return 61;
}

inline int foo2(const char * p_szString)
{
	return std::strcmp("hi", p_szString) ? 0 : -61;
}

inline int foo3(int a, int b)
{
	return a + b;
}

inline int(*foo4())(int, int)
{
	return &foo3;
}