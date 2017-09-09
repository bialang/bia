#pragma once

#include "biaNativeVariable.h"
#include "biaNumberBase.h"
#include "biaDouble.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<>
class BiaNativeVariable<float*> final : public BiaNumberBase
{
public:
	inline BiaNativeVariable(float & p_data) : m_prData(&p_data) {}
	inline BiaNativeVariable(float * p_data) : m_prData(p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown float ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%f", *m_prData);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<float*>(*m_prData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		return NativeHelper<bool, true, false>([this](auto p_right) { *m_prData = static_cast<float>(p_right); }, p_pRight);
	}
	inline virtual bool Inc() override
	{
		++*m_prData;

		return true;
	}
	inline virtual bool Dec() override
	{
		--*m_prData;

		return true;
	}
	inline virtual int Conditional() const override
	{
		return *m_prData != 0.0 ? 1 : 0;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		return NativeOperatorHelperFloat<float>(p_uiOperator, *m_prData, p_pDestination, p_pRight);
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE | F_NATIVE_FLOAT;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return m_prData;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_prData;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::FLOAT;
	}

private:
	float * m_prData;
};

template<>
class BiaNativeVariable<const float*> final : public BiaNumberBase
{
public:
	inline BiaNativeVariable(const float & p_data) : m_prData(&p_data) {}
	inline BiaNativeVariable(const float * p_data) : m_prData(p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown float ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%f", *m_prData);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<const float*>(*m_prData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
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
	inline virtual int Conditional() const override
	{
		return *m_prData != 0.0 ? 1 : 0;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE | F_NATIVE_FLOAT;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return const_cast<float*>(m_prData);
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_prData;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst && p_type == NATIVE_TYPE::FLOAT;
	}

private:
	const float * m_prData;
};

}
}
}
}