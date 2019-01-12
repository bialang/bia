#include "virtual_machine_code.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

void virtual_machine_code::execute()
{
	auto _cursor = 0;

	switch (next_op_code(_cursor)) {
	case OC_RETURN:
		break;
	default:
		break;
	}
}

OP_CODE virtual_machine_code::next_op_code(int & _cursor)
{
	return static_cast<OP_CODE>(_code.first[_cursor++]);
}

}
}
}