#include "instantiate.hpp"
#include "native_member.hpp"
#include "cstring_member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, instantiate_int32(int32_t _value, framework::member *_destination))
{
	_destination->replace_this<framework::native::int_member>(_value);
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int64(int64_t _value, framework::member *_destination))
{
	_destination->replace_this<framework::native::int_member>(_value);
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int_0(framework::member *_destination))
{
	_destination->replace_this<framework::native::int_member>(0);
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int_1(framework::member *_destination))
{
	_destination->replace_this<framework::native::int_member>(1);
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int_n1(framework::member *_destination))
{
	_destination->replace_this<framework::native::int_member>(-1);
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_double(double _value, framework::member *_destination))
{
	_destination->replace_this<framework::native::double_member>(_value);
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_string(const char *_string, size_t _length, framework::member *_destination))
{
	_destination->replace_this<framework::native::cstring_member>(_string, _length);
}

}
}
}