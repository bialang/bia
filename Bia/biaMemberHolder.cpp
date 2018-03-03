#include "biaMemberHolder.hpp"


namespace bia
{
namespace framework
{

BiaMemberHolder::BiaMemberHolder(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager)
{
	m_pAllocator = p_pAllocator;
	m_pNameManager = p_pNameManager;
}

void BiaMemberHolder::SetMember(const std::string & p_stName, machine::BiaAllocator::universal_allocation p_memberAllocation)
{
	m_members.insert_or_assign(m_pNameManager->GetNameAddress(p_stName.c_str(), p_stName.length()), p_memberAllocation);
}

BiaMember * BiaMemberHolder::GetMember(const char * p_szName)
{
	auto pResult = m_members.find(p_szName);

	return pResult != m_members.end() ? static_cast<BiaMember*>(pResult->second.pAddress) : nullptr;
}

machine::BiaAllocator * BiaMemberHolder::GetAllocator()
{
	return m_pAllocator;
}

}
}