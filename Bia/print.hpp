#pragma once

#include <cstdio>
#include <cstdint>

#include "config.hpp"


namespace bia
{
namespace machine
{
namespace link
{

inline BIA_STATIC_CALLING_CONVETION(void, print_i(int32_t _value))
{
	printf("%i\n", _value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print_I(int64_t _value))
{
	printf("%lli\n", _value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print_true())
{
	puts("true");
}

inline BIA_STATIC_CALLING_CONVETION(void, print_false())
{
	puts("false");
}

inline BIA_STATIC_CALLING_CONVETION(void, print_b(int32_t _value))
{
	if (_value) {
		print_true();
	} else {
		print_false();
	}
}

inline BIA_STATIC_CALLING_CONVETION(void, print_d(double _value))
{
	printf("%f\n", _value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print_s(const char * _string))
{
	puts(_string);
}
inline BIA_STATIC_CALLING_CONVETION(void, print(int64_t _value))
{
	print_I(_value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print(double _value))
{
	print_d(_value);
}

template<typename _Ty>
inline BIA_STATIC_CALLING_CONVETION(void, print(_Ty))
{
	printf("%s\n", typeid(_Ty).name());
}

}
}
}