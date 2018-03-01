#include "biaMachineSchein.hpp"

namespace bia
{
namespace machine
{

BiaMachineSchein::BiaMachineSchein(BiaAllocator * p_pAllocator)
{
	m_pAllocator = p_pAllocator;
}

void BiaMachineSchein::RegisterAllocation(BiaAllocator::universal_allocation p_allocation)
{
	m_vpAllocatedPointers.push_back(p_allocation);
}

BiaAllocator * BiaMachineSchein::GetAllocator()
{
	return m_pAllocator;
}

BiaMachineSchein & BiaMachineSchein::operator=(BiaMachineSchein && p_move)
{
	m_pAllocator = p_move.m_pAllocator;
	m_vpAllocatedPointers = std::move(p_move.m_vpAllocatedPointers);

	return *this;
}

}
}