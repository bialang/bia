#pragma once

#include <vector>

#include "biaAllocator.hpp"


namespace bia
{
namespace machine
{

class BiaMachineSchein
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the memory allocator.
	*/
	BiaMachineSchein(BiaAllocator * p_pAllocator);
	BiaMachineSchein(const BiaMachineSchein&) = delete;
	BiaMachineSchein(BiaMachineSchein&&) = default;

	void RegisterAllocation(BiaAllocator::universal_allocation p_allocation);
	BiaAllocator * GetAllocator();
	BiaMachineSchein & operator=(BiaMachineSchein && p_move);

private:
	BiaAllocator * m_pAllocator;

	std::vector<BiaAllocator::universal_allocation> m_vpAllocatedPointers;
};

}
}