#pragma once

#include <cstring>
#include <cstdint>

#include "biaInterpreterRule.hpp"
#include "biaInterpreterIdentifiers.hpp"
#include "utf8.h"


namespace bia
{
namespace grammar
{

enum STRING_CUSTOM_PARAMETER_FLAGS : uint64_t
{
	SCPF_RAW_STRING = 1ui64 << 63,
	SCPF_MASK = 0xffffffffui64
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

	//Starting whitespace
	if (_FLAGS & STARTING_WHITESPACE_OPT_TOKEN)
	{
		TokenOutput output{};

		CharsetToken<Charset_whitespace, OPTIONAL_TOKEN>(p_pcBuffer, p_iSize, p_params, output);

		if (output.iTokenSize)
		{
			p_pcBuffer += output.iTokenSize;
			p_output.iBufferOffset += output.iTokenSize;
			p_iSize -= output.iTokenSize;
		}
	}

	p_output.iTokenSize = p_params.pRules[_RULE].RunRule(p_pcBuffer, p_iSize, p_params);
	p_output.iCustom = _CUSTOM;

	return p_output.iTokenSize ? SUCCESS : ERROR;
}

template<uint64_t _FLAGS>
inline ACTION IdentifierToken(const char * p_pcBuffer, size_t p_iSize, TokenParams, TokenOutput & p_output)
{
	constexpr auto SUCCESS = _FLAGS & FILLER_TOKEN ? (_FLAGS & LOOPING_TOKEN ? ACTION::DONT_REPORT_AND_LOOP : ACTION::DONT_REPORT) : (_FLAGS & LOOPING_TOKEN ? ACTION::REPORT_AND_LOOP : ACTION::REPORT);
	constexpr auto ERROR = _FLAGS & OPTIONAL_TOKEN ? ACTION::DONT_REPORT : ACTION::ERROR;

	//Limit length
	/*if (p_iSize > BIA_MAX_IDENTIFIER_LENGTH)
		p_output.iTokenSize = BIA_MAX_IDENTIFIER_LENGTH;*/

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

	auto pcDelimitor = "";
	size_t iDelimitor = 0;
	uint32_t fFlags = 0;

	//Determine delimitor and quote
	while (p_iSize--)
	{
		++p_output.iBufferOffset;

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
				else
					pcDelimitor = p_pcBuffer;
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
				else
					pcDelimitor = p_pcBuffer;
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

	//Raw string
	if (fFlags & F_RAW_STRING)
	{
		p_output.iCustom = SCPF_RAW_STRING;

		while (p_iSize--)
		{
			switch (*p_pcBuffer++)
			{
			case ')':
				//Check delimitor size + quote
				if (p_iSize < iDelimitor + 1)
					return ERROR;
				else if (!memcmp(pcDelimitor, p_pcBuffer, iDelimitor))
				{
					if (!(fFlags & F_SINGLE_QUOTE) && p_pcBuffer[iDelimitor] == '"' ||
						fFlags & F_SINGLE_QUOTE && p_pcBuffer[iDelimitor] == '\'')
					{
						p_output.iBufferPadding = iDelimitor + 2;

						return SUCCESS;
					}
				}
			default:
				++p_output.iTokenSize;

				break;
			}
		}
	}
	else
	{
		const auto cpcEnd = p_pcBuffer + p_iSize;
		const auto cpcBegin = p_pcBuffer;

		while (p_pcBuffer < cpcEnd)
		{
			try
			{
				switch (utf8::next(p_pcBuffer, cpcEnd))
				{
				case '\\':
					utf8::advance(p_pcBuffer, 1, cpcEnd);

					break;
				case '\'':
					if (fFlags & F_SINGLE_QUOTE)
					{
						p_output.iBufferPadding = 1;
						p_output.iTokenSize = p_pcBuffer - cpcBegin - 1;

						return SUCCESS;
					}
				case '"':
					if (!(fFlags & F_SINGLE_QUOTE))
					{
						p_output.iBufferPadding = 1;
						p_output.iTokenSize = p_pcBuffer - cpcBegin - 1;

						return SUCCESS;
					}
				default:
					break;
				}
			}
			catch (...)
			{
				return ERROR;
			}
		}
	}
	
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
		//case '�':
		case '~':
		case '#':
		case '!':
		//case '�':
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

	p_output.iCustom = NI_INTEGER;

	//First digit
	if (p_output.iTokenSize < p_iSize)
	{
		if (p_pcBuffer[p_output.iTokenSize] > '0' && p_pcBuffer[p_output.iTokenSize] <= '9')
			++p_output.iTokenSize;
		else if (p_pcBuffer[p_output.iTokenSize] == '0')
		{
			if (++p_output.iTokenSize < p_iSize && p_pcBuffer[p_output.iTokenSize] == '.')
			{
				p_output.iCustom = NI_DOUBLE;
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
		else if (p_pcBuffer[p_output.iTokenSize] == '.' && p_output.iCustom == NI_INTEGER)
			p_output.iCustom = NI_DOUBLE;
		else if ((p_pcBuffer[p_output.iTokenSize] == 'f' || p_pcBuffer[p_output.iTokenSize] == 'F') && p_output.iCustom == NI_DOUBLE)
		{
			p_output.iCustom = NI_FLOAT;
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