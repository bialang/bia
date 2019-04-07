#include "undefined_member.hpp"
#include "exception.hpp"

#define BIA_UNDEFINED_ERROR throw exception::symbol_error(BIA_EM_UNDEFINED_MEMBER)


namespace bia
{
namespace framework
{

void BIA_MEMBER_CALLING_CONVENTION undefined_member::undefine()
{
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::print() const
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::copy(member * _destination)
{
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::refer(member * _destination)
{
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::clone(member * _destination)
{
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::execute(machine::stack * _stack, member * _destination)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_VARG_MEMBER_CALLING_CONVENTION undefined_member::execute_count(machine::stack * _stack, member * _destination, void * _reserved, parameter_count_t _count)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_VARG_MEMBER_CALLING_CONVENTION undefined_member::execute_format(machine::stack * _stack, member * _destination, const char * _format, parameter_count_t _count)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::operator_call(member * _destination, operator_t _operator, const member * _right)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::operator_call_int32(member * _destination, operator_t _operator, int32_t _right)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::operator_call_int64(member * _destination, operator_t _operator, int64_t _right)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::operator_call_big_int(member * _destination, operator_t _operator, const detail::big_int * _right)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::operator_call_double(member * _destination, operator_t _operator, double _right)
{
	BIA_UNDEFINED_ERROR;
}

void BIA_MEMBER_CALLING_CONVENTION undefined_member::object_member(member * _destination, machine::name_manager::name_t _name)
{
	BIA_UNDEFINED_ERROR;
}

void undefined_member::set_instance(const void * _instance, const std::type_info & _type)
{
	BIA_UNDEFINED_ERROR;
}

int undefined_member::flags() const
{
	BIA_UNDEFINED_ERROR;
}

int32_t BIA_MEMBER_CALLING_CONVENTION undefined_member::test() const
{
	BIA_UNDEFINED_ERROR;
}

int32_t BIA_MEMBER_CALLING_CONVENTION undefined_member::test_member(operator_t _operator, member * _right) const
{
	BIA_UNDEFINED_ERROR;
}

int32_t BIA_MEMBER_CALLING_CONVENTION undefined_member::test_int32(operator_t _operator, int32_t _right) const
{
	BIA_UNDEFINED_ERROR;
}

int32_t BIA_MEMBER_CALLING_CONVENTION undefined_member::test_int64(operator_t _operator, int64_t _right) const
{
	BIA_UNDEFINED_ERROR;
}

int32_t BIA_MEMBER_CALLING_CONVENTION undefined_member::test_double(operator_t _operator, double _right) const
{
	BIA_UNDEFINED_ERROR;
}

int64_t undefined_member::to_int() const
{
	BIA_UNDEFINED_ERROR;
}

double undefined_member::to_double() const
{
	BIA_UNDEFINED_ERROR;
}

const char * undefined_member::to_cstring(utility::buffer_builder * _builder) const
{
	BIA_UNDEFINED_ERROR;
}

int32_t undefined_member::int32_data(bool & _success) const
{
	BIA_UNDEFINED_ERROR;
}

int64_t undefined_member::int64_data(bool & _success) const
{
	BIA_UNDEFINED_ERROR;
}

double undefined_member::double_data(bool & _success) const
{
	BIA_UNDEFINED_ERROR;
}

void * undefined_member::data(const std::type_info & _type, bool & _success)
{
	BIA_UNDEFINED_ERROR;
}

const void * undefined_member::const_data(const std::type_info & _type, bool & _success) const
{
	BIA_UNDEFINED_ERROR;
}

}
}
