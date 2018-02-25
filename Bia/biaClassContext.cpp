#include "biaClassContext.hpp"


namespace bia
{
namespace framework
{
namespace object
{

BiaClassContext::BiaClassContext(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager)
{
	m_pAllocator = p_pAllocator;
	m_pNameManager = p_pNameManager;
}

void BiaClassContext::SetMember(const std::string & p_stName, BiaMember * p_pMember)
{
	m_members.insert_or_assign(m_pNameManager->GetNameAddress(p_stName.c_str(), p_stName.length()), p_pMember);
}

BiaMember * BiaClassContext::GetMember(const char * p_szName)
{
	auto pResult = m_members.find(p_szName);

	return pResult != m_members.end() ? pResult->second : nullptr;
}

machine::BiaAllocator * BiaClassContext::GetAllocator()
{
	return m_pAllocator;
}

}
}
}