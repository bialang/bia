#pragma once

#include <cstdio>
#include <memory>
#include <new>
#include <string>

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaStaticFunction.hpp"
#include "biaException.hpp"
#include "biaClassMemberHolder.hpp"
#include "biaClass.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClassTemplate final : public BiaMember
{
public:
	inline BiaClassTemplate(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager) : m_pClassMemberHolder(new BiaClassMemberHolder(p_pAllocator, p_pNameManager))
	{
	}

	// Inherited via BiaMember
	inline virtual void Undefine() override
	{
		ReplaceObject<BiaUndefined>();
	}
	inline virtual void Print() override
	{
		printf("<%s at %p>", typeid(decltype(*this)).name(), this);
	}
	inline virtual void Call(BiaMember*, BiaMember * p_pDestination) override
	{
		throw exception::BadCallException("not implemented");
	}
	inline virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		throw exception::BadCallException("not implemented");
	}
	inline virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		throw exception::BadCallException("not implemented");
	}
	/**
	 * @see	BiaMember::Instantiate().
	*/
	inline virtual void Instantiate(BiaMember * p_pDestination) override
	{
		auto pInstance = static_cast<_CLASS*>(m_pClassMemberHolder->GetInitiator()->Instantiate());

		p_pDestination->ReplaceObject<BiaClass<_CLASS>>(m_pClassMemberHolder, std::shared_ptr<_CLASS>(pInstance));
	}
	/**
	 * @see	BiaMember::InstantiateCount().
	*/
	inline virtual void InstantiateCount(BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		va_list args;
		va_start(args, p_unParameterCount);

		auto pInstance = static_cast<_CLASS*>(m_pClassMemberHolder->GetInitiator()->InstantiateCount(p_unParameterCount, args));

		p_pDestination->ReplaceObject<BiaClass<_CLASS>>(m_pClassMemberHolder, std::shared_ptr<_CLASS>(pInstance));

		va_end(args);
	}
	/**
	 * @see	BiaMember::InstantiateFormat().
	*/
	inline virtual void InstantiateFormat(BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override
	{
		va_list args;
		va_start(args, p_pcFormat);

		auto pInstance = static_cast<_CLASS*>(m_pClassMemberHolder->GetInitiator()->InstantiateFormat(p_unParameterCount, p_pcFormat, args));

		p_pDestination->ReplaceObject<BiaClass<_CLASS>>(m_pClassMemberHolder, std::shared_ptr<_CLASS>(pInstance));

		va_end(args);
	}
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		p_pDestination->ReplaceObject<BiaClassTemplate<_CLASS>>(*this);
	}
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
	}
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
	}
	inline virtual int32_t Test() override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCall().
	*/
	inline virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallInt_32().
	*/
	inline virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallInt_64().
	*/
	inline virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallFloat().
	*/
	inline virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallDouble().
	*/
	inline virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	/**
	 * @see	BiaMember::TestCallString().
	*/
	inline virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
		throw exception::SymbolException("Unknown member.");
	}
	/**
	 * Sets a static function.
	 *
	 * @since	3.55.116.671
	 * @date	25-Feb-18
	 *
	 * @param	p_stName	Defines the name of the member.
	 * @param	p_pFunction	
	 *
	 * @return	This.
	*/
	template<typename _RETURN, typename... _ARGS>
	inline BiaClassTemplate * SetFunction(const std::string & p_stName, _RETURN(*p_pFunction)(_ARGS...))
	{
		///TODO: check name

		m_pClassMemberHolder->SetMember<executable::BiaStaticFunction<_RETURN, _ARGS...>>(p_stName, p_pFunction);

		return this;
	}
	/**
	 * Sets the constructor.
	 *
	 * @since	3.60.122.690
	 * @date	13-Mar-18
	 *
	 * @return	This.
	*/
	template<typename... _ARGS>
	inline BiaClassTemplate * SetConstructor()
	{
		m_pClassMemberHolder->SetConstructor<_CLASS, _ARGS...>();

		return this;
	}

public:
	inline virtual void * GetNativeData(native::NATIVE_TYPE p_nativeType) override
	{
		throw exception::BadCastException("Invalid cast on uncastable object.");
	}
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Invalid cast on uncastable object.");
	}

private:
	std::shared_ptr<BiaClassMemberHolder> m_pClassMemberHolder;
};

}
}
}