#include "regex_member.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace native
{

regex_member::regex_member(const data_t & _data) noexcept : _data(_data)
{
}

regex_member::~regex_member()
{
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::print() const
{
	printf("<regex at %p>\n", this);
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::copy(member * _destination)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::refer(member * _destination)
{
	_destination->template replace_this<regex_member>(_data);
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::clone(member * _destination)
{
	refer(_destination);
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::operator_call(member * _destination, operator_t _operator, const member * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::operator_call_int32(member * _destination, operator_t _operator, int32_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::operator_call_int64(member * _destination, operator_t _operator, int64_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::operator_call_big_int(member * _destination, operator_t _operator, const dependency::big_int * _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::operator_call_double(member * _destination, operator_t _operator, double _right)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION regex_member::object_member(member * _destination, machine::name_manager::name_t _name)
{
	BIA_NOT_IMPLEMENTED;
}

int regex_member::flags() const
{
	return 0;
}

int32_t BIA_MEMBER_CALLING_CONVENTION regex_member::test() const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION regex_member::test_member(operator_t _operator, member * _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION regex_member::test_int32(operator_t _operator, int32_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION regex_member::test_int64(operator_t _operator, int64_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t BIA_MEMBER_CALLING_CONVENTION regex_member::test_double(operator_t _operator, double _right) const
{
	BIA_NOT_IMPLEMENTED;
}

int64_t regex_member::to_int() const
{
	BIA_NOT_IMPLEMENTED;
}

double regex_member::to_double() const
{
	BIA_NOT_IMPLEMENTED;
}

const char * regex_member::to_cstring(utility::buffer_builder * _builder) const
{
	BIA_NOT_IMPLEMENTED;
}

int32_t regex_member::int32_data() const
{
	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

int64_t regex_member::int64_data() const
{
	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

double regex_member::double_data() const
{
	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

}
}
}