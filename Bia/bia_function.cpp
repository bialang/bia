#include "bia_function.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

bia_function::bia_function(const data_t & _data) noexcept : _data(_data)
{
}

bia_function::~bia_function()
{
}

void bia_function::disassemble() const
{
	_data->disassemble();
}

void BIA_MEMBER_CALLING_CONVENTION bia_function::print() const
{
	printf("<bia function at %p>\n", this);
}

void BIA_MEMBER_CALLING_CONVENTION bia_function::copy(member * _destination)
{
	BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION bia_function::refer(member * _destination)
{
	_destination->template replace_this<bia_function>(_data);
}

void BIA_MEMBER_CALLING_CONVENTION bia_function::clone(member * _destination)
{
	refer(_destination);
}

void BIA_MEMBER_CALLING_CONVENTION bia_function::execute(machine::stack * _stack, member * _destination)
{
	_data->execute_count(*_stack, _destination, 0);
}

void BIA_VARG_MEMBER_CALLING_CONVENTION bia_function::execute_count(machine::stack * _stack, member * _destination, void * _reserved, parameter_count_t _count)
{
	_data->execute_count(*_stack, _destination, _count);
}

void BIA_VARG_MEMBER_CALLING_CONVENTION bia_function::execute_format(machine::stack * _stack, member * _destination, const char * _format, parameter_count_t _count)
{
	BIA_NOT_IMPLEMENTED;
}

void bia_function::set_instance(const void * _instance, const std::type_info & _type)
{
}

}
}
}
