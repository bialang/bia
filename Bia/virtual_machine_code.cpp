#include "virtual_machine_code.hpp"
#include "local_object.hpp"
#include "member.hpp"
#include "max_member_size.hpp"
#include "undefined_member.hpp"

#include <vector>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

virtual_machine_code::virtual_machine_code(memory::const_universal_allocation _code) : _code(memory::cast_allocation<const uint8_t>(_code))
{
}

void virtual_machine_code::execute()
{
	auto _cursor = 0;
	//std::vector<utility::local_object<framework::member, framework::max_member_size>> _tmp_members;

	switch (next_op_code(_cursor)) {
	case OC_RETURN:
		break;
	case OC_CREATE_TEMP_MEMBERS:
	{
		/*_tmp_members.resize(0);

		for (auto & _tmp : _tmp_members) {
			_tmp.create<framework::undefined_member>();
		}*/

		break;
	}
	case OC_INSTANTIATE_I32:
	{
		break;
	}
	default:
		break;
	}

	/*for (auto & _tmp : _tmp_members) {
		_tmp.destroy();
	}*/
}

OP_CODE virtual_machine_code::next_op_code(int & _cursor)
{
	return static_cast<OP_CODE>(_code.first[_cursor++]);
}

}
}
}