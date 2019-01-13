#pragma once

#include <cstdint>

#include "allocator.hpp"
#include "op_code.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class virtual_machine_code
{
public:
	virtual_machine_code(memory::const_universal_allocation _code);
	void execute();

private:
	memory::allocation<const uint8_t> _code;

	OP_CODE next_op_code(int & _cursor);
};

}
}
}