#pragma once

#include <stdint.h>

#include "biaException.h"
#include "biaReportBundle.h"


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
	uint32_t unTokenId;
};

struct TokenOutput
{
	size_t iTokenSize;
	size_t iBufferOffset;
	uint64_t ullCustom;
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
		m_unMaxElements = 0;
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
		m_unMaxElements = p_move.m_unMaxElements;
		m_fFlags = p_move.m_fFlags;
		p_move.m_unMaxElements = 0;
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
	 * @param	p_unElements	Defines the new amount of elements the rule can have.
	 * @param	p_fFlags	Defines the flags.
	*/
	inline void Reset(uint32_t p_unElements, uint32_t p_fFlags = F_NONE)
	{
		m_unMaxElements = p_unElements;
		m_fFlags = p_fFlags;

		delete[] m_ppTokens;
		m_ppTokens = new bia_token_function[p_unElements]{};
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
		uint32_t unCursor = 0;
		auto unRuleId = static_cast<uint32_t>(this - p_params.pRules);
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

					end.type = Report::T_END;

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
					pBegin->type = Report::T_EMPTY_CHILD;
				}
			}
		};

		//Wrap up
		if (m_fFlags & F_WRAP_UP)
		{
			Report begin{};

			begin.type = Report::T_BEGIN;
			begin.unRuleId = unRuleId;
			begin.unTokenId = p_params.unTokenId;
			
			p_params.pBundle->AddReport(std::move(begin));
		}

		//Or loop
		if (m_fFlags & F_OR)
		{
			size_t iAccount = 0;
			bool bLoop;

			while (unCursor < m_unMaxElements)
			{
				do
				{
					TokenOutput output{};

					p_params.unTokenId = unCursor + 1;

					switch (m_ppTokens[unCursor++](p_pcBuffer, p_iSize, p_params, output))
					{
					case ACTION::REPORT:
					{
						Report token{};

						token.type = Report::T_TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = unRuleId;
						token.unTokenId = unCursor;
						token.ullCustomParameter = output.ullCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT:
						WrapUp();

						return output.iTokenSize + iAccount;
					case ACTION::REPORT_AND_LOOP:
					{
						Report token{};

						token.type = Report::T_TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = unRuleId;
						token.unTokenId = unCursor;
						token.ullCustomParameter = output.ullCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT_AND_LOOP:
						iAccount += output.iTokenSize;
						p_pcBuffer += output.iTokenSize;
						p_iSize -= output.iTokenSize;
						
						bLoop = true;
						--unCursor;

						continue;
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

			while (unCursor < m_unMaxElements)
			{
				do
				{
					TokenOutput output{};

					p_params.unTokenId = unCursor + 1;

					switch (m_ppTokens[unCursor++](p_pcBuffer, p_iSize, p_params, output))
					{
					case ACTION::REPORT:
					{
						Report token{};

						token.type = Report::T_TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = unRuleId;
						token.unTokenId = unCursor;
						token.ullCustomParameter = output.ullCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT:
						p_pcBuffer += output.iTokenSize;
						p_iSize -= output.iTokenSize;

						break;
					case ACTION::REPORT_AND_LOOP:
					{
						Report token{};

						token.type = Report::T_TOKEN;
						token.content.token = { p_pcBuffer + output.iBufferOffset, output.iTokenSize };
						token.unRuleId = unRuleId;
						token.unTokenId = unCursor;
						token.ullCustomParameter = output.ullCustom;

						p_params.pBundle->AddReport(std::move(token));
					}
					case ACTION::DONT_REPORT_AND_LOOP:
						p_pcBuffer += output.iTokenSize;
						p_iSize -= output.iTokenSize;
						
						bLoop = true;
						--unCursor;

						continue;
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
	 * @param	p_unTokenId	Defines the if of the token. Must be smaller than the previously defined max elements.
	 * @param   p_pToken	Defines the token.
	 *
	 * @throws	bia::exception::UnknownException	Thrown when the element limit has been reached.
	 *
	 * @return  This.
	*/
	inline BiaInterpreterRule & SetToken(uint32_t p_unTokenId, bia_token_function p_pToken)
	{
		if (--p_unTokenId < m_unMaxElements)
		{
			m_ppTokens[p_unTokenId] = p_pToken;

			return *this;
		}
		else
			throw exception::UnknownException("Invalid rule element size.");
	}
	inline BiaInterpreterRule & operator=(BiaInterpreterRule && p_right)
	{
		m_unMaxElements = p_right.m_unMaxElements;
		m_fFlags = p_right.m_fFlags;
		p_right.m_unMaxElements = 0;
		p_right.m_fFlags = 0;

		delete[] m_ppTokens;
		m_ppTokens = p_right.m_ppTokens;
		p_right.m_ppTokens = nullptr;

		return *this;
	}


private:
	uint32_t m_unMaxElements;
	uint32_t m_fFlags;

	bia_token_function * m_ppTokens;
};

}
}
}