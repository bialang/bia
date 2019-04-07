#pragma once

#include "stack.hpp"
#include "member.hpp"
#include "virtual_machine_code.hpp"


namespace bia
{
namespace detail
{

class function_holder
{
public:
	function_holder(machine::virtual_machine::virtual_machine_code && _function) noexcept;
	function_holder(const function_holder & _copy) = delete;
	function_holder(function_holder && _move) noexcept = default;
	~function_holder() = default;
	void disassemble() const;
	void execute_format(machine::stack & _stack, framework::member * _destination, const char * _format, framework::member::parameter_count_t _count);

private:
	machine::virtual_machine::virtual_machine_code _function;
};

}
}