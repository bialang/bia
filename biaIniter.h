#pragma once

#include "biaParameter.h"
#include "biaDisguisedCaller.h"


namespace bia
{
namespace api
{
namespace framework
{

struct BiaInitializerBase
{
	inline virtual ~BiaInitializerBase() = default;
	virtual void * Initialize(BiaParameter * p_pBegin, const BiaParameter * p_pEnd) const = 0;
};

template<typename T, typename... _ARGS>
struct BiaInitializer final : BiaInitializerBase
{
	inline virtual void * Initialize(BiaParameter * p_pBegin, const BiaParameter * p_pEnd) const override
	{
		return force::InitializeDisguisedBia<T, _ARGS...>(p_pBegin, p_pEnd);
	}
};

}
}
}