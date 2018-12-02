#include "int_member.hpp"
#include "share.hpp"
#include "print.hpp"


namespace bia
{
namespace framework
{
namespace native
{

int_member::int_member(int32_t _value) : _data(_value)
{
}

int_member::int_member(int64_t _value)
{
}

int_member::int_member(const data_type & _data) noexcept : _data(_data)
{
}

void BIA_MEMBER_CALLING_CONVENTION int_member::print() const
{
	machine::link::print(_data.get());
}

void BIA_MEMBER_CALLING_CONVENTION int_member::copy(member * _destination)
{
	_destination->replace_this<int_member>(_data.get());
}

void BIA_MEMBER_CALLING_CONVENTION int_member::refer(member * _destination)
{
	_destination->replace_this<int_member>(_data);
}

void BIA_MEMBER_CALLING_CONVENTION int_member::clone(member * _destination)
{
	copy(_destination);
}

void BIA_MEMBER_CALLING_CONVENTION int_member::operator_call(member * _destination, operator_type _operator, const member * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION int_member::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION int_member::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION int_member::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION int_member::object_member(member * _destination, machine::string_manager::name_type _name)
{
	BIA_NOT_IMPLEMENTED;
}

int int_member::flags() const
{
	return F_INT | F_TO_DOUBLE | F_TO_INT;
}

int32_t BIA_MEMBER_CALLING_CONVENTION int_member::test() const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION int_member::test_member(operator_type _operator, member * _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION int_member::test_int32(operator_type _operator, int32_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION int_member::test_int64(operator_type _operator, int64_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION int_member::test_double(operator_type _operator, double _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int64_t int_member::to_int() const
{
	return _data.get();
}

double int_member::to_double() const
{
	return static_cast<double>(_data.get());
}

void * int_member::native_data(native::NATIVE_TYPE _type)
{
	BIA_NOT_IMPLEMENTED;
}

const void * int_member::const_native_data(native::NATIVE_TYPE _type) const
{
	BIA_NOT_IMPLEMENTED;
}

}
}
}