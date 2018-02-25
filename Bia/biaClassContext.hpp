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
namespace object
{

class BiaClassContext
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the allocator used to allocate memory for members.
	 * @param	[in]	p_pNameManager	Defines the name manager.
	*/
	BiaClassContext(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager);
	/**
	 * Adds a member or overwrites the existing one.
	 *
	 * @since	3.55.116.671
	 * @date	25-Feb-18
	 *
	 * @param	p_stName	Defines the name of the member.
	 * @param	[in]	p_pMember	Defines the member.
	*/
	void SetMember(const std::string & p_stName, BiaMember * p_pMember);
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
	std::unordered_map<const char*, BiaMember*> m_members;	/**	Stores all known members of a class.	*/

	machine::BiaAllocator * m_pAllocator;	/**	Defines the allocator used to allocate memory for the members.	*/
	machine::BiaNameManager * m_pNameManager;	/**	Defines the name manager used for the name of the members.	*/
};

}
}
}