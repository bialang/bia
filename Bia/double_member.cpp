#include "double_member.hpp"
#include "share.hpp"
#include "print.hpp"
#include "native_operator.hpp"
#include "native_test_operator.hpp"
#include "create_member.hpp"

#include <cstdio>


namespace bia
{
namespace framework
{
namespace native
{

double_member::double_member(double _value)
{
	_data.get() = _value;
}

double_member::double_member(const data_type & _data) noexcept : _data(_data)
{
}

void double_member::print() const
{
	machine::link::print(_data.get());
}

void double_member::copy(member * _destination)
{
	_destination->replace_this<double_member>(_data.get());
}

void double_member::refer(member * _destination)
{
	_destination->replace_this<double_member>(_data);
}

void double_member::clone(member * _destination)
{
	copy(_destination);
}

void double_member::operator_call(member * _destination, operator_t _operator, const member * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void double_member::operator_call_int32(member * _destination, operator_t _operator, int32_t _right)
{
	if (_destination == this) {
		native_operation<true>::operate_arithmetic(_data.get(), _operator, _right);
	} else {
		native_operation<true>::operate_arithmetic(_destination, _data.get(), _operator, _right);
	}
}

void double_member::operator_call_int64(member * _destination, operator_t _operator, int64_t _right)
{
	if (_destination == this) {
		native_operation<true>::operate_arithmetic(_data.get(), _operator, _right);
	} else {
		native_operation<true>::operate_arithmetic(_destination, _data.get(), _operator, _right);
	}
}

void BIA_MEMBER_CALLING_CONVENTION double_member::operator_call_big_int(member * _destination, operator_t _operator, const dependency::big_int * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void double_member::operator_call_double(member * _destination, operator_t _operator, double _right)
{
	if (_destination == this) {
		native_operation<true>::operate_arithmetic(_data.get(), _operator, _right);
	} else {
		native_operation<true>::operate_arithmetic(_destination, _data.get(), _operator, _right);
	}
}

void double_member::object_member(member * _destination, machine::name_manager::name_t _name)
{
	BIA_NOT_IMPLEMENTED;
}

int double_member::flags() const
{
	return F_DOUBLE | F_TO_INT | F_TO_DOUBLE;
}

int32_t double_member::test() const
{
	return test_operation(_data.get());
}

int32_t double_member::test_member(operator_t _operator, member * _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t double_member::test_int32(operator_t _operator, int32_t _right) const
{
	return test_operation(_data.get(), _operator, _right);
}

int32_t double_member::test_int64(operator_t _operator, int64_t _right) const
{
	return test_operation(_data.get(), _operator, _right);
}

int32_t double_member::test_double(operator_t _operator, double _right) const
{
	return test_operation(_data.get(), _operator, _right);
}

int64_t double_member::to_int() const
{
	return static_cast<int64_t>(_data.get());
}

double double_member::to_double() const
{
	return _data.get();
}

const char * double_member::to_cstring(utility::buffer_builder * _builder) const
{
	std::snprintf(_builder->buffer<char>(), _builder->capacity(), "%f", _data.get());

	return _builder->buffer<char>();
}

int32_t double_member::int32_data(bool & _success) const
{
	_success = true;

	return static_cast<int32_t>(_data.get());
}

int64_t double_member::int64_data(bool & _success) const
{
	_success = true;

	return static_cast<int64_t>(_data.get());
}

double double_member::double_data(bool & _success) const
{
	_success = true;

	return _data.get();
}

}
}
}