#pragma once

#include <cstdarg>

#include "member.hpp"
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
	virtual void * instantiate() const
	{
		//throw exception::BadCallException("Cannot instantiate class without a constructor.");
	}
	virtual void * instantiate_count(framework::member::parameter_count _count, va_list _args) const
	{
		//throw exception::BadCallException("Cannot instantiate class without a constructor.");
	}
	virtual void * instantiate_format(framework::member::parameter_count _count, const char * _format, va_list _args) const
	{
		//throw exception::BadCallException("Cannot instantiate class without a constructor.");
	}
};

/**
 * @brief An implementation of @ref initiator.
*/
template<typename _Ty, typename... _Args>
class real_initiator final : public initiator
{
public:
	virtual void * instantiate() const override
	{
		return force::disguised_caller<_Ty, _Args...>();
	}
	virtual void * instantiate_count(framework::member::parameter_count _count, va_list _args) const override
	{
		return force::disguised_caller_count<_Ty, _Args...>(_count, _args);
	}
	virtual void * instantiate_format(framework::member::parameter_count _count, const char * _format, va_list _args) const override
	{
		return force::disguised_caller_format<_Ty, _Args...>(_count, _format, _args);
	}
};

}
}