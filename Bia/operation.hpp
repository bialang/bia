#pragma once

#include <cstdint>

#include "config.hpp"
#include "member.hpp"
#include "operator.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, operation_int32(int32_t _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right));
BIA_STATIC_CALLING_CONVETION(void, operation_int64(int64_t _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right));
BIA_STATIC_CALLING_CONVETION(void, operation_double(double _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right));
BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_int32(int32_t _left, framework::operator_type _operator, framework::member * _right));
BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_int64(int64_t _left, framework::operator_type _operator, framework::member * _right));
BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_double(double _left, framework::operator_type _operator, framework::member * _right));

}
}
}