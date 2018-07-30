#include "operation.hpp"
#include "native_member.hpp"
#include "native_operator.hpp"
#include "native_test_operator.hpp"


namespace bia
{
namespace machine
{
namespace link
{

BIA_STATIC_CALLING_CONVETION(void, operation_int32(int32_t _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right))
{
	auto _flags = _right->flags();

	if (_flags & framework::member::F_INT) {
		_destination->replace_this<framework::native::int_member>(framework::native::operation_chooser_l<int32_t>::operate_result(_left, _operator, _right->to_int()));
	} else if (_flags & framework::member::F_DOUBLE) {
		_destination->replace_this<framework::native::double_member>(framework::native::operation_chooser_l<int32_t>::operate_result(_left, _operator, _right->to_double()));
	}
}

BIA_STATIC_CALLING_CONVETION(void, operation_int64(int64_t _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right))
{
}

BIA_STATIC_CALLING_CONVETION(void, operation_double(double _left, framework::member * _destination, framework::operator_type _operator, framework::member * _right))
{
	//return framework::native::(_left, _operator, _right->to_double());
}

BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_int32(int32_t _left, framework::operator_type _operator, framework::member *_right))
{
	return framework::native::test_operation(_left, _operator, _right->to_int());
}

BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_int64(int64_t _left, framework::operator_type _operator, framework::member *_right))
{
	return framework::native::test_operation(_left, _operator, _right->to_int());
}

BIA_STATIC_CALLING_CONVETION(int32_t, compare_operation_double(double _left, framework::operator_type _operator, framework::member *_right))
{
	return framework::native::test_operation(_left, _operator, _right->to_double());
}

}
}
}