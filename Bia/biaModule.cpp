#include "biaModule.hpp"


namespace bia
{
namespace machine
{
namespace modular
{

BiaModule::BiaModule(BiaAllocator * p_pAllocator)
{
	m_pAllocator = p_pAllocator;
}

BiaAllocator * BiaModule::GetAllocator()
{
	return m_pAllocator;
}

}
}
}