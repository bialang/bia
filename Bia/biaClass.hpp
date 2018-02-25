#pragma once

#include <cstdio>

#include "biaMember.hpp"
#include "biaUndefined.hpp"


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
	virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) override;
	virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override;
	virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, const char * p_szFormat, ...) override;
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override;
	virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override;
	virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override;
	virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override;
	virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override;
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override;
	virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override;
	virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override;
	virtual void OperatorSelfCall(uint32_t p_unOperator) override;
	virtual void Clone(BiaMember * p_pDestination) override;
	virtual bool IsType(const std::type_info & p_type) const override;
	virtual int GetNativeType() const override;
	virtual int32_t Test() override;
	virtual BiaMember * GetMember(const char * p_szName) override;

protected:
	inline virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override
	{
		return nullptr;
	}
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) override;
};

}
}
}