#pragma once

#include <memory>

#include "biaGlobal.h"
#include "biaMember.h"
#include "biaException.h"
#include "biaMemberHolder.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClass final : public BiaMember
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pClass	Defines an instance of the class. Ownership will be transferred.
	 * @param	p_pMembers	Defines the members of the class.
	 * @param	p_pOperators	Defines the operators of the class.
	*/
	inline BiaClass(_CLASS * p_pClass, std::shared_ptr<members> p_pMembers, std::shared_ptr<operators> p_pOperators) : m_pMembers(std::move(p_pMembers)), m_pOperators(std::move(p_pOperators))
	{
		m_pInstance = p_pClass;
	}
	template<typename T>
	inline BiaClass(T&&)
	{
		throw exception::UnknownException("Unknown tpye for class.");
	}
	inline ~BiaClass()
	{
		delete m_pInstance;
	}
	/**
	 * @see	BiaMember::Print().
	*/
	inline virtual void Print() const override
	{
		printf("<%s at 0x%p>", typeid(decltype(*this)).name(), this);
	}
	virtual void SetParameter(SET_PARAMETER, SET_PARAMETER_DATA) override {}
	inline virtual bool GetParameter(GET_PARAMETER, GET_PARAMETER_DATA&) override
	{
		return false;
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		return false;
	}
	inline virtual bool Store(BiaMember*) override
	{
		return false;
	}
	inline virtual bool Inc() override
	{
		return false;
	}
	inline virtual bool Dec() override
	{
		return false;
	}
	inline virtual bool LoadObject(const machine::BiaKey & p_object, void * p_pScopeReferenceDestination) override
	{
		auto pResult = m_pMembers->find(p_object);

		if (pResult != m_pMembers->end())
		{
			new(p_pScopeReferenceDestination) machine::scope::BiaScopeReference(&pResult->second);

			return true;
		}

		return false;
	}
	inline virtual int Conditional() const override
	{
		return -1;
	}
	/**
	 * @see	BiaMember::Operator().
	*/
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		auto pResult = m_pOperators->find(p_uiOperator);

		//Operator was found
		if (pResult != m_pOperators->end())
			return pResult->second->ExecuteOperation(m_pInstance, p_pRight, p_pDestination);

		return -1;
	}
	inline virtual int SelfOperator(unsigned int, void*) override
	{
		return -1;
	}
	inline virtual int Execute(void*, void*, BiaParameter*, const BiaParameter*, machine::BiaMachineContext*) override
	{
		return -1;
	}
	inline virtual int Call(const machine::BiaKey & p_function, void * p_pReturnDestination, BiaParameter * p_pBegin, const BiaParameter * p_pEnd) override
	{
		auto pResult = m_pMembers->find(p_function);

		if (pResult != m_pMembers->end())
			return pResult->second.member.GetMember()->Execute(p_pReturnDestination, const_cast<std::remove_cv<_CLASS>::type*>(m_pInstance), p_pBegin, p_pEnd, nullptr);

		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_CLASS;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return const_cast<std::remove_cv<_CLASS>::type*>(m_pInstance);
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_pInstance;
	}
	inline virtual TYPE IsType(const std::type_info & p_type, unsigned int p_unPointerRank, bool) const override
	{
		if (p_unPointerRank == 0)
			return BIA_TYPE_COMPARE(p_type, typeid(_CLASS)) ? TYPE::NATIVE : TYPE::INVALID;
		else if (p_unPointerRank == 1)
			return BIA_TYPE_COMPARE(p_type, typeid(_CLASS)) ? TYPE::POINTER : TYPE::INVALID;
		else
			return TYPE::INVALID;
	}
	inline virtual bool IsType(NATIVE_TYPE, bool) const override
	{
		return false;
	}

private:
	_CLASS * m_pInstance;

	std::shared_ptr<members> m_pMembers;
	std::shared_ptr<operators> m_pOperators;
};

}
}
}
}