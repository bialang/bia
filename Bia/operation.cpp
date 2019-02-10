#include "operation.hpp"
#include "big_int_member.hpp"
#include "double_member.hpp"
#include "native_operator.hpp"
#include "native_test_operator.hpp"


namespace bia
{
namespace machine
{
namespace link
{

void BIA_STATIC_CALLING_CONVETION operation_int32(framework::member * _destination, framework::operator_t _operator, framework::member * _right, int32_t _left)
{
	BIA_NOT_IMPLEMENTED;
	/*auto _flags = _right->flags();

	if (_flags & framework::member::F_INT) {
		_destination->replace_this<framework::native::big_int_member>(framework::native::operation_chooser_l<int32_t>::operate_result(_left, _operator, _right->to_int()));
	} else if (_flags & framework::member::F_DOUBLE) {
		_destination->replace_this<framework::native::double_member>(framework::native::operation_chooser_l<int32_t>::operate_result(_left, _operator, _right->to_double()));
	}*/
}

void BIA_STATIC_CALLING_CONVETION operation_int64(framework::member * _destination, framework::operator_t _operator, framework::member * _right, int64_t _left)
{
}

void BIA_STATIC_CALLING_CONVETION operation_double(framework::member * _destination, framework::operator_t _operator, framework::member * _right, double _left)
{
	//return framework::native::(_left, _operator, _right->to_double());
}

int32_t BIA_STATIC_CALLING_CONVETION compare_operation_int32(framework::operator_t _operator, framework::member *_right, int32_t _left)
{
	return framework::native::test_operation(_left, _operator, _right->to_int());
}

int32_t BIA_STATIC_CALLING_CONVETION compare_operation_int64(framework::operator_t _operator, framework::member *_right, int64_t _left)
{
	return framework::native::test_operation(_left, _operator, _right->to_int());
}

int32_t BIA_STATIC_CALLING_CONVETION compare_operation_double(framework::operator_t _operator, framework::member *_right, double _left)
{
	return framework::native::test_operation(_left, _operator, _right->to_double());
}

}
}
}