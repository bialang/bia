#pragma once

#include <cstdint>

#include "biaMember.hpp"
#include "biaPrint.hpp"


namespace bia
{
namespace api
{
namespace framework
{

class BiaInt final : public BiaMember
{
public:
	inline BiaInt(int64_t p_llValue)
	{
		m_llValue = p_llValue;
	}

	inline virtual void Print() override
	{
		machine::link::Print_I(m_llValue);
	}

private:
	int64_t m_llValue;
};

}
}
}