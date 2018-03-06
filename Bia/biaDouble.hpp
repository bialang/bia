#pragma once

#include "biaNativeVariable.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class BiaDouble final : public BiaNativeVariable
{
public:
	inline explicit BiaDouble(float p_rValue) : m_rValue(static_cast<double>(p_rValue)) {}
	inline explicit BiaDouble(double p_rValue) : m_rValue(p_rValue) {}
	template<typename _DUMMY>
	inline explicit BiaDouble(_DUMMY)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid parameter.");
	}

	/**
	 * @see	BiaMember::Print().
	*/
	virtual void Print() override;
	/**
	* @see	BiaMember::OperatorCall().
	*/
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorCallString().
	*/
	virtual void OperatorCallString(uint32_t p_unOperator, const char * p_szRight, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) override;
	/**
	 * @see	BiaMember::OperatorAssignCallString().
	*/
	virtual void OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight) override;
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	virtual void OperatorSelfCall(uint32_t p_unOperator) override;
	/**
	 * @see	BiaMember::Clone().
	*/
	virtual void Clone(BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	virtual int GetNativeType() const override;
	/**
	 * @see	BiaMember::Test().
	*/
	virtual int32_t Test() override;
	/**
	 * @see	BiaMember::TestCall().
	*/
	virtual int32_t TestCall(uint32_t p_unOperator, BiaMember * p_pRight) override;
	/**
	 * @see	BiaMember::TestCallInt_32().
	*/
	virtual int32_t TestCallInt_32(uint32_t p_unOperator, int32_t p_nRight) override;
	/**
	 * @see	BiaMember::TestCallInt_64().
	*/
	virtual int32_t TestCallInt_64(uint32_t p_unOperator, int64_t p_llRight) override;
	/**
	 * @see	BiaMember::TestCallFloat().
	*/
	virtual int32_t TestCallFloat(uint32_t p_unOperator, float p_rRight) override;
	/**
	 * @see	BiaMember::TestCallDouble().
	*/
	virtual int32_t TestCallDouble(uint32_t p_unOperator, double p_rRight) override;
	/**
	 * @see	BiaMember::TestCallString().
	*/
	virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) override;

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	virtual void * GetNativeData(NATIVE_TYPE p_nativeType) override;

private:
	double m_rValue;
};

}
}
}