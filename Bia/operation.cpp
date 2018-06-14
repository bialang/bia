#include "operation.hpp"
#include "native_member.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, operation_int32(int32_t _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right))
{
	// Create left
	framework::native::int_member _left_member(_left);

	_left_member.operator_call(_destination, _operator, _right);
}

BIA_STATIC_CALLING_CONVETION(void, operation_int64(int64_t _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right))
{
	// Create left
	framework::native::int_member _left_member(_left);

	_left_member.operator_call(_destination, _operator, _right);
}

BIA_STATIC_CALLING_CONVETION(void, operation_double(double _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right))
{
	// Create left
	framework::native::double_member _left_member(_left);

	_left_member.operator_call(_destination, _operator, _right);
}

BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_int32(int32_t _left, framework::operator_type _operator, framework::member *_right))
{
	// Create left
	framework::native::int_member _left_member(_left);

	return _left_member.test_member(_operator, _right);
}

BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_int64(int64_t _left, framework::operator_type _operator, framework::member *_right))
{
	// Create left
	framework::native::int_member _left_member(_left);

	return _left_member.test_member(_operator, _right);
}

BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_double(double _left, framework::operator_type _operator, framework::member *_right))
{
	// Create left
	framework::native::double_member _left_member(_left);

	return _left_member.test_member(_operator, _right);
}

}
}
}