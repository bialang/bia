#pragma once

#include <functional>


namespace bia
{
namespace utility
{

/**
 * @brief A simple scope guard.
*/
class scope_exit
{
public:
	/** The exit function type. */
	typedef std::function<void()> function_t;

	/**
	 * Constructor.
	 *
	 * @since 3.72.149.810
	 * @date 15-Jan-19
	 *
	 * @param [in] _exit The exit function.
	*/
	scope_exit(function_t && _exit) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.72.149.810
	 * @date 15-Jan-19
	 *
	 * @throws See @a _exit.
	*/
	~scope_exit();

private:
	/** The function that is called on destruction. */
	function_t _exit;
};

}
}