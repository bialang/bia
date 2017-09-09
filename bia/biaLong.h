#pragma once

#include "biaNativeVariable.h"
#include "biaNumberBase.h"
#include "biaFloat.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<>
class BiaNativeVariable<long long> final : public BiaNumberBase
{
public:
	inline BiaNativeVariable(long long p_llData) : m_llData(p_llData) {}
	inline BiaNativeVariable(unsigned long long p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(long p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(unsigned long p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(int p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(unsigned int p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(short p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(unsigned short p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(char p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(signed char p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(unsigned char p_data) : m_llData(static_cast<long long>(p_data)) {}
	inline BiaNativeVariable(bool p_data) : m_llData(static_cast<long long>(p_data)) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long type.");
	}
	inline virtual void Print() const override
	{
		printf("%lli", m_llData);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<long long>(m_llData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		return NativeHelper<bool, true, false>([this](auto p_right) { m_llData = static_cast<long long>(p_right); }, p_pRight);
	}
	inline virtual bool Inc() override
	{
		++m_llData;

		return true;
	}
	inline virtual bool Dec() override
	{
		--m_llData;

		return true;
	}
	inline virtual int Conditional() const override
	{
		return m_llData != 0 ? 1 : 0;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		return NativeOperatorHelperIntegral<long long>(p_uiOperator, m_llData, p_pDestination, p_pRight);
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE | F_NATIVE_LONG;
	}

protected:
	inline virtual void * LoadNative() override
	{
		return &m_llData;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		m_pllData = &m_llData;

		return &m_pllData;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::LONG ||
			p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}

private:
	long long m_llData;
	long long * m_pllData;
};

}
}
}
}