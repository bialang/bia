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
	inline BiaTempCounter()
	{
		m_counter = m_max = 0;
	}
	inline void Pop()
	{
		if (--m_counter < 0)
			throw BIA_IMPLEMENTATION_EXCEPTION("Invalid temp counter.");
	}
	inline int8_t Current() const
	{
		return m_counter;
	}
	int8_t Next()
	{
		if (++m_counter > BIA_MAX_TEMP_ADDRESSES)
			throw exception::LimitationException("Limitation exceeded.");

		if (m_max < m_counter)
			m_max = m_counter;

		return m_counter;
	}
	int8_t Max() const
	{
		return m_max;
	}

private:
	int8_t m_counter;
	int8_t m_max;
};

}
}