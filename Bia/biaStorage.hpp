#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>


namespace bia
{
namespace machine
{

template<size_t _ELEMENT_SIZE>
class BiaStorage
{
public:
	/**
	 * Constructor.
	 * 
	 * @param	p_iElementCount	Defines the amount of elements per row.
	 */
	inline BiaStorage(size_t p_iElementCount)
	{
		m_iElementCount = p_iElementCount;
		m_iRowSize = _ELEMENT_SIZE * m_iElementCount;
		m_iCurrentRow = m_iCurrentPosition = 0;

		//Create first row
		AddRow();
	}
	/**
	 * Move-Constructor.
	 * 
	 * @param	[in,out]	p_move	Defines the object that should be moved.
	 */
	BiaStorage(BiaStorage && p_move) = default;
	BiaStorage(const BiaStorage&) = delete;
	/**
	 * Allocates space for the specified element size.
	 * 
	 * @remarks	Do not delete the returned pointer. The returned pointer is valid until destruction of this object.
	 * 
	 * @since	3.42.93.564
	 * @date	16-Dec-17
	 * 
	 * @return	An address to the allocated space.
	 */
	inline void * CreateElement()
	{
		//Add row
		if (m_iCurrentPosition == m_iRowSize)
		{
			AddRow();

			++m_iCurrentRow;
			m_iCurrentPosition = 0;
		}

		auto pElement = m_vpucStorage[m_iCurrentRow].get() + m_iCurrentPosition;

		m_iCurrentPosition += _ELEMENT_SIZE;

		return pElement;
	}

private:
	std::vector<std::unique_ptr<uint8_t[]>> m_vpucStorage;

	size_t m_iElementCount;
	size_t m_iRowSize;
	size_t m_iCurrentRow;
	size_t m_iCurrentPosition;


	/**
	 * Adds an additional row to the storage table.
	 * 
	 * @since	3.42.93.564
	 * @date	16-Dec-17
	 */
	inline void AddRow()
	{
		m_vpucStorage.push_back(std::unique_ptr<uint8_t[]>(new uint8_t[m_iRowSize]));
	}
};

}
}