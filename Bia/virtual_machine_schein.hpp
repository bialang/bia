#pragma once

#include "schein.hpp"
#include "machine_context.hpp"
#include "virtual_member_map.hpp"


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
	/**
	 * Constructor.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param [in] _context The linked machine context.
	 *
	 * @throws See schein::schein().
	*/
	explicit virtual_machine_schein(machine_context & _context);
	virtual_machine_schein(const virtual_machine_schein & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param [in,out] _move The object that should be moved.
	*/
	virtual_machine_schein(virtual_machine_schein && _move) noexcept = default;
	/**
	 * Updates the globals list.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @param _member_map The member map.
	 *
	 * @throws See virtual_member_map::to_member_list().
	*/
	void set_member_map(const virtual_member_map & _member_map);
	/**
	 * Returns the globals list.
	 *
	 * @since 3.72.149.811
	 * @date 19-Jan-19
	 *
	 * @return The globals list.
	*/
	const virtual_member_map::member_list_t & globals() const noexcept;

private:
	/** The linked context. */
	machine_context * _context;
	/** The globals list. */
	virtual_member_map::member_list_t _globals;
};

}
}
}