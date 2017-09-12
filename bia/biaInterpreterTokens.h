#pragma once

#include <cstring>

#include "biaInterpreterRule.h"
#include "biaInterpreterIdentifiers.h"


namespace bia
{
namespace api
{
namespace grammar
{



template<size_t _SIZE>
inline bool FastFind(char p_cWhat, const char * p_pcSortedString)
{
	for (auto cond = p_pcSortedString + _SIZE; p_pcSortedString < cond; ++p_pcSortedString)
	{
		if (p_cWhat == *p_pcSortedString)
			return true;
	}

	return false;
}

template<typename T, int _FLAGS>
inline ACTION KeywordToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched, TokenParams, uint64_t&)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	if (p_iSize >= T::Size())
	{
		if (memcmp(p_pcBuffer, T::Token(), T::Size()))
			return ERROR;
		else
		{
			p_iOutMatched = T::Size();

			return SUCCESS;
		}
	}
	else
		return ERROR;
}

template<typename T, int _FLAGS, size_t _MIN = 0, size_t _MAX = 0>
inline ACTION CharsetToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched, TokenParams, uint64_t&)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	while (p_iSize)
	{
		if (!FastFind<T::Size()>(p_pcBuffer[p_iOutMatched], T::Token()))
			break;

		++p_iOutMatched;
	}

	return p_iOutMatched ? SUCCESS : ERROR;
}

template<size_t _RULE, int _FLAGS>
inline ACTION RulePointerToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched, TokenParams p_params, uint64_t&)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	p_iOutMatched = p_params.pRules[_RULE].RunRule(p_pcBuffer, p_iSize, p_params);

	return p_iOutMatched ? SUCCESS : ERROR;
}

template<int _FLAGS>
inline ACTION IdentifierToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched, TokenParams, uint64_t&)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	p_iOutMatched = 1;

	return SUCCESS;
}

template<int _FLAGS>
inline ACTION StringValueToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched, TokenParams, uint64_t&)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	return SUCCESS;
}

template<int _FLAGS>
inline ACTION NumberValueToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched, TokenParams, uint64_t & p_ullCustomParameter)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	//Check for minus
	if (p_iSize && *p_pcBuffer == '-')
		++p_iOutMatched;

	p_ullCustomParameter = NI_INTEGER;

	//First digit
	if (p_iOutMatched < p_iSize)
	{
		if (p_pcBuffer[p_iOutMatched] > '0' && p_pcBuffer[p_iOutMatched] <= '9')
			++p_iOutMatched;
		else if (p_pcBuffer[p_iOutMatched] == '0')
		{
			if (++p_iOutMatched < p_iSize && p_pcBuffer[p_iOutMatched] == '.')
			{
				p_ullCustomParameter = NI_DOUBLE;
				++p_iOutMatched;
			}
			else
				return SUCCESS;
		}
		else
			return ERROR;
	}
	else
		return ERROR;

	for (; p_iOutMatched < p_iSize; ++p_iOutMatched)
	{
		if (p_pcBuffer[p_iOutMatched] >= '0' && p_pcBuffer[p_iOutMatched] <= '9');
		else if (p_pcBuffer[p_iOutMatched] == '.' && p_ullCustomParameter == NI_INTEGER)
			p_ullCustomParameter = NI_DOUBLE;
		else if ((p_pcBuffer[p_iOutMatched] == 'f' || p_pcBuffer[p_iOutMatched] == 'F') && p_ullCustomParameter == NI_DOUBLE)
		{
			p_ullCustomParameter = NI_FLOAT;
			++p_iOutMatched;

			return SUCCESS;
		}
		else
			return SUCCESS;
	}

	return SUCCESS;
}

}
}
}