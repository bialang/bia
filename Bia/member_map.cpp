#include "member_map.hpp"
#include "undefined_member.hpp"


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

member * member_map::get(name_type _name)
{
	auto _result = _data.get().find(_name);

	// Not found
	if (_result == _data.get().end()) {
		throw exception::symbol_error(BIA_EM_UNDEFINED_MEMBER);
	}

	return _result->second;
}

member * member_map::get_or_create(name_type _name)
{
	auto _result = _data.get().find(_name);

	// Create new
	if (_result == _data.get().end()) {
		auto _member = machine::machine_context::active_allocator()->construct_blocks<member, undefined_member>(1);

		_data.get().emplace(_name, _member);

		return _member.first;
	}

	return _result->second;
}

}
}
}