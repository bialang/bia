#pragma once

#include <map>
#include <vector>

#include "config.hpp"
#include "member.hpp"
#include "machine_context.hpp"
#include "report.hpp"
#include "op_code.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

/**
 * @brief Holds member names and their indices for the virtual machine.
 *
 * @see @ref virtual_machine_code
*/
class virtual_member_map
{
public:
	/** Type of the member list. */
	typedef std::vector<framework::member*> member_list_t;

	/**
	 * Returns the index of the member. If it does not exist, a new entry will be created.
	 *
	 * @since 3.72.149.810
	 * @date 18-Jan-19
	 *
	 * @param _name The name of the member.
	 *
	 * @throws See std::map::find() and std::map::insert().
	 *
	 * @return The index of the member.
	*/
	member_index_t get_or_insert(grammar::report::member_t _name);
	/**
	 * Creates a member list from all known members.
	 *
	 * @since 3.72.149.810
	 * @date 18-Jan-19
	 *
	 * @param [in] _context The machine context.
	 *
	 * @throws See machine_context::address_of_member().
	 * @throws See std::vector::resize().
	 *
	 * @return A list of members.
	*/
	member_list_t to_member_list(machine_context & _context) const;

private:
	/** Holds all member names and their indices. */
	std::map<grammar::report::member_t, member_index_t> _member_index;
};

}
}
}