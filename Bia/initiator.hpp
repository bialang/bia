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
	 * @param [in,out] _args The passed arguments.
	 *
	 * @throw exception::execution_error Unsupported instantiation.
	 * @throw See force::disguised_caller_count().
	 *
	 * @return The created instance
	*/
	virtual machine::memory::universal_allocation instantiate_count(framework::member::parameter_count _count, va_list_wrapper & _args) const
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
	 * @param [in,out] _args The passed arguments.
	 *
	 * @throw exception::execution_error Unsupported instantiation.
	 * @throw See force::disguised_caller_format().
	 *
	 * @return The created instance
	*/
	virtual machine::memory::universal_allocation instantiate_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args) const
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_INSTANTIATION);
	}
};

/**
 * @brief An implementation of @ref initiator.
*/
template<typename _Ty, typename... _Args>
class real_initiator final : public initiator
{
public:
	virtual machine::memory::universal_allocation instantiate() const override
	{
		return machine::memory::cast_allocation<void>(force::disguised_caller<_Ty, _Args...>());
	}
	virtual machine::memory::universal_allocation instantiate_count(framework::member::parameter_count _count, va_list_wrapper & _args) const override
	{
		return machine::memory::cast_allocation<void>(force::disguised_caller_count<_Ty, _Args...>(_count, _args));
	}
	virtual machine::memory::universal_allocation instantiate_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args) const override
	{
		return machine::memory::cast_allocation<void>(force::disguised_caller_format<_Ty, _Args...>(_format, _count, _args));
	}
};

}
}