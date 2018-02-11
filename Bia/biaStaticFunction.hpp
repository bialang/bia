#pragma once

#include <new>
#include <type_traits>

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

template<typename _RETURN, typename... _ARGS>
class BiaStaticFunction
{
public:
	template<typename _DUMMY>
	inline explicit BiaStaticFunction(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}
};

template<typename _RETURN, typename... _ARGS>
class BiaStaticFunction<_RETURN(*)(_ARGS...)> final : public BiaFunction
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
	 * @see	BiaMember::Undefine().
	*/
	virtual void Undefine() override
	{
		//Destroy this
		this->~BiaStaticFunction();

		//Undefine
		new(this) BiaUndefined();
	}
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
	inline virtual void Call(BiaMember * p_pDestination) override
	{
		//Parameters are required
		if (sizeof...(_ARGS))
			throw exception::ArgumentException("Argument signature is not matching.");
		else
			force::DisguisedCaller(m_pFunction, p_pDestination);
	}
	/**
	 * @see	BiaMember::CallCount().
	*/
	inline virtual void CallCount(BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		va_list args;
		va_start(args, p_unParameterCount);

		force::DisguisedCallerCount(m_pFunction, p_pDestination, p_unParameterCount, args);

		va_end(args);
	}
	/**
	 * @see	BiaMember::CallFormat().
	*/
	inline virtual void CallFormat(BiaMember * p_pDestination, const char * p_szFormat, ...) override
	{
		throw exception::BadCallException("Invalid function call on native type.");
		/*va_list parameters;
		va_start(parameters, p_szFormat);

		while (true)
		{
			switch (*p_szFormat++)
			{
			case 0:
				goto gt_break;
			case 'M':
				va_arg(parameters, BiaMember*);
			case 'i':
				va_arg(parameters, int32_t);
			case 'I':
				va_arg(parameters, int64_t);
			case 'f':
				va_arg(parameters, float);
			case 'd':
				va_arg(parameters, double);
			case 's':
			default:
				break;
			}
		}

	gt_break:;

		va_end(parameters);*/
	}
	/**
	 * @see	BiaMember::Clone().
	*/
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		new(p_pDestination) BiaStaticFunction<_RETURN(*)(_ARGS...)>(m_pFunction);
	}
	/**
	 * @see	BiaMember::IsType().
	*/
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
	}
	/**
	 * @see	BiaMember::Test().
	*/
	virtual int32_t Test() override
	{
		return static_cast<int32_t>(m_pFunction != nullptr);
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
	_RETURN(*m_pFunction)(_ARGS...);
};

}
}
}