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

inline void BIA_STATIC_CALLING_CONVETION print_int32(int32_t _value)
{
	printf("%i\n", _value);
}

inline void BIA_STATIC_CALLING_CONVETION print_int64(int64_t _value)
{
	printf("%lli\n", _value);
}

inline void BIA_STATIC_CALLING_CONVETION print_true()
{
	puts("true");
}

inline void BIA_STATIC_CALLING_CONVETION print_false()
{
	puts("false");
}

inline void BIA_STATIC_CALLING_CONVETION print_bool(int32_t _value)
{
	if (_value) {
		print_true();
	} else {
		print_false();
	}
}

inline void BIA_STATIC_CALLING_CONVETION print_double(double _value)
{
	printf("%f\n", _value);
}

inline void BIA_STATIC_CALLING_CONVETION print_string(const char * _string)
{
	puts(_string);
}

inline void BIA_STATIC_CALLING_CONVETION print(int64_t _value)
{
	print_int64(_value);
}

inline void BIA_STATIC_CALLING_CONVETION print(double _value)
{
	print_double(_value);
}

template<typename _Ty>
inline void BIA_STATIC_CALLING_CONVETION print(_Ty)
{
	printf("%s\n", typeid(_Ty).name());
}

}
}
}