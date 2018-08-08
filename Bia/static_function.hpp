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
	static_function(_Return(*_function)(_Args...)) noexcept
	{
		this->_function = _function;
	}
	virtual void print() const override
	{
		puts(typeid(_function).name());
	}
	virtual void copy(member * _destination) override
	{
		_destination->replace_this<static_function<_Return, _Args...>>(_function);
	}
	virtual void refer(member * _destination) override
	{
		_destination->replace_this<static_function<_Return, _Args...>>(_function);
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<static_function<_Return, _Args...>>(_function);
	}
	virtual void execute(member * _destination) override
	{
		force::disguised_caller(_function, _destination);
	}
	virtual void execute_count(member * _destination, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_count(_function, _destination, _count, _args);

		va_end(_args);
	}
	virtual void execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_format(_function, _destination, _format, _count, _args);

		va_end(_args);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}

private:
	/** The function pointer. */
	_Return(*_function)(_Args...);
};

}
}
}