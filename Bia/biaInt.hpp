#pragma once

#include <cstdint>

#include "biaMember.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace framework
{

class BiaInt final : public BiaMember
{
public:
	inline BiaInt(int64_t p_llValue)
	{
		m_llValue = p_llValue;
	}

	inline virtual void Print() override
	{
		machine::link::Print_I(m_llValue);
	}
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) override
	{

	}
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override
	{

	}
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	virtual void OperatorSelfCall(uint32_t p_unOperator) override
	{

	}
	/**
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info & p_type) const override
	{
		return false;
	}

private:
	int64_t m_llValue;
};

}
}