#pragma once

#include <memory>

#include "biaMemberHolder.hpp"
#include "biaInitiator.hpp"


namespace bia
{
namespace framework
{
namespace object
{

class BiaClassMemberHolder final : public BiaMemberHolder
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the allocator used to allocate memory for members.
	 * @param	[in]	p_pNameManager	Defines the name manager.
	*/
	inline BiaClassMemberHolder(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager) : BiaMemberHolder(p_pAllocator, p_pNameManager), m_pInitiator(&m_sDefaultConstructor, [](force::BiaInitiator * p_pDestructor) {
		if (p_pDestructor != &m_sDefaultConstructor)
			delete p_pDestructor;
	})
	{
	}

	template<typename T, typename... _ARGS>
	inline void SetConstructor()
	{
		m_pInitiator.reset(new force::BiaInitiatorDeriviate<T, _ARGS...>());
	}
private:
	static force::BiaInitiator m_sDefaultConstructor;

	std::unique_ptr<force::BiaInitiator, void(*)(force::BiaInitiator*)> m_pInitiator;
};

}
}
}