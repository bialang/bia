#pragma once

#include <new>
#include <type_traits>

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaException.hpp"
#include "biaDisguisedCalled.hpp"


namespace bia
{
namespace framework
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
class BiaStaticFunction<_RETURN(*)(_ARGS...)> final : public BiaMember
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
	 * @see	BiaMember::OperatorCall().
	*/
	inline virtual void OperatorCall(uint32_t, BiaMember*, void*) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	inline virtual void OperatorCallInt_32(uint32_t, int32_t, void *) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	inline virtual void OperatorCallInt_64(uint32_t, int64_t, void*) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	inline virtual void OperatorCallFloat(uint32_t, float, void*) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	inline virtual void OperatorCallDouble(uint32_t, double, void*) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	inline virtual void OperatorAssignCallInt_32(uint32_t, int32_t) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	inline virtual void OperatorAssignCallInt_64(uint32_t, int64_t) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	inline virtual void OperatorAssignCallFloat(uint32_t, float) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	inline virtual void OperatorAssignCallDouble(uint32_t, double) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	inline virtual void OperatorSelfCall(uint32_t) override
	{
		throw exception::OperatorException("Invalid operator call on static function.");
	}
	/**
	 * @see	BiaMember::Clone().
	*/
	inline virtual void Clone(void * p_pDestination) override
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
	 * @see	BiaMember::GetNativeType().
	*/
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
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
	 * @see	BiaMember::GetNativeData().
	*/
	inline virtual void * GetNativeData(NATIVE_TYPE) override
	{
		throw exception::BadCastException("Native type is not supported.");
	}
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