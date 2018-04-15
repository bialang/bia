#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <memory>
#include <vector>


namespace bia
{
namespace machine
{

template<typename _Ty, size_t _ELEMENT_SIZE>
class BiaTemporaryStorage
{
public:
	/**
	* Constructor.
	*
	* @param	p_unElementCount	Defines the amount of elements per row.
	*/
	inline BiaTemporaryStorage(uint32_t p_unElementCount)
	{
		m_unElementCount = p_unElementCount;
		m_unUpperIndex = 0;
	}
	/**
	* Move-Constructor.
	*
	* @param	[in,out]	p_move	Defines the object that should be moved.
	*/
	BiaTemporaryStorage(BiaTemporaryStorage && p_move) = default;
	BiaTemporaryStorage(const BiaTemporaryStorage&) = delete;
	inline ~BiaTemporaryStorage()
	{
		DeleteTo(0);
	}
	/**
	 * Deletes and destructs the temporary elements to the lower limit.
	 *
	 * @since	3.43.95.574
	 * @date	23-Dec-17
	 *
	 * @param	p_unLowerIndex	Defines the lower limit.
	*/
	inline void DeleteTo(uint32_t p_unLowerIndex)
	{
		for (auto i = p_unLowerIndex; i < m_unUpperIndex; ++i)
		{
			auto pObject = static_cast<_Ty*>(m_vpucStorage[i / m_unElementCount].get() + i % m_unElementCount * _ELEMENT_SIZE);

			//Destruct and set it to zero
			pObject->~T();
			memset(pObject, 0, _ELEMENT_SIZE);
		}

		m_unUpperIndex = p_unLowerIndex;
	}
	/**
	 * Allocates space for the elements, but does not allocate or modifiy the space.
	 *
	 * @since	3.43.95.574
	 * @date	23-Dec-17
	 *
	 * @param	p_unIndex	Defines the index of the space.
	 *
	 * @return	The pointer.
	*/
	inline _Ty * GetSpace(uint32_t p_unIndex)
	{
		//Add row
		if (!(p_unIndex % m_unElementCount))
			AddRow();

		if (p_unIndex + 1> m_unUpperIndex)
			m_unUpperIndex = p_unIndex + 1;

		return new(m_vpucStorage[p_unIndex / m_unElementCount].get() + p_unIndex % m_unElementCount * _ELEMENT_SIZE) _Ty();
	}

private:
	std::vector<std::unique_ptr<uint8_t[]>> m_vpucStorage;

	uint32_t m_unElementCount;
	uint32_t m_unUpperIndex;


	/**
	* Adds an additional row to the storage table.
	*
	* @since	3.43.95.574
	* @date	23-Dec-17
	*/
	inline void AddRow()
	{
		m_vpucStorage.push_back(std::unique_ptr<uint8_t[]>(new uint8_t[_ELEMENT_SIZE * m_unElementCount]{}));
	}
};

}
}