#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

#include "biaAllocator.hpp"
#include "biaMember.hpp"


namespace bia
{
namespace machine
{
namespace modular
{

class BiaModule
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the memory allocator.
	*/
	BiaModule(BiaAllocator * p_pAllocator);

	void RegisterMember(const char * p_szName, BiaAllocator::universal_allocation p_memberAllocation);
	template<typename T, typename... _ARGS>
	inline typename std::enable_if<std::is_base_of<framework::BiaMember, T>::value>::type RegisterMember(const char * p_szName, _ARGS &&... p_args)
	{
		auto allocation = m_pAllocator->ConstructBlocks<T>(1, BiaAllocator::MEMORY_TYPE::NORMAL, std::forward<_ARGS>(p_args)...);

		RegisterMember(p_szName, BiaAllocator::ToUniversalAllocation(allocation));
	}
	static uint32_t GetModuleVersion();
	BiaAllocator * GetAllocator();

private:
	/**	Defines the memory allocator.	*/
	BiaAllocator * m_pAllocator;
};

}
}
}