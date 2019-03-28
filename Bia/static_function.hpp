#pragma once

#include <cstdio>
#include <cstddef>

#include "function.hpp"
#include "exception.hpp"
#include "disguised_caller_def.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

/**
 * @brief A static function member.
 *
 * @tparam Optional_count The amount of optional parameters.
 * @tparam Return The return type of the function.
 * @tparam Arguments The arguments of the function.
*/
template<size_t Optional_count, typename Return, typename... Arguments>
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
	static_function(Return(*_function)(Arguments...)) noexcept
	{
		this->_function = _function;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		puts(typeid(_function).name());
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override
	{
		_destination->replace_this<static_function<Optional_count, Return, Arguments...>>(_function);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override
	{
		_destination->replace_this<static_function<Optional_count, Return, Arguments...>>(_function);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override
	{
		_destination->replace_this<static_function<Optional_count, Return, Arguments...>>(_function);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		force::disguised_caller<Optional_count>(_function, _destination, nullptr, 0, nullptr);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack) override
	{
		force::disguised_caller<Optional_count>(_function, _destination, nullptr, _count, _stack);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack) override
	{
		force::disguised_caller<Optional_count>(_function, _destination, _format, _count, _stack);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}

private:
	/** The function pointer. */
	Return(*_function)(Arguments...);
};

}
}
}
