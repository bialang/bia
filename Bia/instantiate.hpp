#pragma once

#include <cstdint>

#include "config.hpp"
#include "member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, instantiate_int32(framework::member * _destination, int32_t _value));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int64(framework::member * _destination, int64_t _value));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_0(framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_1(framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_n1(framework::member * _destination));
BIA_STATIC_CALLING_CONVETION(void, instantiate_float(framework::member * _destination, float _value));
BIA_STATIC_CALLING_CONVETION(void, instantiate_double(framework::member * _destination, double _value));
BIA_STATIC_CALLING_CONVETION(void, instantiate_string(framework::member * _destination, const char * _string));

}
}
}