#pragma once

#include <cstdint>

#include "biaConfig.hpp"
#include "biaException.hpp"


namespace bia
{
namespace compiler
{

class BiaTempCounter
{
public:
	typedef int32_t counter_type;

	inline BiaTempCounter()
	{
		m_counter = m_max = 0;
	}
	inline void Pop(counter_type p_oldCounter)
	{
		if (m_counter < p_oldCounter)
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid old counter.");
			
		m_counter = p_oldCounter;
	}
	inline counter_type Next()
	{
		if (m_counter + 1 > BIA_MAX_TEMP_ADDRESSES)
			throw exception::LimitationException("Limitation exceeded.");
	
		return ++m_counter;
	}
	inline counter_type Current()
	{
		//Update max if counter is used
		if (m_max < m_counter)
			m_max = m_counter;

		return m_counter;
	}
	inline counter_type Max() const
	{
		return m_max;
	}

private:
	counter_type m_counter;
	counter_type m_max;
};

}
}