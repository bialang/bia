#pragma once

#include "biaMember.hpp"
#include "biaException.hpp"


namespace bia
{
namespace framework
{

class BiaUnknown final : public BiaMember
{
public:
	/**
	 * @see	BiaMember::Print().
	*/
	virtual void Print() override;
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, void * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, void * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, void * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, void * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	virtual void OperatorSelfCall(uint32_t p_unOperator) override;
	/**
	 * @see	BiaMember::Clone().
	*/
	virtual void Clone(void * p_pDestination) override;
	/**
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info & p_type) const override;
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	virtual int GetNativeType() const override;

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override;
	/**
	 * @see	BiaMember::GetData().
	*/
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) override;
};

}
}