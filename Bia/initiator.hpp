#pragma once

#include <cstdarg>

#include "member.hpp"
#include "allocator.hpp"
#include "exception.hpp"
#include "disguised_caller.hpp"


namespace bia
{
namespace force
{

/**
 * @brief An initiator interfrace.
 *
 * An initiator interface for instantiating objects.
 *
 * @see @ref real_initiator
*/
class initiator
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~initiator() noexcept = default;
	/**
	 * Instantiation function without arguments.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @throw exception::execution_error Unsupported instantiation.
	 * @throw See force::disguised_caller().
	 *
	 * @return The created instance
	*/
	virtual machine::memory::universal_allocation instantiate() const
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_INSTANTIATION);
	}
	/**
	 * Instantiation function with only member arguments.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _count The count of the passed arguments.
	 * @param [in] _stack The stack with the parameters.
	 *
	 * @throw exception::execution_error Unsupported instantiation.
	 * @throw See force::disguised_caller_count().
	 *
	 * @return The created instance
	*/
	virtual machine::memory::universal_allocation instantiate_count(framework::member::parameter_count _count, machine::stack * _stack) const
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_INSTANTIATION);
	}
	/**
	 * Instantiation function without arguments.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param _format The types of the passed arguments.
	 * @param _count The count of the passed arguments.
	 * @param [in] _stack The stack with the parameters.
	 *
	 * @throw exception::execution_error Unsupported instantiation.
	 * @throw See force::disguised_caller_format().
	 *
	 * @return The created instance
	*/
	virtual machine::memory::universal_allocation instantiate_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack) const
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_INSTANTIATION);
	}
};

/**
 * @brief An implementation of @ref initiator.
*/
template<typename Type, typename... Arguments>
class real_initiator final : public initiator
{
public:
	virtual machine::memory::universal_allocation instantiate() const override
	{
		return machine::memory::cast_allocation<void>(force::disguised_caller<Type, Arguments...>());
	}
	virtual machine::memory::universal_allocation instantiate_count(framework::member::parameter_count _count, machine::stack * _stack) const override
	{
		return machine::memory::cast_allocation<void>(force::disguised_caller_count<Type, Arguments...>(_count, _stack));
	}
	virtual machine::memory::universal_allocation instantiate_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack) const override
	{
		return machine::memory::cast_allocation<void>(force::disguised_caller_format<Type, Arguments...>(_format, _count, _stack));
	}
};

}
}