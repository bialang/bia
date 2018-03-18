#pragma once

#include <memory>
#include <unordered_map>

#include "biaAllocator.hpp"
#include "biaMember.hpp"
#include "biaNameManager.hpp"


namespace bia
{
namespace framework
{

class BiaMemberHolder
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the allocator used to allocate memory for members.
	 * @param	[in]	p_pNameManager	Defines the name manager.
	*/
	inline BiaMemberHolder(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager)
	{
		m_pAllocator = p_pAllocator;
		m_pNameManager = p_pNameManager;
	}
	inline virtual ~BiaMemberHolder()
	{
		for (auto & allocation : m_members)
			m_pAllocator->DestroyBlocks(allocation.second, machine::BiaAllocator::MEMORY_TYPE::NORMAL);
	}
	/**
	 * Adds a member or overwrites the existing one.
	 *
	 * @since	3.55.116.671
	 * @date	25-Feb-18
	 *
	 * @param	p_stName	Defines the name of the member.
	 * @param	p_memberAllocation	Defines the member.
	*/
	template<typename T, typename... _ARGS>
	inline void SetMember(const std::string & p_stName, _ARGS &&... p_args)
	{
		auto allocation = m_pAllocator->ConstructBlocks<BiaMember, T>(1, machine::BiaAllocator::MEMORY_TYPE::NORMAL, std::forward<_ARGS>(p_args)...);

#if defined(BIA_CPP_17)
		m_members.insert_or_assign(m_pNameManager->GetNameAddress(p_stName.c_str(), p_stName.length()), std::move(allocation));
#else
		m_members[m_pNameManager->GetNameAddress(p_stName.c_str(), p_stName.length())] = std::move(allocation);
#endif
	}
	/**
	 * Retrieves the member associated with the name.
	 *
	 * @since	3.55.116.671
	 * @date	25-Feb-18
	 *
	 * @param	p_szName	Defines the name of the member.
	 *
	 * @return	The member if it known, otherwise null.
	*/
	inline BiaMember * GetMember(const char * p_szName)
	{
		auto pResult = m_members.find(p_szName);

		return pResult != m_members.end() ?pResult->second.pAddress : nullptr;
	}
	/**
	 * Returns the allocator.
	 *
	 * @since	3.55.116.671
	 * @date	25-Fev-18
	 *
	 * @return	The allocator.
	*/
	/*inline machine::BiaAllocator * GetAllocator()
	{
		return m_pAllocator;
	}*/


private:
	/**	Stores all known members of a class.	*/
	std::unordered_map<const char*, machine::BiaAllocator::Allocation<BiaMember>> m_members;

	/**	Defines the allocator used to allocate memory for the members.	*/
	machine::BiaAllocator * m_pAllocator;
	/**	Defines the name manager used for the name of the members.	*/
	machine::BiaNameManager * m_pNameManager;
};

}
}