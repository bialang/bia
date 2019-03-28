#pragma once

#include <utility>

#include "member_map_def.hpp"
#include "machine_context.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty, typename... Arguments>
inline member * member_map::emplace(name_t _name, Arguments &&... _args)
{
	auto _result = _data.get().data.find(_name);

	// Create new
	if (_result == _data.get().data.end()) {
		auto _member = machine::machine_context::active_member_allocator()->template construct_member<_Ty>(std::forward<Arguments>(_args)...);

		_data.get().data.emplace(_name, _member);
		
		return _member.first;
	} else {
		return _result->second->replace_this<_Ty>(std::forward<Arguments>(_args)...);
	}
}

}
}
}