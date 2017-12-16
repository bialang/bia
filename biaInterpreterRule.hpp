#pragma once

#include <stdint.h>

#include "biaException.hpp"
#include "biaReportBundle.hpp"


namespace bia
{
namespace api
{
namespace grammar
{

constexpr uint64_t NONE = 0;
constexpr uint64_t FILLER_TOKEN = 0x1;
constexpr uint64_t OPTIONAL_TOKEN = 0x2;
constexpr uint64_t LOOPING_TOKEN = 0x4;
constexpr uint64_t STARTING_WHITESPACE_OPT_TOKEN = 0x8;

enum class ACTION
{
	REPORT,
	DONT_REPORT,
	REPORT_AND_LOOP,
	DONT_REPORT_AND_LOOP,
	ERROR
};

class BiaInterpreterRule;

struct TokenParams
{
	BiaReportBundle * pBundle;
	BiaInterpreterRule * pRules;
	Report::token_id iTokenId;
};

struct TokenOutput
{
	size_t iTokenSize;
	size_t iBufferOffset;
	size_t iBufferPadding;
	Report::custom_parameter iCustom;
};

typedef ACTION(*bia_token_function)(const char*, size_t, TokenParams, TokenOutput&);

class BiaInterpreterRule
{
public:
	enum FLAGS : uint32_t
	{
		F_NONE = 0,
		F_OR = 0x1,
		F_WRAP_UP = 0x2,
		F_DONT_REPORT_EMPTY = 0x4
	};


