#pragma once

#include <map>

#include "member.hpp"
#include "allocator.hpp"
#include "share.hpp"
#include "string_manager.hpp"
#include "machine_context.hpp"
#include "exception.hpp"


namespace bia
{
namespace framework
{
namespace object
{

class member_map
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.67.135.754
	 * @date 8-Aug-18
	 *
	 * @throws See machine::memory::allocator::destroy_blocks().
	*/
	~member_map();
	
	/**
	 * Emplaces a new member.
	 *
	 * @since 3.67.135.754
	 * @date 8-Aug-18
	 *
	 * @tparam _Ty The type of the member.
	 * @tparam _Args The argument types.
	 *
	 * @param _name The name of the member.
	 * @param _args The arguments needed to create the member.
	 *
	 * @throws See machine::memory::allocator::construct_blocks().
	 * @throws See member::replace_this().
	 * @throws See std::map::find() and std::map::emplace().
	*/
	template<typename _Ty, typename... _Args>
	void emplace(machine::string_manager::name_type _name, _Args &&... _args)
	{
		auto _result = _data.get().find(_name);

		// Create new
		if (_result == _data.get().end()) {
			_data.get().emplace(_name, machine::machine_context::active_allocator()->construct_blocks<member, _Ty>(1, std::forward<_Args>(_args)...));
		} else {
			_result->second->replace_this<_Ty>(std::forward<_Args>(_args)...);
		}
	}
	/**
	 * Returns the member.
	 *
	 * @since 3.67.135.754
	 * @date 8-Aug-18
	 *
	 * @param _name The name of the member.
	 *
	 * @throws exception::symbol_error If the member doesn't exist.
	 * @throws See std::map::find().
	 *
	 * @return The member.
	*/
	member * get(machine::string_manager::name_type _name);

private:
	/** The map with all the members. */
	utility::share<std::map<machine::string_manager::name_type, machine::memory::allocation<member>>> _data;
};

}
}
}