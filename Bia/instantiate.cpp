#include "instantiate.hpp"
#include "int_member.hpp"
#include "big_int_member.hpp"
#include "double_member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

void BIA_STATIC_CALLING_CONVETION instantiate_int32(framework::member *_destination, int32_t _value)
{
	_destination->replace_this<framework::native::int_member>(_value);
}

void BIA_STATIC_CALLING_CONVETION instantiate_int64(framework::member *_destination, int64_t _value)
{
	_destination->replace_this<framework::native::int_member>(_value);
}

void BIA_STATIC_CALLING_CONVETION instantiate_big_int(framework::member * _destination, dependency::big_int * _value)
{
	_destination->replace_this<framework::native::big_int_member>(*_value);
}

void BIA_STATIC_CALLING_CONVETION instantiate_int_0(framework::member *_destination)
{
	_destination->replace_this<framework::native::int_member>(0);
}

void BIA_STATIC_CALLING_CONVETION instantiate_int_1(framework::member *_destination)
{
	_destination->replace_this<framework::native::int_member>(1);
}

void BIA_STATIC_CALLING_CONVETION instantiate_int_n1(framework::member *_destination)
{
	_destination->replace_this<framework::native::int_member>(-1);
}

void BIA_STATIC_CALLING_CONVETION instantiate_double(framework::member *_destination, double _value)
{
	_destination->replace_this<framework::native::double_member>(_value);
}

void BIA_STATIC_CALLING_CONVETION instantiate_string(framework::member *_destination, const char *_string, framework::native::cstring_member<char>::size_type _size, framework::native::cstring_member<char>::length_type _length)
{
	_destination->replace_this<framework::native::cstring_member<char>>(_string, _size, _length);
}

void BIA_STATIC_CALLING_CONVETION instantiate_string16(framework::member *_destination, const char16_t *_string, framework::native::cstring_member<char16_t>::size_type _size, framework::native::cstring_member<char16_t>::length_type _length)
{
	_destination->replace_this<framework::native::cstring_member<char16_t>>(_string, _size, _length);
}

void BIA_STATIC_CALLING_CONVETION instantiate_string32(framework::member *_destination, const char32_t *_string, framework::native::cstring_member<char32_t>::size_type _size, framework::native::cstring_member<char32_t>::length_type _length)
{
	_destination->replace_this<framework::native::cstring_member<char32_t>>(_string, _size, _length);
}

void BIA_STATIC_CALLING_CONVETION instantiate_wstring(framework::member *_destination, const wchar_t *_string, framework::native::cstring_member<wchar_t>::size_type _size, framework::native::cstring_member<wchar_t>::length_type _length)
{
	_destination->replace_this<framework::native::cstring_member<wchar_t>>(_string, _size, _length);
}

}
}
}