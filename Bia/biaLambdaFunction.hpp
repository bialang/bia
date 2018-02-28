#pragma once

#include <new>
#include <memory>
#include <utility>

#include "biaFunction.hpp"
#include "biaUndefined.hpp"
#include "biaException.hpp"
#include "biaDisguisedCalled.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<typename _LAMBDA>
class BiaLambdaFunction final : public BiaFunction
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines the static function.
	*/
	inline explicit BiaLambdaFunction(_LAMBDA && p_lambda) : m_pLambda(new _LAMBDA(std::move(p_lambda))) {}
	inline explicit BiaLambdaFunction(std::shared_ptr<_LAMBDA> p_pLambda) : m_pLambda(std::move(p_pLambda)) {}
	inline ~BiaLambdaFunction() = default;

	/**
	 * @see	BiaMember::Print().
	*/
	inline virtual void Print() override
	{
		puts(typeid(&_LAMBDA::operator()).name());
	}
	/**
	 * @see	BiaMember::Call().
	*/
	inline virtual void Call(BiaMember*, BiaMember * p_pDestination) override
	{
		force::DisguisedCaller(&_LAMBDA::operator(), m_pLambda.get(), p_pDestination);
	}
	/**
	 * @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(BiaMember*, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		va_list args;
		va_start(args, p_unParameterCount);

		force::DisguisedCallerCount(&_LAMBDA::operator(), m_pLambda.get(), p_pDestination, p_unParameterCount, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(BiaMember*, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		va_list args;
		va_start(args, p_pcFormat);

		force::DisguisedCallerFormat(&_LAMBDA::operator(), m_pLambda.get(), p_pDestination, p_unParameterCount, p_pcFormat, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::Clone().
	*/
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaLambdaFunction<_LAMBDA>>(*this);
	}
	/**
	 * @see	BiaMember::IsType().
	*/
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
	}

protected:
	/**
	 * @see	BiaMember::GetData().
	*/
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Type is not supported.");
	}

private:
	std::shared_ptr<_LAMBDA> m_pLambda;
};

}
}
}