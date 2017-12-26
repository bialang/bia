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
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info & p_type) const override;
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	virtual bool OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual bool OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	virtual bool OperatorSelfCall(uint32_t p_unOperator) override;
};

}
}