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
		throw exception::AccessViolationException("Cannot instantiate class without a constructor.");
	}
	inline virtual void * InstantiateCount(framework::BiaMember::parameter_count p_unParameterCount, ...)
	{
		throw exception::AccessViolationException("Cannot instantiate class without a constructor.");
	}
	inline virtual void * InstantiateFormat(framework::BiaMember::parameter_count p_unParameterCount, const char * p_pcFormat, ...)
	{
		throw exception::AccessViolationException("Cannot instantiate class without a constructor.");
	}
};

template<typename T, typename... _ARGS>
class BiaInitiatorDeriviate final : BiaInitiator
{
public:
	inline virtual void * Instantiate() override
	{
		return nullptr;
	}
	inline virtual void * InstantiateCount(framework::BiaMember::parameter_count p_unParameterCount, ...) override
	{
		return nullptr;
	}
	inline virtual void * InstantiateFormat(framework::BiaMember::parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		return nullptr;
	}
};

}
}