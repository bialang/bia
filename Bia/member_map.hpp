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

template<typename _Ty, typename... _Args>
inline member * member_map::emplace(name_type _name, _Args &&... _args)
{
	auto _result = _data.get().find(_name);

	// Create new
	if (_result == _data.get().end()) {
		auto _member = machine::machine_context::active_member_allocator()->template construct_member<_Ty>(std::forward<_Args>(_args)...);

		_data.get().emplace(_name, _member);
		
		return _member.first;
	} else {
		return _result->second->replace_this<_Ty>(std::forward<_Args>(_args)...);
	}
}

}
}
}