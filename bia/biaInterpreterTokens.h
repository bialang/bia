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

template<typename T, uint64_t _FLAGS>
inline ACTION KeywordToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	if (p_iSize >= T::Size())
	{
		if (memcmp(p_pcBuffer, T::Token(), T::Size()))
			return ERROR;
		else
		{
			p_output.iTokenSize = T::Size();

			return SUCCESS;
		}
	}
	else
		return ERROR;
}

template<typename T, uint64_t _FLAGS, size_t _MIN = 0, size_t _MAX = 0>
inline ACTION CharsetToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? ACTION::DONT_REPORT : ACTION::REPORT;
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	while (p_iSize)
	{
		if (!FastFind<T::Size()>(p_pcBuffer[p_output.iTokenSize], T::Token()))
			break;

		++p_output.iTokenSize;
	}

	return p_output.iTokenSize ? SUCCESS : ERROR;
}

template<size_t _RULE, uint64_t _FLAGS>
inline ACTION RulePointerToken(const char * p_pcBuffer, size_t p_iSize, TokenParams p_params, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & (OPTIONAL_TOKEN | LOOPING_TOKEN) ? ACTION::DONT_REPORT : ACTION::ERROR;

	p_output.iTokenSize = p_params.pRules[_RULE].RunRule(p_pcBuffer, p_iSize, p_params);

	return p_output.iTokenSize ? SUCCESS : ERROR;
}

template<uint64_t _FLAGS>
inline ACTION IdentifierToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	//Limit length
	if (p_iSize > BIA_MAX_IDENTIFIER_LENGTH)
		p_output.iTokenSize = BIA_MAX_IDENTIFIER_LENGTH;

	if (p_output.iTokenSize < p_iSize)
	{
		if ((p_pcBuffer[p_output.iTokenSize] >= 'a' && p_pcBuffer[p_output.iTokenSize] <= 'z') ||
			(p_pcBuffer[p_output.iTokenSize] >= 'A' && p_pcBuffer[p_output.iTokenSize] <= 'Z') ||
			p_pcBuffer[p_output.iTokenSize] == '_')
			++p_output.iTokenSize;
		else
			return ERROR;
	}
	else
		return ERROR;

	while (p_output.iTokenSize < p_iSize)
	{
		if ((p_pcBuffer[p_output.iTokenSize] >= 'a' && p_pcBuffer[p_output.iTokenSize] <= 'z') ||
			(p_pcBuffer[p_output.iTokenSize] >= 'A' && p_pcBuffer[p_output.iTokenSize] <= 'Z') ||
			(p_pcBuffer[p_output.iTokenSize] >= '0' && p_pcBuffer[p_output.iTokenSize] <= '9') ||
			p_pcBuffer[p_output.iTokenSize] == '_')
			++p_output.iTokenSize;
		else
			break;
	}

	return SUCCESS;
}

template<uint64_t _FLAGS>
inline ACTION StringValueToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);



	return ERROR;
}

template<uint64_t _FLAGS>
inline ACTION CustomOperatorToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	if (p_iSize > 4)
		p_iSize = 4;

	for (auto i = p_pcBuffer; p_output.iTokenSize < p_iSize; ++i)
	{
		switch (*i)
		{
		case '>':
		case '<':
		case '+':
		case '-':
		case '^':
		case '°':
		case '~':
		case '#':
		case '!':
		case '§':
		case '$':
			++p_output.iTokenSize;

			break;
		case ' ':
		default:
			return p_output.iTokenSize ? SUCCESS : ERROR;
		}
	}

	return ERROR;
}

template<uint64_t _FLAGS>
inline ACTION NumberValueToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR);

	//Check for minus
	if (p_iSize && *p_pcBuffer == '-')
		++p_output.iTokenSize;

	p_output.ullCustom = NI_INTEGER;

	//First digit
	if (p_output.iTokenSize < p_iSize)
	{
		if (p_pcBuffer[p_output.iTokenSize] > '0' && p_pcBuffer[p_output.iTokenSize] <= '9')
			++p_output.iTokenSize;
		else if (p_pcBuffer[p_output.iTokenSize] == '0')
		{
			if (++p_output.iTokenSize < p_iSize && p_pcBuffer[p_output.iTokenSize] == '.')
			{
				p_output.ullCustom = NI_DOUBLE;
				++p_output.iTokenSize;
			}
			else
				return SUCCESS;
		}
		else
			return ERROR;
	}
	else
		return ERROR;

	for (; p_output.iTokenSize < p_iSize; ++p_output.iTokenSize)
	{
		if (p_pcBuffer[p_output.iTokenSize] >= '0' && p_pcBuffer[p_output.iTokenSize] <= '9');
		else if (p_pcBuffer[p_output.iTokenSize] == '.' && p_output.ullCustom == NI_INTEGER)
			p_output.ullCustom = NI_DOUBLE;
		else if ((p_pcBuffer[p_output.iTokenSize] == 'f' || p_pcBuffer[p_output.iTokenSize] == 'F') && p_output.ullCustom == NI_DOUBLE)
		{
			p_output.ullCustom = NI_FLOAT;
			++p_output.iTokenSize;

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