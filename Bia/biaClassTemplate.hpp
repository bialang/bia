#pragma once

#include <cstdio>
#include <memory>

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaStaticFunction.hpp"
#include "biaException.hpp"
#include "biaClassContext.hpp"
#include "biaClass.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClassTemplate : public BiaMember
{
public:
	inline BiaClassTemplate(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager) : m_pClassContext(new BiaClassContext(p_pAllocator, p_pNameManager))
	{
	}

	// Inherited via BiaMember
	inline virtual void Undefine() override
	{
		this->~BiaClassWrapper();

		new(this) BiaUndefined();
	}
	inline virtual void Print() override
	{
		printf("<%s at %p>", typeid(decltype(*this)).name(), this);
	}
	inline virtual void Call(BiaMember*, BiaMember * p_pDestination) override
	{
		p_pDestination->~BiaMember();

		new(p_pDestination) BiaClass<_CLASS>(m_pClassContext);
	}
	inline virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override
	{
		///TODO
	}
	inline virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, const char * p_szFormat, ...) override
	{
		///TODO
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
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{
		throw exception::OperatorException("Unsupported operation on class template.");
	}
	inline virtual void Clone(BiaMember * p_pDestination) override
	{
		new(p_pDestination) BiaClassTemplate<_CLASS>(*this);
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

		auto pMember = new(m_pClassContext->GetAllocator()->AllocateBlocks(1, machine::BiaAllocator::MEMORY_TYPE::NORMAL)) executable::BiaStaticFunction<_RETURN, _ARGS...>(p_pFunction);

		m_pClassContext->SetMember(p_stName, pMember);

		return this;
	}

public:
	inline virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override
	{
		throw exception::BadCastException("Invalid cast on uncastable object.");
	}
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Invalid cast on uncastable object.");
	}

private:
	std::shared_ptr<BiaClassContext> m_pClassContext;
};

}
}
}