#pragma once

#include "biaString.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<>
class BiaNativeVariable<const char*> final : public BiaStringBase
{
public:
	inline BiaNativeVariable(const char * p_pszString) : m_pszString(p_pszString) {}
	template<typename T>
	inline BiaNativeVariable(T&&)
	{
		throw exception::UnknownException("Unknown string type.");
	}
	inline virtual void Print() const override
	{
		printf("%s", m_pszString);
	}
	inline virtual bool Clone(void * p_pDestination) override
	{
		new(p_pDestination) BiaNativeVariable<const char*>(m_pszString);

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
				auto iLeftSize = std::char_traits<char>::length(m_pszString);
				auto iRightSize = std::char_traits<char>::length(*ppszString);

				stResult.reserve(iLeftSize + iRightSize);
				stResult.assign(m_pszString, iLeftSize).append(*ppszString, iRightSize);

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
	inline virtual int Call(const machine::BiaKey & p_function, void * p_pReturnDestination, BiaParameter*, const BiaParameter*) override
	{
		return -1;
	}

protected:
	inline virtual void * LoadNative() override
	{
		//Promote to string
		auto pszString = m_pszString;

		this->~BiaNativeVariable();
		return (new(this) BiaNativeVariable<std::string>(pszString))->LoadNative();
	}
	inline virtual void * LoadPtr(PTR_TYPE p_type) override
	{
		if (p_type == PTR_TYPE::CONST_CHAR)
			return &m_pszString;
		else
		{
			//Promote to string
			auto pszString = m_pszString;

			this->~BiaNativeVariable();
			return (new(this) BiaNativeVariable<std::string>(pszString))->LoadPtr(p_type);
		}
	}

private:
	const char * m_pszString;
};

}
}
}
}