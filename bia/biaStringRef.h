#pragma once

#include <string>

#include "biaStringBase.h"
#include "biaNativeVariable.h"
#include "biaMemberHolder.h"
#include "biaLong.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<>
class BiaNativeVariable<std::string*> final : public BiaStringBase
{
public:
	inline BiaNativeVariable(std::string * p_stString) : m_pstData(p_stString) {}
	inline BiaNativeVariable(std::string & p_stString) : m_pstData(&p_stString) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown string type.");
	}
	inline virtual void Print() const override
	{
		printf("%s", m_pstData->c_str());
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<std::string*>(m_pstData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		const std::string * pstTmp;

		if (p_pRight->Cast(pstTmp))
		{
			m_pstData->assign(*pstTmp);

			return true;
		}

		return false;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		switch (p_uiOperator)
		{
		case O_PLUS:
		{
			const char ** ppszString;

			if (p_pRight->Cast<const char*>(ppszString))
			{
				std::string stResult;
				auto iRightSize = std::char_traits<char>::length(*ppszString);

				stResult.reserve(m_pstData->length() + iRightSize);
				stResult.assign(*m_pstData).append(*ppszString, iRightSize);

				new(p_pDestination) BiaNativeVariable<std::string>(std::move(stResult));

				return 1;
			}

			break;
		}
		case O_ASSIGN_PLUS:
		{
			const char ** ppszString;

			if (p_pRight->Cast<const char*>(ppszString))
			{
				m_pstData->append(*ppszString);

				return 0;
			}

			break;
		}
		default:
			break;
		}

		return -1;
	}
	inline virtual int Call(const machine::BiaKey & p_function, void * p_pReturnDestination, BiaParameter*, const BiaParameter*) override
	{
		return -1;
	}

protected:
	friend BiaNativeVariable<const char*>;


	inline virtual void * LoadNative() override
	{
		return m_pstData;
	}
	inline virtual void * LoadPtr(PTR_TYPE p_type) override
	{
		if (p_type == PTR_TYPE::CONST_CHAR)
		{
			m_pszTmp = m_pstData->data();

			return &m_pszTmp;
		}
		else
			return &m_pstData;
	}

private:
	std::string * m_pstData;

	const char * m_pszTmp;
};

template<>
class BiaNativeVariable<const std::string*> final : public BiaStringBase
{
public:
	inline BiaNativeVariable(const std::string * p_stString) : m_pstData(p_stString) {}
	inline BiaNativeVariable(const std::string & p_stString) : m_pstData(&p_stString) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown string type.");
	}
	inline virtual void Print() const override
	{
		printf("%s", m_pstData->c_str());
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<const std::string*>(m_pstData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		return false;
	}
	inline virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) override
	{
		switch (p_uiOperator)
		{
		case O_PLUS:
		{
			const char ** ppszString;

			if (p_pRight->Cast<const char*>(ppszString))
			{
				std::string stResult;
				auto iRightSize = std::char_traits<char>::length(*ppszString);

				stResult.reserve(m_pstData->length() + iRightSize);
				stResult.assign(*m_pstData).append(*ppszString, iRightSize);

				new(p_pDestination) BiaNativeVariable<std::string>(std::move(stResult));

				return 1;
			}

			break;
		}
		default:
			break;
		}

		return -1;
	}
	inline virtual int Call(const machine::BiaKey&, void*, BiaParameter*, const BiaParameter*) override
	{
		return -1;
	}

protected:
	friend BiaNativeVariable<const char*>;


	inline virtual void * LoadNative() override
	{
		return const_cast<std::string*>(m_pstData);
	}
	inline virtual void * LoadPtr(PTR_TYPE p_type) override
	{
		if (p_type == PTR_TYPE::CONST_CHAR)
		{
			m_pszTmp = m_pstData->data();

			return &m_pszTmp;
		}
		else
			return &m_pstData;
	}
	inline virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const override
	{
		return p_bConst && p_type == NATIVE_TYPE::STRING;
	}

private:
	const std::string * m_pstData;

	const char * m_pszTmp;
};

}
}
}
}