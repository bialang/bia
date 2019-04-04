#pragma once

#include <utility>


namespace bia
{
namespace utility
{

/**
 * @brief A simple scope guard.
*/
template<typename Lambda>
class scope_exit
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.72.149.810
	 * @date 15-Jan-19
	 *
	 * @param [in] _exit The exit function.
	*/
	scope_exit(Lambda && _exit) noexcept : _exit(std::move(_exit))
	{
	}
	/**
	 * Destructor.
	 *
	 * @since 3.72.149.810
	 * @date 15-Jan-19
	 *
	 * @throws See @a _exit.
	*/
	~scope_exit()
	{
		_exit();
	}

private:
	/** The function that is called on destruction. */
	Lambda _exit;
};


template<typename Lambda>
inline scope_exit<Lambda> make_scope_exit(Lambda && _exit)
{
	return { std::forward<Lambda>(_exit) };
}

}
}