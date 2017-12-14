#pragma once

#include <memory>
#include <unordered_map>

#include "biaGlobal.h"
#include "biaClass.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClassRef final : public BiaMember
{
public:
	/**
	* Constructor.
	*
	* @param	[in]	p_pClass	Defines an instance of the class. Ownership will be transferred.
	* @param	p_pMembers	Defines the members of the class.
	* @param	p_pOperators	Defines the operators of the class.
	*/
	inline BiaClassRef(_CLASS * p_pClass, std::shared_ptr<members> p_pMembers, std::shared_ptr<operators> p_pOperators) : m_pMembers(std::move(p_pMembers)), m_pOperators(std::move(p_pOperators))
	{
		m_pReference = p_pClass;
	}
	template<typename T>
	inline BiaClassRef(T&&)
	{
		throw exception::UnknownException("Unknown tpye for class ref.");
	}
	/**
	* @see	bia::api::framework::BiaMember::Print().
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
			return pResult->second->ExecuteOperation(m_pReference, p_pRight, p_pDestination);

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
			return pResult->second.member.GetMember()->Execute(p_pReturnDestination, m_pReference, p_pBegin, p_pEnd, nullptr);

		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_CLASS;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return m_pReference;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_pReference;
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
	_CLASS * m_pReference;

	std::shared_ptr<members> m_pMembers;
	std::shared_ptr<operators> m_pOperators;
};

template<typename _CLASS>
class BiaClassRef<const _CLASS> final : public BiaMember
{
public:
	/**
	* Constructor.
	*
	* @param	[in]	p_pClass	Defines an instance of the class. Ownership will be transferred.
	* @param	p_pMembers	Defines the members of the class.
	*/
	inline BiaClassRef(const _CLASS * p_pClass, std::shared_ptr<members> p_pMembers) : m_pMembers(std::move(p_pMembers))
	{
		m_pReference = p_pClass;
	}
	template<typename T>
	inline BiaClassRef(T&&)
	{
		throw exception::UnknownException("Unknown tpye for class ref.");
	}
	/**
	* @see	bia::api::framework::BiaMember::Print().
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
	inline virtual int Operator(unsigned int, void*, BiaMember*) override
	{
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
		//TODO: call only const functions
		if (pResult != m_pMembers->end())
			return pResult->second.member.GetMember()->Execute(p_pReturnDestination, const_cast<_CLASS*>(m_pReference), p_pBegin, p_pEnd, nullptr);

		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_CLASS;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return const_cast<_CLASS*>(m_pReference);
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_pReference;
	}
	inline virtual TYPE IsType(const std::type_info & p_type, unsigned int p_unPointerRank, bool p_bConst) const override
	{
		if (!p_bConst)
			return TYPE::INVALID;
		else if (p_unPointerRank == 0)
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
	const _CLASS * m_pReference;

	std::shared_ptr<members> m_pMembers;
};

}
}
}
}