	/**
	 * Constructor.
	*/
	inline BiaInterpreterRule()
	{
		m_iMaxElements = 0;
		m_fFlags = 0;

		m_ppTokens = nullptr;
	}
	/**
	 * Move-constructor.
	 *
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	inline BiaInterpreterRule(BiaInterpreterRule && p_move)
	{
		m_iMaxElements = p_move.m_iMaxElements;
		m_fFlags = p_move.m_fFlags;
		p_move.m_iMaxElements = 0;
		p_move.m_fFlags = 0;

		m_ppTokens = p_move.m_ppTokens;
		p_move.m_ppTokens = nullptr;
	}
	inline ~BiaInterpreterRule()
	{
		delete[] m_ppTokens;
	}
	/**
	 * Resets the rule.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_iElements	Defines the new amount of elements the rule can have.
	 * @param	p_fFlags	Defines the flags.
	 *
	 * @throws	bia::exception::ImplementationException	Thrown when the element size is not allowed.
	*/
	inline void Reset(Report::token_id p_iElements, uint32_t p_fFlags = F_NONE)
	{
		if (p_iElements & static_cast<Report::token_id>(-1) << Report::TOKEN_BITS)
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid token size.");

		m_iMaxElements = p_iElements;
		m_fFlags = p_fFlags;

		delete[] m_ppTokens;
		m_ppTokens = new bia_token_function[p_iElements]{};
	}
	/**
	 * Runs this rule.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_pcBuffer	Defines a buffer which this rule should be run on.
	 * @param	p_iSize	Defines the size of the buffer.
	 * @param	p_params	Defines parameters for the token functions.
	 *
	 * @return	The amount of bytes processed of the buffer.
	*/
	inline size_t RunRule(const char * p_pcBuffer, size_t p_iSize, TokenParams p_params)
	{
		const auto iSizeToBegin = p_params.pBundle->Size();
		Report::token_id iCursor = 0;
		auto iRuleId = static_cast<Report::rule_id>(this - p_params.pRules);
		auto WrapUp = [&] {
			auto unTokenAdded = p_params.pBundle->Size() - iSizeToBegin;

			if (m_fFlags & F_WRAP_UP)
			{
				if (unTokenAdded > 1)
				{
					//Edit beginning token
					auto pBegin = p_params.pBundle->Begin() + iSizeToBegin;

					pBegin->content.children = { pBegin, p_params.pBundle->End() };

					//End
					auto end = *pBegin;

					end.type = Report::TYPE::END;

					p_params.pBundle->AddReport(std::move(end));
				}
				//Dont report empty child
				else if (m_fFlags & F_DONT_REPORT_EMPTY)
				{
					if (unTokenAdded)
						p_params.pBundle->Reset(iSizeToBegin);
				}
				//Empty child
				else if (unTokenAdded == 1)
				{
					//Edit beginning token
					auto pBegin = p_params.pBundle->Begin() + iSizeToBegin;

					pBegin->content.children = { pBegin, pBegin };
					pBegin->type = Report::TYPE::EMPTY_CHILD;
				}
			}
		};

		//Wrap up
		if (m_fFlags & F_WRAP_UP)
		{
			Report begin{};

			begin.type = Report::TYPE::BEGIN;
			begin.unRuleId = iRuleId;
			begin.unTokenId = p_params.iTokenId;
			
			p_params.pBundle->AddReport(std::move(begin));
		}

		//Or loop
		if (m_fFlags & F_OR)
		{
			size_t iAccount = 0;
			bool bLoop;

			while (iCursor < m_iMaxElements)
			{
				do
				{
					TokenOutput output{};

					p_params.iTokenId = iCursor + 1;

					switch (m_ppTokens[iCursor++](p_pcBuffer, p_iSize, p_params, output))
					{
					case ACTION::REPORT:
					{
						Report token{};

						token.type = Report::TYPE::TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = iRuleId;
						token.unTokenId = iCursor;
						token.unCustomParameter = output.iCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT:
						WrapUp();

						return output.iTokenSize + output.iBufferOffset + output.iBufferPadding + iAccount;
					case ACTION::REPORT_AND_LOOP:
					{
						Report token{};

						token.type = Report::TYPE::TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = iRuleId;
						token.unTokenId = iCursor;
						token.unCustomParameter = output.iCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT_AND_LOOP:
					{
						auto iOffset = output.iTokenSize + output.iBufferOffset + output.iBufferPadding;

						iAccount += iOffset;
						p_pcBuffer += iOffset;
						p_iSize -= iOffset;

						bLoop = true;
						--iCursor;

						continue;
					}
					case ACTION::ERROR:
						break;
					}

					bLoop = false;
				} while (bLoop);
			}

			//Clear errors
			p_params.pBundle->Reset(iSizeToBegin);

			return 0;
		}
		//And loop
		else
		{
			const auto ciSize = p_iSize;
			bool bLoop;

			while (iCursor < m_iMaxElements)
			{
				do
				{
					TokenOutput output{};

					p_params.iTokenId = iCursor + 1;

					switch (m_ppTokens[iCursor++](p_pcBuffer, p_iSize, p_params, output))
					{
					case ACTION::REPORT:
					{
						Report token{};

						token.type = Report::TYPE::TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = iRuleId;
						token.unTokenId = iCursor;
						token.unCustomParameter = output.iCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT:
					{
						auto iOffset = output.iTokenSize + output.iBufferOffset + output.iBufferPadding;

						p_pcBuffer += iOffset;
						p_iSize -= iOffset;

						break;
					}
					case ACTION::REPORT_AND_LOOP:
					{
						Report token{};

						token.type = Report::TYPE::TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = iRuleId;
						token.unTokenId = iCursor;
						token.unCustomParameter = output.iCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT_AND_LOOP:
					{
						auto iOffset = output.iTokenSize + output.iBufferOffset + output.iBufferPadding;

						p_pcBuffer += iOffset;
						p_iSize -= iOffset;

						bLoop = true;
						--iCursor;

						continue;
					}
					case ACTION::ERROR:
						//Clear errors
						p_params.pBundle->Reset(iSizeToBegin);

						return 0;
					}

					bLoop = false;
				} while (bLoop);
			}

			WrapUp();

			return ciSize - p_iSize;
		}
	}
	/**
	 * Sets a token.
	 *
	 * @since	2.39.81.472
	 * @date	10-Sep-17
	 *
	 * @param	p_iTokenId	Defines the if of the token. Must be smaller than the previously defined max elements.
	 * @param   p_pToken	Defines the token.
	 *
	 * @throws	bia::exception::ImplementationException	Thrown when the element limit has been reached.
	 *
	 * @return  This.
	*/
	inline BiaInterpreterRule & SetToken(Report::token_id p_iTokenId, bia_token_function p_pToken)
	{
		if (--p_iTokenId < m_iMaxElements)
		{
			m_ppTokens[p_iTokenId] = p_pToken;

			return *this;
		}
		else
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid rule element size.");
	}
	inline BiaInterpreterRule & operator=(BiaInterpreterRule p_right)
	{
		m_iMaxElements = p_right.m_iMaxElements;
		m_fFlags = p_right.m_fFlags;
		p_right.m_iMaxElements = 0;
		p_right.m_fFlags = 0;

		delete[] m_ppTokens;
		m_ppTokens = p_right.m_ppTokens;
		p_right.m_ppTokens = nullptr;

		return *this;
	}


private:
	Report::token_id m_iMaxElements;
	uint32_t m_fFlags;

	bia_token_function * m_ppTokens;
};

}
}
}