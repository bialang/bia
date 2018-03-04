#pragma once

#include "biaMember.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class BiaNativeVariable : public BiaMember
{
public:
	/**
	 * @see	BiaMember::Undefine().
	*/
	virtual void Undefine() override;
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
	virtual void CallFormat(BiaMember*, BiaMember*, parameter_count, const char*, ...) override;
	/**
	 * @see	BiaMember::Instantiate().
	*/
	virtual void Instantiate(BiaMember*) override;
	/**
	 * @see	BiaMember::InstantiateCount().
	*/
	virtual void InstantiateCount(BiaMember*, parameter_count, ...) override;
	/**
	 * @see	BiaMember::InstantiateFormat().
	*/
	virtual void InstantiateFormat(BiaMember*, parameter_count, const char*, ...) override;
	/**
	 * @see	BiaMember::IsType().
	*/
	virtual bool IsType(const std::type_info & p_type) const override;
	/**
	 * @see	BiaMember::GetMember().
	*/
	virtual BiaMember * GetMember(const char * p_szName) override;

protected:
	/**
	 * @see	BiaMember::GetData().
	*/
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) override;
};

}
}
}