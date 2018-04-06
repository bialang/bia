#pragma once

#include <cstring>

#include "test.hpp"


inline void static_order1(const char * a, const char * b)
{
	BIA_ASSERT(std::strcmp(a, "a") == 0, "Strings don't match");
	BIA_ASSERT(std::strcmp(b, "b") == 0, "Strings don't match");
}

inline void static_order2(const char * a, const char * b, const char * c)
{
	BIA_ASSERT(std::strcmp(a, "a") == 0, "Strings don't match");
	BIA_ASSERT(std::strcmp(b, "b") == 0, "Strings don't match");
	BIA_ASSERT(std::strcmp(c, "c") == 0, "Strings don't match");
}

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