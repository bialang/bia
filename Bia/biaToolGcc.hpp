#pragma once

#include <cstdint>
#include <type_traits>

#include "biaMachineContext.hpp"
#include "biaArchitecture.hpp"
#include "biax86.hpp"
#include "biaOutputStream.hpp"


namespace bia
{
namespace machine
{
namespace architecture
{

template<typename _ARCHITECTURE>
class BiaToolGcc
{
public:
	inline BiaToolGcc(stream::BiaOutputStream & p_output) : m_output(p_output)
	{
		m_ucPushedElements = 0;
	}
	inline ~BiaToolGcc()
	{
		//For 32-Bit systems
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			//Pop rest
			PopParameters();

			Biax86::Operation<OP_CODE::RETURN_NEAR>(m_output);
		}
	}
	inline void PushParameter(uint8_t p_ucValue)
	{
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			Biax86::Operation8<OP_CODE::PUSH>(m_output, p_ucValue);

			++m_ucPushedElements;
		}
	}
	inline void PushParameter(uint32_t p_unValue)
	{
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			//Save 3 bytes
			if (p_unValue < 256)
				PushParameter(static_cast<uint8_t>(p_unValue));
			//Push all 4 bytes
			else
			{
				Biax86::Operation32<OP_CODE::PUSH>(m_output, p_unValue);

				++m_ucPushedElements;
			}
		}
	}
	inline void PushParameter(uint64_t p_ullValue)
	{
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			Biax86::Operation32<OP_CODE::PUSH>(m_output, p_ullValue >> 32);
			Biax86::Operation32<OP_CODE::PUSH>(m_output, p_ullValue & 0xffffffff);

			m_ucPushedElements += 2;
		}
	}
	inline void PopParameters()
	{
		if (std::is_same<_ARCHITECTURE, Biax86>::value && m_ucPushedElements)
		{
			Biax86::Operation8<OP_CODE::ADD>(m_output, m_ucPushedElements * 4, REGISTER::ESP);

			m_ucPushedElements = 0;
		}
	}
	template<bool _AUTO_POP = true>
	inline void Call(const void * p_pAddress)
	{
		//For 32-Bit systems
		if (std::is_same<_ARCHITECTURE, Biax86>::value)
		{
			//Move the address of the function into EAX
			Biax86::Operation32<OP_CODE::MOVE>(m_output, reinterpret_cast<uint32_t>(p_pAddress), REGISTER::EAX);

			//Call EAX
			Biax86::Operation<OP_CODE::CALL>(m_output, REGISTER::EAX);

			//Pop parameter
			if (_AUTO_POP && m_ucPushedElements)
			{
				Biax86::Operation8<OP_CODE::ADD>(m_output, m_ucPushedElements * 4, REGISTER::ESP);

				m_ucPushedElements = 0;
			}
		}
	}

private:
	stream::BiaOutputStream & m_output;

	uint8_t m_ucPushedElements;
};

}
}
}