#pragma once

#include <cstdint>
#include <vector>

#include "allocator.hpp"
#include "op_code.hpp"
#include "member.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class virtual_machine_code
{
public:
	virtual_machine_code(memory::const_universal_allocation _code, machine_context & _context);
	void execute();

private:
	memory::allocation<const uint8_t> _code;
	std::vector<framework::member*> _globals;

	OP_CODE next_op_code(int & _cursor);
};

}
}
}