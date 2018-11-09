#pragma once

#include <cstdint>
#include <cstddef>

#include "config.hpp"
#include "member.hpp"
#include "cstring_member.hpp"
#include "int_member.hpp"
#include "double_member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_int32(framework::member * _destination, int32_t _value);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_int64(framework::member * _destination, int64_t _value);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_big_int(framework::member * _destination, framework::native::int_member::int_type * _value);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_int_0(framework::member * _destination);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_int_1(framework::member * _destination);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_int_n1(framework::member * _destination);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_double(framework::member * _destination, double _value);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_big_double(framework::member * _destination, framework::native::double_member::double_type * _value);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_string(framework::member *_destination, const char *_string, framework::native::cstring_member<char>::size_type _size, framework::native::cstring_member<char>::length_type _length);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_string16(framework::member *_destination, const char16_t *_string, framework::native::cstring_member<char16_t>::size_type _size, framework::native::cstring_member<char16_t>::length_type _length);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_string32(framework::member *_destination, const char32_t *_string, framework::native::cstring_member<char32_t>::size_type _size, framework::native::cstring_member<char32_t>::length_type _length);
BIA_EXPORT void BIA_STATIC_CALLING_CONVETION instantiate_wstring(framework::member *_destination, const wchar_t *_string, framework::native::cstring_member<wchar_t>::size_type _size, framework::native::cstring_member<wchar_t>::length_type _length);

}
}
}