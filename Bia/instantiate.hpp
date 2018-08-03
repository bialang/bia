#pragma once

#include <cstdint>
#include <cstddef>

#include "config.hpp"
#include "member.hpp"
#include "cstring_member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, instantiate_int32(int32_t _value, framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int64(int64_t _value, framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_0(framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_1(framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_n1(framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_double(double _value, framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_string(const char *_string, framework::native::cstring_member<char>::size_type _size, framework::native::cstring_member<char>::length_type _length, framework::member *_destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_string16(const char16_t *_string, framework::native::cstring_member<char16_t>::size_type _size, framework::native::cstring_member<char16_t>::length_type _length, framework::member *_destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_string32(const char32_t *_string, framework::native::cstring_member<char32_t>::size_type _size, framework::native::cstring_member<char32_t>::length_type _length, framework::member *_destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_wstring(const wchar_t *_string, framework::native::cstring_member<wchar_t>::size_type _size, framework::native::cstring_member<wchar_t>::length_type _length, framework::member *_destination));

}
}
}