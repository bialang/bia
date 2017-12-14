#pragma once

#include <string>

#include "biaNativeVariable.h"
#include "biaMemberHolder.h"
#include "biaLong.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

class BiaStringBase : public BiaMember
{
public:
	inline virtual void SetParameter(SET_PARAMETER, SET_PARAMETER_DATA) override {}
	inline virtual bool GetParameter(GET_PARAMETER, GET_PARAMETER_DATA&) override
	{
		return false;
	}
	inline virtual bool Inc() override
	{
		return false;
	}
	inline virtual bool Dec() override
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
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		return -1;
	}
	inline virtual int SelfOperator(unsigned int, void*) override
	{
		return -1;
	}
	inline virtual int Execute(void*, void*, BiaParameter*, const BiaParameter*, machine::BiaMachineContext*) override
	{
		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE;
	}

protected:
	inline virtual TYPE IsType(const std::type_info&, unsigned int, bool) const override
	{
		return TYPE::INVALID;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::STRING;
	}
};

}
}
}
}