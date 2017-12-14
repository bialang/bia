#pragma once

#include "biaFunction.h"
#include "biaDisguisedCaller.h"
#include "biaException.h"
#include "biaLong.h"
#include "biaType.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace executable
{

template<typename T>
class BiaStaticFunction final : public BiaFunction, public utility::BiaFunctionTraits<T>
{
public:
	inline BiaStaticFunction(function_signature p_pFunction) : m_pFunction(p_pFunction)
	{
		if (IS_MEMBER_FUNCTION)
			throw exception::UnknownException("Must be static function.");
	}
	template<typename _T>
	inline BiaStaticFunction(_T&&)
	{
		throw exception::UnknownException("Unknown static function.");
	}
	inline virtual void Print() const override
	{
		printf("%s at 0x%p", typeid(decltype(*this)).name(), this);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaStaticFunction<T>(m_pFunction);
		
		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		decltype(m_pFunction) * pPtr;

		if (p_pRight->Cast<decltype(m_pFunction)>(pPtr))
		{
			m_pFunction = *pPtr;

			return true;
		}

		return false;
	}
	inline virtual int Execute(void * p_pDestination, void*, BiaParameter * p_pBegin, const BiaParameter * p_pEnd, machine::BiaMachineContext*) override
	{
		return force::ExecuteDisguisedBia(p_pDestination, p_pBegin, p_pEnd, nullptr, m_pFunction);
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_FUNCTION | F_STATIC;
	}

protected:
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_pFunction;
	}
	inline virtual TYPE IsType(const std::type_info & p_type, unsigned int p_unPointerRank, bool) const override
	{
		return p_unPointerRank == 1 && BIA_TYPE_COMPARE(p_type, typeid(*m_pFunction)) ? TYPE::POINTER : TYPE::INVALID;
	}

private:
	function_signature m_pFunction;
};

}
}
}
}