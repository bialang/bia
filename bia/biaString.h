#pragma once

#include <string>

#include "biaNativeVariable.h"
#include "biaMemberHolder.h"
#include "biaStringBase.h"
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
class BiaNativeVariable<std::string> final : public BiaStringBase
{
public:
	inline BiaNativeVariable(std::string && p_stString) : m_stData(std::move(p_stString)) {}
	inline BiaNativeVariable(const std::string & p_stString) : m_stData(p_stString) {}
	inline BiaNativeVariable(const char * p_pcString, size_t p_iSize) : m_stData(p_pcString, p_iSize) {}
	inline BiaNativeVariable(const char * p_pszString) : m_stData(p_pszString) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown string type.");
	}
	inline virtual void Print() const override
	{
		printf("%s", m_stData.c_str());
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<std::string>(m_stData);

		return true;
	}
	inline virtual bool Store(BiaMember * p_pRight) override
	{
		const std::string * pstTmp;

		if (p_pRight->Cast(pstTmp))
		{
			m_stData.assign(*pstTmp);

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

				stResult.reserve(m_stData.length() + iRightSize);
				stResult.assign(m_stData).append(*ppszString, iRightSize);

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
				m_stData.append(*ppszString);

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
		if (p_function == std::string("length"))
		{
			(new(p_pReturnDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<long long>>(m_stData.length());

			return 1;
		}

		return -1;
	}

protected:
	friend BiaNativeVariable<const char*>;


	inline virtual void * LoadNative() override
	{
		return &m_stData;
	}
	inline virtual void * LoadPtr(PTR_TYPE p_type) override
	{
		if (p_type == PTR_TYPE::CONST_CHAR)
		{
			m_pszTmp = m_stData.data();

			return &m_pszTmp;
		}
		else
		{
			m_pstData = &m_stData;

			return &m_pstData;
		}
	}

private:
	std::string m_stData;
	std::string * m_pstData;

	const char * m_pszTmp;
};

}
}
}
}