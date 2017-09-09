#pragma once

#include "biaMember.h"
#include "biaClassWrapper.h"


namespace bia
{
namespace api
{
namespace framework
{

class BiaClassWrapperMember final : public BiaMember
{
public:
	inline BiaClassWrapperMember(std::shared_ptr<BiaClassWrapperBase> p_pMembers) : m_pMembers(std::move(p_pMembers)) {}
	inline virtual void Print() const override
	{
		printf("<%s as %s at 0x%p>", typeid(*this).name(), m_pMembers->UniqueName().c_str(), this);
	}
	inline virtual void SetParameter(SET_PARAMETER, SET_PARAMETER_DATA) override {}
	inline virtual bool GetParameter(GET_PARAMETER, GET_PARAMETER_DATA&) override
	{
		return false;
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaClassWrapperMember(m_pMembers);

		return true;
	}
	inline virtual bool Store(BiaMember*) override
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
	inline virtual int Operator(unsigned int, void*, BiaMember*) override
	{
		return -1;
	}
	inline virtual int SelfOperator(unsigned int, void*) override
	{
		return -1;
	}
	inline virtual int Execute(void * p_pReturnDestination, void*, BiaParameter * p_pBegin, const BiaParameter * p_pEnd, machine::BiaMachineContext*) override
	{
		return m_pMembers->CreateInstance(p_pReturnDestination, p_pBegin, p_pEnd) ? 1 : -1;
	}
	inline virtual int Call(const machine::BiaKey&, void*, BiaParameter*, const BiaParameter*) override
	{
		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_CLASS;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return nullptr;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return nullptr;
	}
	inline virtual TYPE IsType(const std::type_info&, unsigned int, bool) const override
	{
		return TYPE::INVALID;
	}
	inline virtual bool IsType(NATIVE_TYPE, bool) const override
	{
		return false;
	}

private:
	std::shared_ptr<BiaClassWrapperBase> m_pMembers;
};

}
}
}