#pragma once

#include "biaMemberHolder.hpp"


namespace bia
{
namespace framework
{
namespace object
{

class BiaClassContext final : public BiaMemberHolder
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the allocator used to allocate memory for members.
	 * @param	[in]	p_pNameManager	Defines the name manager.
	*/
	inline BiaClassContext(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager) : BiaMemberHolder(p_pAllocator, p_pNameManager)
	{
	}

	template<typename T, typename... _ARGS>
	inline void SetConstructor()
	{

	}
private:
};

}
}
}