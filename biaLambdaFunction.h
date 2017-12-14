#pragma once

#include <utility>
#include <type_traits>

#include "biaFunction.h"
#include "biaDisguisedCaller.h"
#include "biaLong.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace executable
{

template<typename _LAMBDA>
class BiaLambdaFunction final : public BiaFunction
{
public:
	inline BiaLambdaFunction(_LAMBDA && p_lambda) : m_pLambda(new _LAMBDA(std::forward<_LAMBDA>(p_lambda))), m_bDelete(true) {}
	inline BiaLambdaFunction(_LAMBDA * p_pLambda) : m_pLambda(p_pLambda), m_bDelete(false) {}
	inline ~BiaLambdaFunction()
	{
		if (m_bDelete)
			delete m_pLambda;

		m_pLambda = nullptr;
	}
	template<typename T>
	inline BiaLambdaFunction(T&&)
	{
		m_pLambda = nullptr;

		throw exception::UnknownException("Unknown lambda function.");
	}
	inline virtual void Print() const override
	{
		printf("%s at 0x%p", typeid(decltype(*this)).name(), this);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		return false;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		return false;
	}
	inline virtual int Execute(void * p_pDestination, void*, BiaParameter * p_pBegin, const BiaParameter * p_pEnd, machine::BiaMachineContext*) override
	{
		return force::ExecuteDisguisedBia(p_pDestination, p_pBegin, p_pEnd, m_pLambda, &_LAMBDA::operator());
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
	inline virtual TYPE IsType(const std::type_info&, unsigned int, bool) const override
	{
		return TYPE::INVALID;
	}

private:
	_LAMBDA * m_pLambda;
	bool m_bDelete;
};

}
}
}
}