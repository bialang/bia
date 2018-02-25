#pragma once

#include <cstdio>
#include <memory>

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaClassContext.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClass : public BiaMember
{
public:
	inline BiaClass(std::shared_ptr<BiaClassContext> p_pClassContext) : m_pClassContext(std::move(p_pClassContext))
	{
	}

	// Inherited via BiaMember
	inline virtual void Undefine() override
	{
		this->~BiaClass();

		new(this) BiaUndefined();
	}
	inline virtual void Print() override
	{
		printf("<%s at %p>", typeid(decltype(*this)).name(), this);
	}
	inline virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) override;
	inline virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override;
	inline virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, const char * p_szFormat, ...) override;
	inline virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override;
	inline virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override;
	inline virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override;
	inline virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override;
	inline virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override;
	inline virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	inline virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	inline virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override;
	inline virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override;
	inline virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override;
	inline virtual void OperatorSelfCall(uint32_t p_unOperator) override;
	inline virtual void Clone(BiaMember * p_pDestination) override;
	inline virtual bool IsType(const std::type_info & p_type) const override
	{
		return typeid(_CLASS) == p_type;
	}
	inline virtual int GetNativeType() const override
	{
		return NTF_NONE;
	}
	inline virtual int32_t Test() override
	{
		throw exception::BadCallException("Not implemented.");
	}
	inline virtual BiaMember * GetMember(const char * p_szName) override
	{
		if (auto pMember = m_pClassContext->GetMember(p_szName))
			return pMember;

		throw exception::SymbolException("Unknown member.");
	}

protected:
	inline virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override
	{
		throw exception::BadCastException("Not implemented.");
	}
	inline virtual void * GetData(const std::type_info & p_type, bool p_bConst) override
	{
		throw exception::BadCastException("Not implemented.");
	}

private:
	std::shared_ptr<BiaClassContext> m_pClassContext;
};

}
}
}