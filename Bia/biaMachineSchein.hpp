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
	void RegisterAllocatedPointer(void * p_pAddress);
	BiaAllocator * GetAllocator();

private:
	BiaAllocator * m_pAllocator;

	std::vector<void*> m_vpAllocatedPointers;
};

}
}