#include "function_holder.hpp"


namespace bia
{
namespace detail
{

function_holder::function_holder(machine::virtual_machine::virtual_machine_code && _function) noexcept : _function(std::move(_function))
{
}

void function_holder::disassemble() const
{
	_function.disassemble();
}

void function_holder::execute(machine::stack & _stack, framework::member * _destination)
{
	_function.execute(_stack);
}

void function_holder::execute_count(framework::member * _destination)
{
}

void function_holder::execute_format(framework::member * _destination)
{
}

}
}