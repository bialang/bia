#pragma once

#include <cstdint>
#include <cstddef>

#include "config.hpp"
#include "member.hpp"
#include "parameter_order.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, instantiate_int32(BIA_PO_0_1_2(int32_t _value, framework::member * _destination)));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int64(BIA_PO_0_1_2(int64_t _value, framework::member * _destination)));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_0(BIA_PO_0_1_1(framework::member * _destination)));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_1(BIA_PO_0_1_1(framework::member * _destination)));
BIA_STATIC_CALLING_CONVETION(void, instantiate_int_n1(BIA_PO_0_1_1(framework::member * _destination)));
BIA_STATIC_CALLING_CONVETION(void, instantiate_double(BIA_PO_0_1_2(double _value, framework::member * _destination)));
BIA_STATIC_CALLING_CONVETION(void, instantiate_string(BIA_PO_0_2_3(const char *_string, size_t _length, framework::member *_destination)));

}
}
}