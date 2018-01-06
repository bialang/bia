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
	typedef int8_t counter_type;

	inline BiaTempCounter()
	{
		m_counter = m_max = 0;
	}
	inline void Pop()
	{
		if (--m_counter < 0)
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid temp counter.");
	}
	inline counter_type Current()
	{
		if (m_max < m_counter)
			m_max = m_counter;

		return m_counter;
	}
	counter_type Next()
	{
		if (++m_counter > BIA_MAX_TEMP_ADDRESSES)
			throw exception::LimitationException("Limitation exceeded.");

		return m_counter;
	}
	counter_type Max() const
	{
		return m_max;
	}

private:
	counter_type m_counter;
	counter_type m_max;
};

}
}