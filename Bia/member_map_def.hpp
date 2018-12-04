#pragma once

#include <map>

#include "config.hpp"
#include "member.hpp"
#include "share_def.hpp"
#include "string_manager.hpp"


namespace bia
{
namespace framework
{
namespace object
{

class member_map
{
public:
	typedef machine::string_manager::name_type name_type;

	/**
	 * Destructor.
	 *
	 * @since 3.67.135.754
	 * @date 8-Aug-18
	 *
	 * @throws See data_map::~data_map().
	*/
	~member_map() = default;
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
	 *
	 * @return The emplaced member.
	*/
	template<typename _Ty, typename... _Args>
	member * emplace(name_type _name, _Args &&... _args);
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
	BIA_EXPORT member * get(name_type _name);
	/**
	 * Returns the member or creates a new if it does not exist.
	 *
	 * @since 3.68.140.788
	 * @date 16-Sep-18
	 *
	 * @param _name The name of the member.
	 *
	 * @throws See machine::memory::allocator::construct_blocks().
	 * @throws See std::map::find() and std::map::emplace().
	 *
	 * @return The member.
	*/
	BIA_EXPORT member * get_or_create(name_type _name);

private:
	struct data_map
	{
		typedef std::map<name_type, machine::memory::allocation<member>> type;

		type data;

		BIA_EXPORT ~data_map();
	};

	/** The map with all the members. */
	utility::share<data_map> _data;
};

}
}
}