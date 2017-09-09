#pragma once

#include "biaException.h"
#include "biaInterpreterTokens.h"


namespace bia
{
namespace api
{
namespace grammar
{

class BiaInterpreterRule
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_iElements	Defines the amount of elements.
	*/
	inline BiaInterpreterRule(size_t p_iElements)
	{
		m_iMaxElements = p_iElements;
		m_iCursor = 0;

		m_ppTokens = new bia_token_function[p_iElements]{};
	}
	inline ~BiaInterpreterRule()
	{
		delete[] m_ppTokens;
	}
	inline void Reset()
	{
		m_iCursor = 0;
	}
	inline bool NotFinished()
	{
		return m_iCursor < m_iMaxElements;
	}
	inline bia_token_function Next()
	{
		return m_ppTokens[m_iCursor++];
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

private:
	size_t m_iMaxElements;
	size_t m_iCursor;

	bia_token_function * m_ppTokens;
};

}
}
}