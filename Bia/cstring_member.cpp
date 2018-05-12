#include "cstring_member.hpp"
#include "print.hpp"

#include <string>


namespace bia
{
namespace framework
{
namespace native
{

cstring_member::cstring_member(const char * _string) noexcept : cstring_member(_string, std::char_traits<char>::length(_string))
{
}

cstring_member::cstring_member(const char * _string, size_t _length) noexcept
{
	this->_string = _string;
	this->_length = _length;
}

void cstring_member::print() const
{
	machine::link::print_s(_string);
}

void cstring_member::clone(member * _destination)
{
	_destination->replace_this<cstring_member>(_string, _length);
}

void cstring_member::operator_call(member * _destination, operator_type _operator, const member * _right)
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
}

void cstring_member::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
}

void cstring_member::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
}

void cstring_member::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
}

bool cstring_member::is_const() const
{
	return true;
}

int32_t cstring_member::test() const
{
	return static_cast<int32_t>(_length != 0);
}

int32_t cstring_member::test_int32(operator_type _operator, int32_t _right) const
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
}

int32_t cstring_member::test_int64(operator_type _operator, int64_t _right) const
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
}

int32_t cstring_member::test_double(operator_type _operator, double _right) const
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
}

void * cstring_member::get_native_data(native::NATIVE_TYPE _type)
{
	throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
}

const void * cstring_member::get_const_native_data(native::NATIVE_TYPE _type) const
{
	switch (_type) {
	case NATIVE_TYPE::CONST_STRING:
		return &_string;
	default:
		break;
	}

	throw exception::invalid_type(BIA_EM_UNSUPPORTED_TYPE);
}

}
}
}