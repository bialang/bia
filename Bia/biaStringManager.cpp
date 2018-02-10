#include "biaStringManager.hpp"

#include <cstring>
#include <utility>


namespace bia
{
namespace machine
{

BiaStringManager::BiaStringManager(BiaAllocator * p_pAllocator)
{
	m_pAllocator = p_pAllocator;
}

BiaStringManager::BiaStringManager(BiaStringManager && p_move) : m_index(std::move(p_move.m_index))
{
	m_pAllocator = p_move.m_pAllocator;
}

BiaStringManager::~BiaStringManager()
{
	//Delete all allocated strings
	for (auto & entry : m_index)
		m_pAllocator->Deallocate(const_cast<char*>(entry.pcString));
}

const char * BiaStringManager::GetStringAddress(const char * p_pcString, size_t p_iSize)
{
	auto pResult = m_index.find(StringEntry(p_pcString, p_iSize));

	//Create new entry
	if (pResult == m_index.end())
	{
		auto pcString = static_cast<char*>(m_pAllocator->Allocate(p_iSize + 1));

		//Copy string
		memcpy(pcString, p_pcString, p_iSize);
		pcString[p_iSize] = 0;

		pResult = m_index.insert(StringEntry(pcString, p_iSize)).first;
	}

	return pResult->pcString;
}

}
}