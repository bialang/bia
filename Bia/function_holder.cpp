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

void function_holder::execute_count(machine::stack & _stack, framework::member * _destination, framework::member::parameter_count_t _count)
{
	machine::virtual_machine::virtual_machine_code::return_t _return;

	_function.execute(_stack, _count, _return);

	_return.get()->refer(_destination);
}

void function_holder::execute_format(framework::member * _destination)
{
}

}
}