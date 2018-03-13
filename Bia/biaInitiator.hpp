#pragma once

#include "biaMember.hpp"
#include "biaException.hpp"


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
class BiaInitiatorDeriviate final : BiaInitiator
{
public:
	inline virtual void * Instantiate() override
	{
		return BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void * InstantiateCount(framework::BiaMember::parameter_count p_unParameterCount, va_list p_args) override
	{
		return BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
	inline virtual void * InstantiateFormat(framework::BiaMember::parameter_count p_unParameterCount, const char * p_pcFormat, va_list p_args) override
	{
		return BIA_IMPLEMENTATION_EXCEPTION("Not implemented.");
	}
};

}
}