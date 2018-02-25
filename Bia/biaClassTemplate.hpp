#pragma once

#include <cstdio>
#include <memory>

#include "biaMember.hpp"
#include "biaUndefined.hpp"
#include "biaException.hpp"


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
	inline BiaClassTemplate()
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
	virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) override;
	virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override;
	virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, const char * p_szFormat, ...) override;
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
	virtual bool IsType(const std::type_info & p_type) const override;
	virtual int GetNativeType() const override;
	inline virtual int32_t Test() override
	{
		throw exception::BadCallException("Cannot be tested.");
	}
	virtual BiaMember * GetMember(const char * p_szName) override;

public:
	virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override;
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) override;

private:
	std::shared_ptr<void> m_pMembers;
};

}
}
}