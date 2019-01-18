#pragma once

#include <map>
#include <string>

#include "config.hpp"
#include "machine_code.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief Holds named scripts.
 *
 * Holds all scripts with their names.
 *
 * @see @ref machine_context
*/
class script_map
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	*/
	BIA_EXPORT script_map() noexcept;
	script_map(const script_map & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @param [in,out] _move The object that should be moved.
	*/
	BIA_EXPORT script_map(script_map && _move);
	/**
	 * Sets the script with the name.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @param _name The name of the script.
	 * @param [in] _code The script.
	 *
	 * @throws See std::map::emplace().
	*/
	BIA_EXPORT void set(const char * _name, platform::machine_code && _code);
	/**
	 * Returns the script with the name.
	 *
	 * @since 3.71.149.809
	 * @date 29-Dec-18
	 *
	 * @param _name The name of the script.
	 *
	 * @throws exception::symbol_error The script doesn't exist.
	 *
	 * @return The script.
	*/
	BIA_EXPORT const platform::machine_code & get(const char * _name) const;

private:
	std::map<std::string, platform::machine_code> _scripts;
};

}
}