#pragma once

#include "biaFunction.h"
#include "biaByteStream.h"
#include "biaMachineContext.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace executable
{

class BiaBiaFunction final : public BiaFunction
{
public:
	inline BiaBiaFunction(const void * p_pFunction, size_t p_iSize) : m_function([=]{
		auto pcTmp = new char[p_iSize];

		memcpy(pcTmp, p_pFunction, p_iSize);

		return pcTmp;
	}(), p_iSize) {}
	inline ~BiaBiaFunction()
	{
		delete[] m_function.pcByteCode;
	}
	inline virtual void Print() const override
	{

	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaBiaFunction(m_function.pcByteCode, m_function.pcByteCodeEnd - m_function.pcByteCode);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		return false;
	}
	inline virtual int Execute(void * p_pReturnDestination, void * p_pInstance, BiaParameter * p_pBegin, const BiaParameter * p_pEnd, machine::BiaMachineContext * p_pContext) override
	{
		//Make parameter


		//Execute
		p_pContext->ExecuteBia(m_function);

		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_FUNCTION;
	}

protected:
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return nullptr;
	}
	inline virtual bool IsType(const std::type_info&, unsigned int, bool) const override
	{
		return false;
	}

private:
	stream::BiaByteStream m_function;
};

}
}
}
}