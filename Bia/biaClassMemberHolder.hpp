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
	inline BiaClassMemberHolder(machine::BiaAllocator * p_pAllocator, machine::BiaNameManager * p_pNameManager) : BiaMemberHolder(p_pAllocator, p_pNameManager), m_pInitiator(GetDefaultConstructor(), [](force::BiaInitiator * p_pDestructor) {
		if (p_pDestructor != GetDefaultConstructor())
			delete p_pDestructor;
	})
	{
	}
	/**
	 * Sets the default constructor.
	 *
	 * @since	3.60.122.690
	 * @date	13-Mar-18
	*/
	template<typename T, typename... _ARGS>
	inline void SetConstructor()
	{
		m_pInitiator.reset(new force::BiaInitiatorDeriviate<T, _ARGS...>());
	}
	/**
	 * Returns the initiator.
	 *
	 * @since	3.60.122.690
	 * @date	13-Mar-18
	 *
	 * @return	The initiator set for the class.
	*/
	inline force::BiaInitiator * GetInitiator()
	{
		return m_pInitiator.get();
	}

private:
	std::unique_ptr<force::BiaInitiator, void(*)(force::BiaInitiator*)> m_pInitiator;


	/**
	 * Returns a static address to the default constructor.
	 *
	 * @remarks	Using this technique because the BiaClassMemberHolder class is not needed at bia-runtime.
	 *
	 * @since	3.60.122.690
	 * @date	13-Mar-18
	 *
	 * @return	The static address.
	*/
	inline static force::BiaInitiator * GetDefaultConstructor()
	{
		static force::BiaInitiator sDefaultConstructor;

		return &sDefaultConstructor;
	}
};

}
}
}