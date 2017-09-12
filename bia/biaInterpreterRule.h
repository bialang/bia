#pragma once

#include "biaException.h"
#include "biaReportBundle.h"


namespace bia
{
namespace api
{
namespace grammar
{

constexpr int NONE = 0;
constexpr int FILLER_TOKEN = 0x1;
constexpr int OPTIONAL_TOKEN = 0x2;

enum class ACTION
{
	REPORT,
	DONT_REPORT,
	ERROR
};

class BiaInterpreterRule;

struct TokenParams
{
	BiaReportBundle * pBundle;
	BiaInterpreterRule * pRules;
};

typedef ACTION(*bia_token_function)(const char*, size_t, size_t&, TokenParams, uint64_t&);

class BiaInterpreterRule
{
public:
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
	inline void Reset(size_t p_iElements, bool p_bOr = false)
	{
		m_iMaxElements = p_iElements;
		m_fFlags = p_bOr ? F_OR : 0;

		delete[] m_ppTokens;
		m_ppTokens = new bia_token_function[p_iElements]{};
	}
	inline size_t RunRule(const char * p_pcBuffer, size_t p_iSize, TokenParams p_params)
	{
		size_t iCursor = 0;
		auto iRuleId = static_cast<size_t>(this - p_params.pRules);

		//Or loop
		if (m_fFlags & F_OR)
		{
			while (iCursor < m_iMaxElements)
			{
				size_t iTokenSize = 0;
				uint64_t ullCustomParameter = 0;

				switch (m_ppTokens[iCursor++](p_pcBuffer, p_iSize, iTokenSize, p_params, ullCustomParameter))
				{
				case ACTION::REPORT:
					p_params.pBundle->AddReport({ p_pcBuffer, iTokenSize, iRuleId, iCursor - 1, ullCustomParameter });
				case ACTION::DONT_REPORT:
					return iTokenSize;
				case ACTION::ERROR:
					break;
				}
			}

			return 0;
		}
		//And loop
		else
		{
			const auto ciSize = p_iSize;

			while (iCursor < m_iMaxElements)
			{
				size_t iTokenSize = 0;
				uint64_t ullCustomParameter;

				switch (m_ppTokens[iCursor++](p_pcBuffer, p_iSize, iTokenSize, p_params, ullCustomParameter))
				{
				case ACTION::REPORT:
					p_params.pBundle->AddReport({ p_pcBuffer, iTokenSize, iRuleId, iCursor - 1, ullCustomParameter });
				case ACTION::DONT_REPORT:
					p_pcBuffer += iTokenSize;
					p_iSize -= iTokenSize;

					break;
				case ACTION::ERROR:
					return 0;
				}
			}

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
	 * @throws	bia::exception::UnknownException	Thrown when the element limit has been reached.
	 *
	 * @return  This.
	*/
	inline BiaInterpreterRule & SetToken(size_t p_iTokenId, bia_token_function p_pToken)
	{
		if (p_iTokenId < m_iMaxElements)
		{
			m_ppTokens[p_iTokenId] = p_pToken;

			return *this;
		}
		else
			throw exception::UnknownException("Invalid rule element size.");
	}
	inline BiaInterpreterRule & operator=(BiaInterpreterRule && p_right)
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
	enum FLAGS
	{
		F_OR = 0x1
	};

	size_t m_iMaxElements;
	size_t m_fFlags;

	bia_token_function * m_ppTokens;
};

}
}
}