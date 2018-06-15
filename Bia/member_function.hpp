#pragma once

#include "function.hpp"
#include "exception.hpp"
#include "disguised_caller.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<typename _Class, typename _Return = void, typename... _Args>
class member_function;

/**
 * @brief A member function member.
 *
 * @tparam _Class The class of the function.
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguemnt types of the function.
*/
template<typename _Class, typename _Return, typename... _Args>
class member_function<_Return(_Class::*)(_Args...)> final : public function
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _function The member function address.
	*/
	explicit member_function(_Return(_Class::*_function)(_Args...)) noexcept
	{
		this->_function = _function;
	}
	virtual void print() override
	{
		puts(typeid(_function).name());
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<member_function<_Return(_Class::*)(_Args...)>>(_function);
	}
	virtual void execute(member * _destination) override
	{
		force::disguised_caller(_function, cast_instance(_instance.get()), _destination);
	}
	virtual void execute_count(member * _destination, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_count(_function, cast_instance(_instance.get()), _destination, _count, _args);

		va_end(_args);
	}
	virtual void execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_format(_function, cast_instance(_instance.get()), _destination, _format, _count, _args);

		va_end(_args);
	}

private:
	/** The member function address. */
	_Return(_Class::*_function)(_Args...);
	utility::share<member*> _instance;


	/**
	 * Retrieves the needed instance from the member.
	 *
	 * @since 3.56.117.675
	 * @date 28-Feb-18
	 *
	 * @param [in] _instance The instance that should be casted.
	 *
	 * @throws exception::argument_error If the passed instance is null.
	 * @throws ... See member::cast().
	 *
	 * @return The instance.
	*/
	static _Class * cast_instance(member * _instance)
	{
		if (_instance) {
			return _instance->cast<_Class>();
		} else {
			throw exception::argument_error(BIA_EM_NULL_INSTANCE);
		}
	}
};

/**
 * @brief A member function.
 *
 * A constant member function member.
 *
 * @tparam _Class The class of the function.
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguemnt types of the function.
*/
template<typename _Class, typename _Return, typename... _Args>
class member_function<_Return(_Class::*)(_Args...) const> final : public function
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _function The member function address.
	*/
	explicit member_function(_Return(_Class::*_function)(_Args...) const) noexcept
	{
		this->_function = _function;
	}
	virtual void print() override
	{
		puts(typeid(_function).name());
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<member_function<_Return(_Class::*)(_Args...) const>>(_function);
	}
	virtual void execute(member * _instance, member * _destination) override
	{
		force::disguised_caller(_function, cast_instance(_instance), _destination);
	}
	virtual void execute_count(member * _instance, member * _destination, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_count(_function, cast_instance(_destination), _destination, _count, _args);

		va_end(_args);
	}
	virtual void execute_format(member * _instance, member * _destination, const char * _format, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_format(_function, cast_instance(_destination), _destination, _format, _count, _args);

		va_end(_args);
	}

private:
	/** The member function address. */
	_Return(_Class::*_function)(_Args...) const;


	/**
	 * Retrieves the needed instance from the member.
	 *
	 * @since 3.56.117.675
	 * @date 28-Feb-18
	 *
	 * @param [in] _instance The instance that should be casted.
	 *
	 * @throws exception::argument_error If the passed instance is null.
	 * @throws ... See member::cast().
	 *
	 * @return The instance.
	*/
	static const _Class * cast_instance(member * _instance)
	{
		if (_instance) {
			return _instance->cast<const _Class>();
		} else {
			throw exception::argument_error(BIA_EM_NULL_INSTANCE);
		}
	}
};

}
}
}