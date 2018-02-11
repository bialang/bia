#include "biaMachineSchein.hpp"

namespace bia
{
namespace machine
{

BiaMachineSchein::BiaMachineSchein(BiaAllocator * p_pAllocator)
{
	m_pAllocator = p_pAllocator;
}

void BiaMachineSchein::RegisterAllocatedPointer(void * p_pAddress)
{
	m_vpAllocatedPointers.push_back(p_pAddress);
}

BiaAllocator * BiaMachineSchein::GetAllocator()
{
	return m_pAllocator;
}

}
}