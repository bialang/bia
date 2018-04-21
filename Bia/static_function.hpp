#pragma once

#include <cstdio>

#include "function.hpp"
#include "exception.hpp"
#include "disguised_caller.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

/**
 * @brief A static function member.
 *
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguments of the function.
*/
template<typename _Return, typename... _Args>
class static_function final : public function
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _function The static function address.
	*/
	explicit static_function(_Return(*_function)(_Args...)) noexcept
	{
		this->_function = _function;
	}
	virtual void print() override
	{
		puts(typeid(_function).name());
	}

private:
	/** The function pointer. */
	_Return(*_function)(_Args...);
};

}
}
}