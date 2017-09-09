#pragma once

#include "biaNativeVariable.h"
#include "biaNumberBase.h"
#include "biaLong.h"
#include "biaException.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<typename T>
class BiaNativeVariableRefBase : public BiaNumberBase
{
public:
	inline BiaNativeVariableRefBase(T * p_data) : m_pData(p_data) {}
	inline virtual bool Clone(void * p_pDestination) override final
	{
		new(p_pDestination) BiaNativeVariable<T*>(m_pData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override final
	{
		return NativeHelper<bool, true, false>([this](auto p_right) { *m_pData = static_cast<T>(p_right); }, p_pRight);
	}
	inline virtual bool Inc() override
	{
		++*m_pData;

		return true;
	}
	inline virtual bool Dec() override
	{
		--*m_pData;

		return true;
	}
	inline virtual int Conditional() const override final
	{
		return *m_pData != 0 ? 1 : 0;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override final
	{
		return NativeOperatorHelperIntegral<T>(p_uiOperator, *m_pData, p_pDestination, p_pRight);
	}
	inline virtual unsigned int GetFlags() const override final
	{
		return F_VARIABLE | F_NATIVE_LONG;
	}

protected:
	T * m_pData;


	inline virtual void * LoadNative() override final
	{
		return m_pData;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override final
	{
		return &m_pData;
	}
};

template<typename T>
class BiaNativeVariableRefBase<const T> : public BiaNumberBase
{
public:
	inline BiaNativeVariableRefBase(const T * p_data) : m_pData(p_data) {}
	inline virtual bool Clone(void * p_pDestination) override final
	{
		new(p_pDestination) BiaNativeVariable<const T*>(m_pData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override final
	{
		return false;
	}
	inline virtual bool Inc() override final
	{
		return false;
	}
	inline virtual bool Dec() override final
	{
		return false;
	}
	inline virtual int Conditional() const override final
	{
		return *m_pData != 0 ? 1 : 0;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override final
	{
		return -1;
	}
	inline virtual unsigned int GetFlags() const override final
	{
		return F_VARIABLE | F_NATIVE_LONG;
	}

protected:
	const T * m_pData;


	inline virtual void * LoadNative() override final
	{
		return const_cast<T*>(m_pData);
	}
	inline virtual void * LoadPtr(PTR_TYPE) override final
	{
		return &m_pData;
	}
};

template<>
class BiaNativeVariable<long long*> final : BiaNativeVariableRefBase<long long>
{
public:
	inline BiaNativeVariable(long long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(long long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%lli", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::LONG ||
			p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const long long*> final : BiaNativeVariableRefBase<const long long>
{
public:
	inline BiaNativeVariable(const long long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const long long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%lli", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::LONG ||
			p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<unsigned long long*> final : BiaNativeVariableRefBase<unsigned long long>
{
public:
	inline BiaNativeVariable(unsigned long long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(unsigned long long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%llu", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::LONG ||
			p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const unsigned long long*> final : BiaNativeVariableRefBase<const unsigned long long>
{
public:
	inline BiaNativeVariable(const unsigned long long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const unsigned long long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%llu", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::LONG ||
			p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<long*> final : BiaNativeVariableRefBase<long>
{
public:
	inline BiaNativeVariable(long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%li", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const long*> final : BiaNativeVariableRefBase<const long>
{
public:
	inline BiaNativeVariable(const long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%li", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<unsigned long*> final : BiaNativeVariableRefBase<unsigned long>
{
public:
	inline BiaNativeVariable(unsigned long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(unsigned long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%lu", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const unsigned long*> final : BiaNativeVariableRefBase<const unsigned long>
{
public:
	inline BiaNativeVariable(const unsigned long * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const unsigned long & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned long ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%lu", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<int*> final : BiaNativeVariableRefBase<int>
{
public:
	inline BiaNativeVariable(int * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(int & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown int ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%i", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const int*> final : BiaNativeVariableRefBase<const int>
{
public:
	inline BiaNativeVariable(const int * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const int & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown int ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%i", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<unsigned int*> final : BiaNativeVariableRefBase<unsigned int>
{
public:
	inline BiaNativeVariable(unsigned int * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(unsigned int & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned int ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%u", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const unsigned int*> final : BiaNativeVariableRefBase<const unsigned int>
{
public:
	inline BiaNativeVariable(const unsigned int * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const unsigned int & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned int ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%u", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::INT ||
			p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<short*> final : BiaNativeVariableRefBase<short>
{
public:
	inline BiaNativeVariable(short * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(short & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown short ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%hi", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const short*> final : BiaNativeVariableRefBase<const short>
{
public:
	inline BiaNativeVariable(const short * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const short & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown short ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%hi", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<unsigned short*> final : BiaNativeVariableRefBase<unsigned short>
{
public:
	inline BiaNativeVariable(unsigned short * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(unsigned short & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned short ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%hu", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const unsigned short*> final : BiaNativeVariableRefBase<const unsigned short>
{
public:
	inline BiaNativeVariable(const unsigned short * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const unsigned short & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned short ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%hu", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst &&
			(p_type == NATIVE_TYPE::SHORT ||
			p_type == NATIVE_TYPE::BYTE);
	}
};

template<>
class BiaNativeVariable<char*> final : BiaNativeVariableRefBase<char>
{
public:
	inline BiaNativeVariable(char * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(char & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown char ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%c", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<signed char*> final : BiaNativeVariableRefBase<signed char>
{
public:
	inline BiaNativeVariable(signed char * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(signed char & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown signed char ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%c", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const signed char*> final : BiaNativeVariableRefBase<const signed char>
{
public:
	inline BiaNativeVariable(const signed char * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const signed char & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown signed char ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%c", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<unsigned char*> final : BiaNativeVariableRefBase<unsigned char>
{
public:
	inline BiaNativeVariable(unsigned char * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(unsigned char & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned char ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%c", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const unsigned char*> final : BiaNativeVariableRefBase<const unsigned char>
{
public:
	inline BiaNativeVariable(const unsigned char * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const unsigned char & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown unsigned char ref type.");
	}
	inline virtual void Print() const override
	{
		printf("%c", *m_pData);
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<bool*> final : BiaNumberBase
{
public:
	inline BiaNativeVariable(bool * p_data) : m_pData(p_data) {}
	inline BiaNativeVariable(bool & p_data) : m_pData(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown bool ref type.");
	}
	inline virtual void Print() const override
	{
		if (*m_pData)
			putchar('1');
		else
			putchar('0');
	}
	inline virtual bool Clone(void * p_pDestination) override final
	{
		new(p_pDestination) BiaNativeVariable<bool*>(m_pData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override final
	{
		return NativeHelper<bool, true, false>([this](auto p_right) { *m_pData = p_right; }, p_pRight);
	}
	inline virtual bool Inc() override
	{
		return false;
	}
	inline virtual bool Dec() override
	{
		return false;
	}
	inline virtual int Conditional() const override final
	{
		return *m_pData ? 1 : 0;
	}
	inline virtual int Operator(unsigned int, void*, BiaMember*) override final
	{
		return -1;
	}
	inline virtual unsigned int GetFlags() const override
	{
		return F_VARIABLE | F_NATIVE_BYTE;
	}

protected:
	bool * m_pData;


	inline virtual void * LoadNative() override
	{
		return m_pData;
	}
	inline virtual void * LoadPtr(PTR_TYPE) override
	{
		return &m_pData;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool) const override
	{
		return p_type == NATIVE_TYPE::BYTE;
	}
};

template<>
class BiaNativeVariable<const bool*> final : BiaNativeVariableRefBase<const bool>
{
public:
	inline BiaNativeVariable(const bool * p_data) : BiaNativeVariableRefBase(p_data) {}
	inline BiaNativeVariable(const bool & p_data) : BiaNativeVariableRefBase(&p_data) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown bool ref type.");
	}
	inline virtual void Print() const override
	{
		if (*m_pData)
			putchar('1');
		else
			putchar('0');
	}

protected:
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst && p_type == NATIVE_TYPE::BYTE;
	}
};

}
}
}
}