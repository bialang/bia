#pragma once

#include "biaMember.h"
#include "biaClass.h"
#include "biaClassRef.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace object
{

template<typename _CLASS>
class BiaClassRawBase : public BiaMember
{
public:
	inline BiaClassRawBase(_CLASS * p_pInstance) : m_pInstance(p_pInstance) {}
	/**
	* @see	bia::api::framework::BiaMember::Print().
	*/
	inline virtual void Print() const override
	{
		printf("<%s at 0x%p>", typeid(decltype(*this)).name(), this);
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
		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_CLASS;
	}

protected:
	_CLASS * m_pInstance;


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
};


template<typename _CLASS>
class BiaClassRaw final : public BiaClassRawBase<_CLASS>
{
public:
	inline BiaClassRaw(_CLASS * p_pInstance) : BiaClassRawBase<_CLASS>(p_pInstance) {}
	template<typename T>
	inline BiaClassRaw(T&&) : BiaClassRawBase<_CLASS>(nullptr)
	{
		throw exception::UnknownException("Unknown type for class.");
	}
	inline ~BiaClassRaw()
	{
		delete m_pInstance;
	}
	inline virtual void SetParameter(SET_PARAMETER p_type, SET_PARAMETER_DATA p_data) override
	{
		//Promote
		if (p_type == SET_PARAMETER::CLASS_PROMOTE_PARAMS)
		{
			auto pTmp = m_pInstance;

			m_pInstance = nullptr;

			this->~BiaClassRaw();
			new(this) BiaClass<_CLASS>(pTmp, *p_data.classPromoteParams.pMembers, *p_data.classPromoteParams.pOperators);
		}
	}
	inline virtual bool GetParameter(GET_PARAMETER p_type, GET_PARAMETER_DATA & p_data) override
	{
		if (p_type == GET_PARAMETER::CLASS_HASH_CODE)
		{
			p_data.iClassHashCode = typeid(_CLASS).hash_code();

			return true;
		}

		return false;
	}
};

template<typename _CLASS>
class BiaClassRawRef final : public BiaClassRawBase<_CLASS>
{
public:
	inline BiaClassRawRef(_CLASS * p_pInstance) : BiaClassRawBase<_CLASS>(p_pInstance) {}
	inline BiaClassRawRef(_CLASS & p_instance) : BiaClassRawBase<_CLASS>(&p_instance) {}
	template<typename T>
	inline BiaClassRawRef(T&&) : BiaClassRawBase<_CLASS>(nullptr)
	{
		throw exception::UnknownException("Unknown type for class ref.");
	}
	inline virtual void SetParameter(SET_PARAMETER p_type, SET_PARAMETER_DATA p_data) override
	{
		//Promote
		if (p_type == SET_PARAMETER::CLASS_PROMOTE_PARAMS)
		{
			auto pTmp = m_pInstance;

			m_pInstance = nullptr;

			this->~BiaClassRawRef();
			new(this) BiaClassRef<_CLASS>(pTmp, *p_data.classPromoteParams.pMembers, *p_data.classPromoteParams.pOperators);
		}
	}
	inline virtual bool GetParameter(GET_PARAMETER p_type, GET_PARAMETER_DATA & p_data) override
	{
		if (p_type == GET_PARAMETER::CLASS_HASH_CODE)
		{
			p_data.iClassHashCode = typeid(_CLASS).hash_code();

			return true;
		}

		return false;
	}
};

template<typename _CLASS>
class BiaClassRawRef<const _CLASS> final : public BiaClassRawBase<const _CLASS>
{
public:
	inline BiaClassRawRef(const _CLASS * p_pInstance) : BiaClassRawBase<const _CLASS>(p_pInstance) {}
	inline BiaClassRawRef(const _CLASS & p_instance) : BiaClassRawBase<const _CLASS>(&p_instance) {}
	template<typename T>
	inline BiaClassRawRef(T&&) : BiaClassRawBase<const _CLASS>(nullptr)
	{
		throw exception::UnknownException("Unknown type for class ref.");
	}
	inline virtual void SetParameter(SET_PARAMETER p_type, SET_PARAMETER_DATA p_data) override
	{
		//Promote
		if (p_type == SET_PARAMETER::CLASS_PROMOTE_PARAMS)
		{
			auto pTmp = m_pInstance;

			m_pInstance = nullptr;

			this->~BiaClassRawRef();
			new(this) BiaClassRef<const _CLASS>(pTmp, *p_data.classPromoteParams.pMembers, *p_data.classPromoteParams.pOperators);
		}
	}
	inline virtual bool GetParameter(GET_PARAMETER p_type, GET_PARAMETER_DATA & p_data) override
	{
		if (p_type == GET_PARAMETER::CLASS_HASH_CODE)
		{
			p_data.iClassHashCode = typeid(_CLASS).hash_code();

			return true;
		}

		return false;
	}
};

}
}
}
}