#pragma once

#include <cstring>
#include <stdint.h>

#include "biaInterpreterRule.h"
#include "biaInterpreterIdentifiers.h"
#include "utf8.h"


namespace bia
{
namespace api
{
namespace grammar
{


struct StringCustomParameter
{
	const char * pcBuffer;
	uint64_t ullSize;
};

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

template<uint32_t _RULE, uint64_t _FLAGS, uint64_t _CUSTOM = 0>
inline ACTION RulePointerToken(const char * p_pcBuffer, size_t p_iSize, TokenParams p_params, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & (OPTIONAL_TOKEN | LOOPING_TOKEN) ? ACTION::DONT_REPORT : ACTION::ERROR;

	p_output.iTokenSize = p_params.pRules[_RULE].RunRule(p_pcBuffer, p_iSize, p_params);
	p_output.ullCustom = _CUSTOM;

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

	enum FLAGS : uint32_t
	{
		F_SINGLE_QUOTE = 0x1,	/**	If set ', otherwise ".	*/
		F_QUOTE_SET = 0x2,
		F_RAW_STRING = 0x4,
	};

	constexpr uint64_t cullSize = 256;
	thread_local char acLocalBuffer[cullSize];
	thread_local StringCustomParameter customParameter;
	const auto cpcDestEnd = acLocalBuffer + cullSize;
	const auto cpcEnd = p_pcBuffer + p_iSize;
	auto pcDest = acLocalBuffer;
	auto pcDelimitor = "";
	size_t iDelimitor = 0;
	uint32_t fFlags = 0;

	//Determine delimitor and quote
	while (p_iSize--)
	{
		switch (*p_pcBuffer++)
		{
		case 'R':
			//Add 'R' to delimitor
			if (fFlags & F_QUOTE_SET)
				++iDelimitor;
			else if (!(fFlags & F_RAW_STRING))
				fFlags |= F_RAW_STRING;
			else
				return ERROR;

			break;
		case '"': //Double quote
			//No quote set yet
			if (!(fFlags & F_QUOTE_SET))
			{
				fFlags |= F_QUOTE_SET;

				//Terminate
				if (!(fFlags & F_RAW_STRING))
					goto gt_break;
			}
			//Add to delimitor
			else
				++iDelimitor;

			break;
		case '\'': //Single quote
			//No quote set yet
			if (!(fFlags & F_QUOTE_SET))
			{
				fFlags |= F_QUOTE_SET | F_SINGLE_QUOTE;

				//Terminate
				if (!(fFlags & F_RAW_STRING))
					goto gt_break;
			}
			//Add to delimitor
			else
				++iDelimitor;

			break;
		case '(':
			//Terminate delimitor
			if (fFlags & F_QUOTE_SET)
				goto gt_break;

			return ERROR;
		default:
			//Add delimitor
			if (fFlags & F_QUOTE_SET)
				++iDelimitor;
			else
				return ERROR;

			break;
		}
	}

gt_break:;

	auto pcLast = p_pcBuffer;
	auto bEscape = false;
	auto Maker = [](size_t p_iSize, auto p_lambda) {
		if (pcDest + p_iSize <= cpcDestEnd)
			p_lambda();
		else
			return false;

		return true;
	};

	//Main checking loop
	while (p_pcBuffer < cpcEnd)
	{
		auto pcTmp = p_pcBuffer;

		if (bEscape)
		{


			switch (utf8::next(p_pcBuffer, cpcEnd))
			{
			case 'n':
				*pcDest++ = '\n';
				++pcLast;

				break;
			case 't':
				*pcDest++ = '\t';
				++pcLast;

				break;
			case 'r':
				*pcDest++ = '\r';
				++pcLast;

				break;
			case 'b':
				*pcDest++ = '\b';
				++pcLast;
			default:
				break;
			}

			bEscape = false;
		}
		else
		{
			switch (utf8::next(p_pcBuffer, cpcEnd))
			{
			case '\\':
				memcpy(pcDest, pcLast, pcTmp - pcLast);

				pcDest += pcTmp - pcLast;
				pcLast = p_pcBuffer;
				bEscape = true;
			default:
				break;
			}
		}
	}

	//On success
	p_output.ullCustom = static_cast<uint64_t>(&customParameter);

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