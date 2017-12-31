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
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
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
};

}
}