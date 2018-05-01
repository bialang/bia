#include "instantiate.hpp"
#include "native_member.hpp"
#include "cstring_member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, instantiate_int32(BIA_PO_0_1_2(int32_t _value, framework::member *_destination)))
{
	_destination->replace_this<framework::native::int_member>(BIA_PO_0_1_1(_value));
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int64(BIA_PO_0_1_2(int64_t _value, framework::member *_destination)))
{
	_destination->replace_this<framework::native::int_member>(BIA_PO_0_1_1(_value));
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int_0(BIA_PO_0_1_1(framework::member *_destination)))
{
	_destination->replace_this<framework::native::int_member>(BIA_PO_0_1_1(0));
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int_1(BIA_PO_0_1_1(framework::member *_destination)))
{
	_destination->replace_this<framework::native::int_member>(BIA_PO_0_1_1(1));
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_int_n1(BIA_PO_0_1_1(framework::member *_destination)))
{
	_destination->replace_this<framework::native::int_member>(BIA_PO_0_1_1(-1));
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_double(BIA_PO_0_1_2(double _value, framework::member *_destination)))
{
	_destination->replace_this<framework::native::double_member>(BIA_PO_0_1_1(_value));
}

BIA_STATIC_CALLING_CONVETION(void, instantiate_string(BIA_PO_0_2_3(const char *_string, size_t _length, framework::member *_destination)))
{
	_destination->replace_this<framework::native::cstring_member>(BIA_PO_0_2_2(_string, _length));
}

}
}
}