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

inline BIA_STATIC_CALLING_CONVETION(void, print_int32(int32_t _value))
{
	printf("%i\n", _value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print_int64(int64_t _value))
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

inline BIA_STATIC_CALLING_CONVETION(void, print_bool(int32_t _value))
{
	if (_value) {
		print_true();
	} else {
		print_false();
	}
}

inline BIA_STATIC_CALLING_CONVETION(void, print_double(double _value))
{
	printf("%f\n", _value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print_string(const char * _string))
{
	puts(_string);
}

inline BIA_STATIC_CALLING_CONVETION(void, print(int64_t _value))
{
	print_int64(_value);
}

inline BIA_STATIC_CALLING_CONVETION(void, print(double _value))
{
	print_double(_value);
}

template<typename _Ty>
inline BIA_STATIC_CALLING_CONVETION(void, print(_Ty))
{
	printf("%s\n", typeid(_Ty).name());
}

}
}
}