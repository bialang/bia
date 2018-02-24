#pragma once

#include "biaMember.hpp"
#include "biaException.hpp"


namespace bia
{
namespace framework
{

class BiaUndefined final : public BiaMember
{
public:
	/**
	 * @see	BiaMember::Undefine().
	*/
	virtual void Undefine() override;
	/**
	 * @see	BiaMember::Print().
	*/
	virtual void Print() override;
	/**
	 * @see	BiaMember::Call().
	*/
	virtual void Call(BiaMember*, BiaMember*) override;
	/**
	 * @see	BiaMember::CallCount().
	*/
	virtual void CallCount(BiaMember*, BiaMember*, parameter_count, ...) override;
	/**
	 * @see	BiaMember::CallFormat().
	*/
	virtual void CallFormat(BiaMember*, BiaMember*, const char*, ...) override;
	/**
	 * @see	BiaMember::OperatorCall().
	*/
	virtual void OperatorCall(uint32_t, BiaMember*, BiaMember*) override;
	/**
	 * @see	BiaMember::OperatorCallInt_32().
	*/
	virtual void OperatorCallInt_32(uint32_t, int32_t, BiaMember*) override;
	/**
	 * @see	BiaMember::OperatorCallInt_64().
	*/
	virtual void OperatorCallInt_64(uint32_t, int64_t, BiaMember*) override;
	/**
	 * @see	BiaMember::OperatorCallFloat().
	*/
	virtual void OperatorCallFloat(uint32_t, float, BiaMember*) override;
	/**
	 * @see	BiaMember::OperatorCallDouble().
	*/
	virtual void OperatorCallDouble(uint32_t, double, BiaMember*) override;
	/**
	 * @see	BiaMember::OperatorAssignCall().
	*/
	virtual void OperatorAssignCall(uint32_t, BiaMember*) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_32().
	*/
	virtual void OperatorAssignCallInt_32(uint32_t, int32_t) override;
	/**
	 * @see	BiaMember::OperatorAssignCallInt_64().
	*/
	virtual void OperatorAssignCallInt_64(uint32_t, int64_t) override;
	/**
	 * @see	BiaMember::OperatorAssignCallFloat().
	*/
	virtual void OperatorAssignCallFloat(uint32_t, float) override;
	/**
	 * @see	BiaMember::OperatorAssignCallDouble().
	*/
	virtual void OperatorAssignCallDouble(uint32_t, double) override;
	/**
	 * @see	BiaMember::OperatorSelfCall().
	*/
	virtual void OperatorSelfCall(uint32_t) override;
	/**
	 * @see	BiaMember::Clone().
	*/
	virtual void Clone(BiaMember*) override;
	/**
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info&) const override;
	/**
	 * @see	BiaMember::GetNativeType().
	*/
	virtual int GetNativeType() const override;
	/**
	 * @see	BiaMember::Test().
	*/
	virtual int32_t Test() override;
	/**
	 * @see	BiaMember::GetMember().
	*/
	virtual BiaMember * GetMember(const char * p_szName) override;

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	virtual void * GetNativeData(NATIVE_TYPE) override;
	/**
	 * @see	BiaMember::GetData().
	*/
	virtual void * GetData(const std::type_info&, bool) override;
};

}
}