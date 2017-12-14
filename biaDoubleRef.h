#pragma once

#include "biaNativeVariable.h"
#include "biaNumberBase.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<>
class BiaNativeVariable<double*> final : public BiaNumberBase
{
public:
	inline BiaNativeVariable(double & p_data) : m_prData(&p_data) {}
	inline BiaNativeVariable(double * p_data) : m_prData(p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown double type.");
	}
	inline virtual void Print() const override
	{
		printf("%f", *m_prData);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<double*>(m_prData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		return NativeHelper<bool, true, false>([this](auto p_right) { *m_prData = static_cast<double>(p_right); }, p_pRight);
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
		return NativeOperatorHelperFloat<double>(p_uiOperator, *m_prData, p_pDestination, p_pRight);
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE | F_NATIVE_DOUBLE;
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
		return p_type == NATIVE_TYPE::DOUBLE;
	}

private:
	double * m_prData;
};

template<>
class BiaNativeVariable<const double*> final : public BiaNumberBase
{
public:
	inline BiaNativeVariable(const double & p_data) : m_prData(&p_data) {}
	inline BiaNativeVariable(const double * p_data) : m_prData(p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown double type.");
	}
	inline virtual void Print() const override
	{
		printf("%f", *m_prData);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<const double*>(m_prData);

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
	inline virtual int SelfOperator(unsigned int p_uiOperator, void * p_pDestination) override
	{
		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE | F_NATIVE_DOUBLE;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return const_cast<double*>(m_prData);
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_prData;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst && p_type == NATIVE_TYPE::DOUBLE;
	}

private:
	const double * m_prData;
};

}
}
}
}