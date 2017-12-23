#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

#include "biaMachineContext.hpp"
#include "biaArchitecture.hpp"
#include "biaOutputStream.hpp"


namespace bia
{
namespace machine
{
namespace architecture
{

class BiaToolset
{
public:
	inline BiaToolset(stream::BiaOutputStream & p_output) : m_output(p_output)
	{
		m_ucPushedElements = 0;
	}
	inline ~BiaToolset()
	{
#if defined(BIA_ARCHITECTURE_MG32)
		//Pop rest
		PopAll();

		BiaArchitecture::Operation<OP_CODE::RETURN_NEAR>(m_output);
#endif
	}
	inline void PushResult()
	{
#if defined(BIA_ARCHITECTURE_MG32)
		BiaArchitecture::Operation<OP_CODE::PUSH>(m_output, REGISTER::EAX);

		++m_ucPushedElements;
#endif
	}
	template<typename T>
	inline void Push(T p_value)
	{
#if defined(BIA_ARCHITECTURE_MG32)
		static_assert(sizeof(T) == 1 || sizeof(T) == 4 || sizeof(T) == 8, "Push parameter must of size 1, 4 or 8.");

		//8 bit
		if (sizeof(T) == 1)
			BiaArchitecture::Operation8<OP_CODE::PUSH>(m_output, *reinterpret_cast<uint8_t*>(&p_value));
		//32 bit
		else if (sizeof(T) == 4)
		{
			//Save 3 bytes
			if (std::is_integral<T>::value && !(*reinterpret_cast<uint32_t*>(&p_value) & 0xffffff00))
				BiaArchitecture::Operation8<OP_CODE::PUSH>(m_output, *reinterpret_cast<uint8_t*>(&p_value));
			//Push all 4 bytes
			else
				BiaArchitecture::Operation32<OP_CODE::PUSH>(m_output, *reinterpret_cast<uint32_t*>(&p_value));
		}
		//64 bit
		else
		{
			BiaArchitecture::Operation32<OP_CODE::PUSH>(m_output, *reinterpret_cast<uint64_t*>(&p_value) >> 32);
			BiaArchitecture::Operation32<OP_CODE::PUSH>(m_output, *reinterpret_cast<uint32_t*>(&p_value));

			++m_ucPushedElements;
		}
		
		++m_ucPushedElements;
#endif
	}
	inline void RestoreLocation(std::pair<uint8_t, long long> p_location)
	{
		m_ucPushedElements = p_location.first;
		m_output.SetPosition(p_location.second);
	}
	inline void Pop(uint8_t p_ucElements)
	{
#if defined(BIA_ARCHITECTURE_MG32)
		if (p_ucElements && p_ucElements <= m_ucPushedElements)
		{
			BiaArchitecture::Operation8<OP_CODE::ADD>(m_output, p_ucElements * 4, REGISTER::ESP);

			m_ucPushedElements -= p_ucElements;
		}
#endif
	}
	inline void PopAll()
	{
#if defined(BIA_ARCHITECTURE_MG32)
		if (m_ucPushedElements)
		{
			BiaArchitecture::Operation8<OP_CODE::ADD>(m_output, m_ucPushedElements * 4, REGISTER::ESP);

			m_ucPushedElements = 0;
		}
#endif
	}
	template<bool _AUTO_POP = true>
	inline void Call(const void * p_pAddress)
	{
#if defined(BIA_ARCHITECTURE_MG32)
		//Move the address of the function into EAX
		BiaArchitecture::Operation32<OP_CODE::MOVE>(m_output, reinterpret_cast<uint32_t>(p_pAddress), REGISTER::EAX);

		//Call EAX
		BiaArchitecture::Operation<OP_CODE::CALL>(m_output, REGISTER::EAX);

		//Pop parameter
		if (_AUTO_POP && m_ucPushedElements)
		{
			BiaArchitecture::Operation8<OP_CODE::ADD>(m_output, m_ucPushedElements * 4, REGISTER::ESP);

			m_ucPushedElements = 0;
		}
#endif
	}
	inline uint8_t GetPushedElements()
	{
		return m_ucPushedElements;
	}
	inline std::pair<uint8_t, long long> GetLocation() const
	{
		return { m_ucPushedElements, m_output.GetPosition() };
	}

private:
	stream::BiaOutputStream & m_output;

	uint8_t m_ucPushedElements;
};

}
}
}