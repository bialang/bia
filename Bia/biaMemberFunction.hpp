#pragma once

#include <new>

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

template<typename, typename = void, typename...>
class BiaMemberFunction
{
public:
	template<typename _DUMMY>
	inline explicit BiaMemberFunction(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}
};

template<typename _CLASS, typename _RETURN, typename... _ARGS>
class BiaMemberFunction<_RETURN(_CLASS::*)(_ARGS...)> final : public BiaFunction
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_pFunction	Defines the static function.
	*/
	inline explicit BiaMemberFunction(_RETURN(_CLASS::*p_pFunction)(_ARGS...)) : m_pFunction(p_pFunction) {}
	inline ~BiaMemberFunction() = default;

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
	inline virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) override
	{
		force::DisguisedCaller(m_pFunction, GetInstance(p_pInstance), p_pDestination);
	}
	/**
	 * @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		va_list args;
		va_start(args, p_unParameterCount);

		force::DisguisedCallerCount(m_pFunction, GetInstance(p_pInstance), p_pDestination, p_unParameterCount, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		va_list args;
		va_start(args, p_pcFormat);

		force::DisguisedCallerFormat(m_pFunction, GetInstance(p_pInstance), p_pDestination, p_unParameterCount, p_pcFormat, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::Clone().
	*/
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		new(p_pDestination) BiaMemberFunction<_RETURN(_CLASS::*)(_ARGS...)>(m_pFunction);
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
	/**	Defines the address to the member function.	*/
	_RETURN(_CLASS::*m_pFunction)(_ARGS...);


	/**
	 * Retrieves the needed instance from the member.
	 *
	 * @since	3.56.117.675
	 * @date	28-Feb-18
	 *
	 * @param	[in]	p_pInstance	Defines the member.
	 *
	 * @throws	exception::BadCastException	Thrown when the member does not hold a valid instance.
	 * @throws	exception::ArgumentException	Thrown when a nullpointer was passed.
	 *
	 * @return	The instance.
	*/
	inline _CLASS * GetInstance(BiaMember * p_pInstance)
	{
		if (p_pInstance)
		{
			if (auto pInstance = p_pInstance->Cast<_CLASS>())
				return pInstance;
			else
				throw exception::BadCastException("Invalid instance passed.");
		}
		else
			throw exception::ArgumentException("Nullpointer instance is not valid.");
	}
};

}
}
}