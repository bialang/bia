#pragma once

#include <memory>
#include <utility>
#include <type_traits>

#include "biaMember.hpp"
#include "biaAllocator.hpp"
#include "biaMemberHolder.hpp"


namespace bia
{
namespace framework
{

class BiaNamespace : public BiaMember
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the member allocator.
	 * @param	[in]	p_pNameManager	Defines the name manager.
	*/
	BiaNamespace(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager);
	
	/**
	 * Sets or adds a member.
	 *
	 * @since	3.58.119.683
	 * @date	3-Mar-18
	 *
	 * @param	p_stName	Defines the name.
	 * @param	p_args	Defines the args that should be passed to the instance.
	*/
	template<typename T, typename... _ARGS>
	inline typename std::enable_if<std::is_base_of<BiaMember, T>::value>::type SetMember(const std::string & p_stName, _ARGS &&... p_args)
	{
		m_pMemberHolder->SetMember<T>(p_stName, std::forward<_ARGS>(p_args)...);
	}
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
	virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::CallCount().
	*/
	virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override;
	/**
	 * @see	BiaMember::CallFormat().
	*/
	virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override;
	/**
	 * @see	BiaMember::Instantiate().
	*/
	virtual void Instantiate(BiaMember * p_pDestination) override;
	/**
	 * @see	BiaMember::InstantiateCount().
	*/
	virtual void InstantiateCount(BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) override;
	/**
	 * @see	BiaMember::InstantiateFormat().
	*/
	virtual void InstantiateFormat(BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) override;
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
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info & p_type) const override;
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
	/**
	 * @see	BiaMember::GetMember().
	*/
	virtual BiaMember * GetMember(const char * p_szName) override;

protected:
	/**
	 * @see	BiaMember::GetNativeData().
	*/
	virtual void * GetNativeData(native::NATIVE_TYPE p_nativeType) override;
	/**
	 * @see	BiaMember::GetData().
	*/
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) override;

private:
	std::shared_ptr<BiaMemberHolder> m_pMemberHolder;
};

}
}