#pragma once

#include "schein.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

/**
 * @brief Contains information about machine code.
 *
 * @see @ref machine_code
*/
class machine_schein : public schein
{
public:
	using schein::schein;
	machine_schein(const machine_schein & _copy) = delete;
	machine_schein(machine_schein && _move) = default;
	/**
	 * Move operator.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param [in,out] _move Defines the value that should be moved.
	 *
	 * @throws See clear().
	 *
	 * @return This.
	*/
	BIA_EXPORT machine_schein & operator=(machine_schein && _move);
};

}
}
}