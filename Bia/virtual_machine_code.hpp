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
	void execute();

private:
	memory::allocation<uint8_t> _code;

	OP_CODE next_op_code(int & _cursor);
};

}
}
}