#pragma once

#include "biaMember.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace executable
{

class BiaFunction : public BiaMember
{
public:
	inline virtual void SetParameter(SET_PARAMETER, SET_PARAMETER_DATA) override {}
	inline virtual bool GetParameter(GET_PARAMETER, GET_PARAMETER_DATA&) override
	{
		return false;
	}
	inline virtual bool Inc() override final
	{
		return false;
	}
	inline virtual bool Dec() override final
	{
		return false;
	}
	inline virtual bool LoadObject(const machine::BiaKey&, void*) override
	{
		return false;
	}
	inline virtual int Conditional() const override
	{
		return -1;
	}
	inline virtual int Operator(unsigned int, void*, BiaMember*) override final
	{
		return -1;
	}
	inline virtual int SelfOperator(unsigned int, void*) override final
	{
		return -1;
	}
	inline virtual int Call(const machine::BiaKey&, void*, BiaParameter*, const BiaParameter*) override final
	{
		return -1;
	}

protected:
	inline virtual void * LoadNative() override final
	{
		return nullptr;
	}
	inline virtual bool IsType(NATIVE_TYPE, bool) const override final
	{
		return false;
	}
};

}
}
}
}