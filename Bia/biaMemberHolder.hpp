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
	BiaMemberHolder(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager);
	/**
	 * Adds a member or overwrites the existing one.
	 *
	 * @since	3.55.116.671
	 * @date	25-Feb-18
	 *
	 * @param	p_stName	Defines the name of the member.
	 * @param	p_memberAllocation	Defines the member.
	*/
	void SetMember(const std::string & p_stName, machine::BiaAllocator::universal_allocation p_memberAllocation);
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
	BiaMember * GetMember(const char * p_szName);
	/**
	 * Returns the allocator.
	 *
	 * @since	3.55.116.671
	 * @date	25-Fev-18
	 *
	 * @return	The allocator.
	*/
	machine::BiaAllocator * GetAllocator();

private:
	/**	Stores all known members of a class.	*/
	std::unordered_map<const char*, machine::BiaAllocator::universal_allocation> m_members;

	/**	Defines the allocator used to allocate memory for the members.	*/
	machine::BiaAllocator * m_pAllocator;
	/**	Defines the name manager used for the name of the members.	*/
	machine::BiaNameManager * m_pNameManager;
};

}
}