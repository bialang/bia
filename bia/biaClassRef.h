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

template<typename _CLASS>
class BiaClassRef final : public BiaMember
{
public:
	/**
	* Constructor.
	*
	* @remarks	This is a 'pass constructor' meaning that function/member cannot be accessed. In order to do so the members has to be defined first.
	*
	* @param	[in]	p_pClass	Defines an instance of the class. Ownership will be transferred.
	*/
	/*inline BiaClassRef(_CLASS * p_pClass)
	{
		m_pReference = p_pClass;
	}
	inline BiaClassRef(_CLASS & p_class)
	{
		m_pReference = &p_class;
	}*/
	inline BiaClassRef(_CLASS * p_pClass, std::shared_ptr<members> p_pMembers) : m_pMembers(std::move(p_pMembers))
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
};

template<typename _CLASS>
class BiaClassRef<const _CLASS> final : public BiaMember
{
public:
	/**
	* Constructor.
	*
	* @remarks	This is a 'pass constructor' meaning that function/member cannot be accessed. In order to do so the members has to be defined first.
	*
	* @param	[in]	p_pClass	Defines an instance of the class. Ownership will be transferred.
	*/
	/*inline BiaClassRef(const _CLASS * p_pClass)
	{
		m_pReference = p_pClass;
	}
	inline BiaClassRef(const _CLASS & p_class)
	{
		m_pReference = &p_class;
	}*/
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