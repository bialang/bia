#include "biaNameManager.hpp"

#include <cstring>
#include <utility>


namespace bia
{
namespace machine
{

BiaNameManager::BiaNameManager(BiaAllocator * p_pAllocator)
{
	m_pAllocator = p_pAllocator;
}

BiaNameManager::BiaNameManager(BiaNameManager && p_move) : m_index(std::move(p_move.m_index))
{
	m_pAllocator = p_move.m_pAllocator;
}

BiaNameManager::~BiaNameManager()
{
	//Delete all allocated strings
	for (auto & entry : m_index)
		m_pAllocator->Deallocate(entry.GetAllocation(), BiaAllocator::MEMORY_TYPE::NORMAL);
}

const char * BiaNameManager::GetNameAddress(const char * p_pcString, size_t p_iSize)
{
	auto pResult = m_index.find({ p_pcString,p_iSize });

	//Create new entry
	if (pResult == m_index.end())
	{
		auto allocation = m_pAllocator->Allocate(p_iSize + 1, BiaAllocator::MEMORY_TYPE::NORMAL);
		auto pcString = static_cast<char*>(allocation.pAddress);

		//Copy string
		memcpy(pcString, p_pcString, p_iSize);
		pcString[p_iSize] = 0;

		pResult = m_index.insert(StringEntry(allocation)).first;
	}

	return pResult->pcString;
}

}
}