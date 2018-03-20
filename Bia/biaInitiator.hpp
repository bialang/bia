#pragma once

#include <cstdarg>

#include "biaMember.hpp"
#include "biaException.hpp"
#include "biaDisguisedCaller.hpp"


namespace bia
{
namespace force
{

class BiaInitiator
{
public:
	virtual ~BiaInitiator() = default;
	inline virtual void * Instantiate()
	{
		throw exception::BadCallException("Cannot instantiate class without a constructor.");
	}
	inline virtual void * InstantiateCount(framework::BiaMember::parameter_count p_unParameterCount, va_list p_args)
	{
		throw exception::BadCallException("Cannot instantiate class without a constructor.");
	}
	inline virtual void * InstantiateFormat(framework::BiaMember::parameter_count p_unParameterCount, const char * p_pcFormat, va_list p_args)
	{
		throw exception::BadCallException("Cannot instantiate class without a constructor.");
	}
};

template<typename T, typename... _ARGS>
class BiaInitiatorDeriviate final : public BiaInitiator
{
public:
	inline virtual void * Instantiate() override
	{
		return force::DisguisedCaller<T, _ARGS...>();
	}
	inline virtual void * InstantiateCount(framework::BiaMember::parameter_count p_unParameterCount, va_list p_args) override
	{
		return force::DisguisedCallerCount<T, _ARGS...>(p_unParameterCount, p_args);
	}
	inline virtual void * InstantiateFormat(framework::BiaMember::parameter_count p_unParameterCount, const char * p_pcFormat, va_list p_args) override
	{
		return force::DisguisedCallerFormat<T, _ARGS...>(p_unParameterCount, p_pcFormat, p_args);
	}
};

}
}