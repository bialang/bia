#pragma once

#include <new>

#include "biaFunction.hpp"
#include "biaException.hpp"
#include "biaDisguisedCaller.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<typename _RETURN, typename... _ARGS>
class BiaStaticFunction final : public BiaFunction
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines the static function.
	*/
	inline explicit BiaStaticFunction(_RETURN(*p_pFunction)(_ARGS...)) : m_pFunction(p_pFunction) {}
	inline ~BiaStaticFunction() = default;

	/**
	 * @see	BiaMember::Print().
	*/
	inline virtual void Print() override
	{
		puts(typeid(m_pFunction).name());
	}
	/**
	 * @see	BiaMember::Call().
	*/
	inline virtual void Call(BiaMember*, BiaMember * p_pDestination) override
	{
		force::DisguisedCaller(m_pFunction, p_pDestination);
	}
	/**
	 * @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(BiaMember*, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		va_list args;
		va_start(args, p_unParameterCount);

		force::DisguisedCallerCount(m_pFunction, p_pDestination, p_unParameterCount, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(BiaMember*, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		va_list args;
		va_start(args, p_pcFormat);

		force::DisguisedCallerFormat(m_pFunction, p_pDestination, p_unParameterCount, p_pcFormat, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::Clone().
	*/
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaStaticFunction<_RETURN, _ARGS...>>(m_pFunction);
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
	/**	Defines the address to the static function.	*/
	_RETURN(*m_pFunction)(_ARGS...);
};

}
}
}