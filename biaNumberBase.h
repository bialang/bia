#pragma once

#include "biaNativeVariable.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

class BiaNumberBase : public BiaMember
{
public:
	inline virtual void SetParameter(SET_PARAMETER, SET_PARAMETER_DATA) override {}
	inline virtual bool GetParameter(GET_PARAMETER, GET_PARAMETER_DATA&) override
	{
		return false;
	}
	inline virtual bool LoadObject(const machine::BiaKey&, void*) override
	{
		return false;
	}
	inline virtual int SelfOperator(size_t, void*) override
	{
		return -1;
	}
	inline virtual int Execute(void*, void*, BiaParameter*, const BiaParameter*, machine::BiaMachineContext*) override
	{
		return -1;
	}
	inline virtual int Call(const machine::BiaKey&, void*, BiaParameter*, const BiaParameter*) override
	{
		return -1;
	}

protected:
	inline virtual TYPE IsType(const std::type_info&, unsigned int, bool) const override
	{
		return TYPE::INVALID;
	}
};

}
}
}
}