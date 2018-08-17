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

void BIA_STATIC_CALLING_CONVETION operation_int32(framework::member * _destination, framework::operator_type _operator, framework::member * _right, int32_t _left);
void BIA_STATIC_CALLING_CONVETION operation_int64(framework::member * _destination, framework::operator_type _operator, framework::member * _right, int64_t _left);
void BIA_STATIC_CALLING_CONVETION operation_double(framework::member * _destination, framework::operator_type _operator, framework::member * _right, double _left);
int32_t BIA_STATIC_CALLING_CONVETION compare_operation_int32(framework::operator_type _operator, framework::member * _right, int32_t _left);
int32_t BIA_STATIC_CALLING_CONVETION compare_operation_int64(framework::operator_type _operator, framework::member * _right, int64_t _left);
int32_t BIA_STATIC_CALLING_CONVETION compare_operation_double(framework::operator_type _operator, framework::member * _right, double _left);

}
}
}