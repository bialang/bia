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

		m_bUsedCurrent = false;
	}
	inline void Pop()
	{
		if (!m_popFree)
		{
			if (--m_counter < 0)
				throw BIA_IMPLEMENTATION_EXCEPTION("Invalid temp counter.");
		}
		else
			--m_popFree;
	}
	inline counter_type Current()
	{
		if (m_max < m_counter)
			m_max = m_counter;

		m_bUsedCurrent = true;

		return m_counter;
	}
	void Next()
	{
		if (m_bUsedCurrent)
		{
			if (++m_counter > BIA_MAX_TEMP_ADDRESSES)
				throw exception::LimitationException("Limitation exceeded.");

			m_bUsedCurrent = false;
		}
		else
			++m_popFree;
	}
	counter_type Max() const
	{
		return m_max;
	}

private:
	counter_type m_counter;
	counter_type m_max;
	counter_type m_popFree;

	bool m_bUsedCurrent;
};

}
}