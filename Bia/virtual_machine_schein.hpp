#pragma once

#include <vector>

#include "config.hpp"
#include "schein.hpp"
#include "index_map.hpp"
#include "name_manager.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

/**
 * @brief The schein for virtual machine code.
 *
 * @see @ref virtual_machine_code
*/
class virtual_machine_schein : public schein
{
public:
	typedef std::vector<framework::member*> member_list_t;
	typedef std::vector<name_manager::name_t> name_list_t;

	using schein::schein;
	/**
	 * Updates the globals list.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param _member_map The member map.
	 *
	 * @throws See utility::index_map::to_list().
	*/
	BIA_EXPORT void set_member_map(const utility::index_map & _member_map);
	/**
	 * Updates the name list.
	 *
	 * @since 3.73.150.818
	 * @date 8-Mar-19
	 *
	 * @param _name_map The name map.
	 *
	 * @throws See utility::index_map::to_list().
	*/
	BIA_EXPORT void set_name_map(const utility::index_map & _name_map);
	/**
	 * Returns the globals list.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @return The global list.
	*/
	BIA_EXPORT const member_list_t & globals() const noexcept;
	/**
	 * Returns the name list.
	 *
	 * @since 3.73.150.818
	 * @date 8-Mar-19
	 *
	 * @return The name list.
	*/
	BIA_EXPORT const name_list_t & names() const noexcept;

private:
	/** The globals list. */
	member_list_t _globals;
	/** The names. */
	name_list_t _names;
};

}
}
}