#include "member_map.hpp"

namespace bia
{
namespace framework
{
namespace object
{

member_map::~member_map()
{
	if (_data.only_owner()) {
		auto _allocator = machine::machine_context::active_allocator();

		for (auto & _member : _data.get()) {
			_allocator->destroy_blocks(_member.second);
		}
	}
}

member * member_map::get(machine::string_manager::name_type _name)
{
	auto _result = _data.get().find(_name);

	// Not found
	if (_result == _data.get().end()) {
		throw exception::symbol_error(BIA_EM_UNDEFINED_MEMBER);
	}

	return _result->second;
}

}
}
}