#pragma once

#include <stdlib.h>
#include <utility>
#include <new>

#include "biaScopeElement.h"


namespace bia
{
namespace machine
{
namespace scope
{

class BiaScopeStorage
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_unMaxElements	Defines the max elements per cell.
	*/
	inline BiaScopeStorage(unsigned int p_unMaxElements) : m_cunMaxElements(p_unMaxElements)
	{
		m_uiIdCounter = 0;
		m_unCellsLimit = 8;
		m_unCurrentCell = 0;
		m_unElements = 0;

		m_ppcAllocatorTable = static_cast<BiaScopeElement**>(calloc(m_unCellsLimit, sizeof(BiaScopeElement*)));

		InsertNewCell();
	}
	/**
	 * Move-Constructor.
	 *
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	inline BiaScopeStorage(BiaScopeStorage && p_move) : m_cunMaxElements(p_move.m_cunMaxElements)
	{
		m_uiIdCounter = p_move.m_uiIdCounter;
		m_unCellsLimit = p_move.m_unCellsLimit;
		m_unCurrentCell = p_move.m_unCurrentCell;
		m_unElements = p_move.m_unElements;
		p_move.m_unCellsLimit = 0;

		m_ppcAllocatorTable = p_move.m_ppcAllocatorTable;
		p_move.m_ppcAllocatorTable = nullptr;
	}
	inline ~BiaScopeStorage()
	{
		for (auto i = 0u; i < m_unCellsLimit; ++i)
			free(m_ppcAllocatorTable[i]);

		free(m_ppcAllocatorTable);
	}
	/**
	 * Pops all variables until the specified state is reached.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   p_lastState	Defines the last state.
	*/
	inline void PopLastElements(const std::pair<unsigned int, unsigned int> & p_lastState)
	{
		while (m_unCurrentCell > p_lastState.first)
		{
			while (m_unElements)
			{
				//Check if id is non zero
				if (m_ppcAllocatorTable[m_unCurrentCell][--m_unElements].m_uiIdentifier)
					m_ppcAllocatorTable[m_unCurrentCell][m_unElements].~BiaScopeElement();
			}

			m_unElements = m_cunMaxElements;
			--m_unCurrentCell;
		}

		while (m_unElements > p_lastState.second)
		{
			//Check if id is non zero
			if (m_ppcAllocatorTable[m_unCurrentCell][--m_unElements].m_uiIdentifier)
				m_ppcAllocatorTable[m_unCurrentCell][m_unElements].~BiaScopeElement();
		}
	}
	/**
	 * Clears everything.
	 *
	 * @since	2.37.78.453
	 * @date	02-Sep-17
	*/
	inline void Clear()
	{
		while (m_unCurrentCell)
		{
			while (m_unElements)
			{
				//Check if id is non zero
				if (m_ppcAllocatorTable[m_unCurrentCell][--m_unElements].m_uiIdentifier)
					m_ppcAllocatorTable[m_unCurrentCell][m_unElements].~BiaScopeElement();
			}

			m_unElements = m_cunMaxElements;
			free(m_ppcAllocatorTable[m_unCurrentCell]);
			m_ppcAllocatorTable[m_unCurrentCell--] = nullptr;
		}

		while (m_unElements)
		{
			//Check if id is non zero
			if (m_ppcAllocatorTable[m_unCurrentCell][--m_unElements].m_uiIdentifier)
				m_ppcAllocatorTable[m_unCurrentCell][m_unElements].~BiaScopeElement();
		}

		//Reset rest
		m_uiIdCounter = 0;
	}
	/**
	 * Returns the current state.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @return  The current state.
	*/
	inline std::pair<unsigned int, unsigned int> GetState() const
	{
		return { m_unCurrentCell, m_unElements };
	}
	/**
	 * Inserts a member holder.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   [in,out]	p_value	Defines the member holder.
	 *
	 * @return  The resulting scope element.
	*/
	inline BiaScopeElement * Insert(api::framework::BiaMemberHolder && p_value)
	{
		//Create init new cell
		if (m_unElements >= m_cunMaxElements)
		{
			//Create new cells
			if (++m_unCurrentCell >= m_unCellsLimit)
				DoubleCellLimit();

			InsertNewCell();
		}

		return new(m_ppcAllocatorTable[m_unCurrentCell] + m_unElements++) BiaScopeElement(std::move(p_value), m_uiIdCounter++, true);
	}

private:
	unsigned int m_uiIdCounter;	/**	Defines the id counter for creating elements with an unique id.	*/
	unsigned int m_unCellsLimit;	/**	Defines the current cell limit.	*/
	unsigned int m_unCurrentCell;	/**Defines the amount of currently used cells.	*/
	const unsigned int m_cunMaxElements;	/**	Defines the maximum elements per cell.	*/
	unsigned int m_unElements;	/**	Defines the amount of currently valid elements in the active cell.	*/

	BiaScopeElement ** m_ppcAllocatorTable;	/**	Defines the two dimensional storage.	*/


	/**
	 * Doubles the current limit of cells.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void DoubleCellLimit()
	{
		auto unNewLimit = m_unCellsLimit * 2;
		auto ppcTmp = static_cast<BiaScopeElement**>(calloc(unNewLimit, sizeof(BiaScopeElement*)));

		for (auto i = 0u; i < m_unCellsLimit; ++i)
			ppcTmp[i] = m_ppcAllocatorTable[i];

		free(m_ppcAllocatorTable);
		m_ppcAllocatorTable = ppcTmp;
		m_unCellsLimit = unNewLimit;
	}
	/**
	 * Inserts a new cell.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	*/
	inline void InsertNewCell()
	{
		if (!m_ppcAllocatorTable[m_unCurrentCell])
			m_ppcAllocatorTable[m_unCurrentCell] = static_cast<BiaScopeElement*>(malloc(sizeof(BiaScopeElement) * m_cunMaxElements));

		m_unElements = 0;
	}
};

typedef BiaScopeStorage scope_container;

}
}
}