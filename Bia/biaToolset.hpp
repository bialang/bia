#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>
#include <initializer_list>

#include "biaMachineContext.hpp"
#include "biaArchitecture.hpp"
#include "biaOutputStream.hpp"
#include "biaManagement.hpp"


namespace bia
{
namespace machine
{
namespace architecture
{

class BiaToolset
{
public:
	inline BiaToolset(stream::BiaOutputStream & p_output) : m_output(p_output) {}
	inline ~BiaToolset()
	{
#if defined(BIA_ARCHITECTURE_MG32)

		BiaArchitecture::Operation<OP_CODE::RETURN_NEAR>(m_output);
#endif
	}
	inline void RestoreLocation(std::pair<uint8_t, long long> p_location)
	{
		m_nPushedElements = p_location.first;
		m_output.SetPosition(p_location.second);
	}
	
	template<typename _RETURN, typename... _ARGS>
	inline void Call(_RETURN(*p_pFunctionAddress)(_ARGS...), _ARGS... p_args)
	{
#if defined(BIA_ARCHITECTURE_MG32)
		//Push all parameters
		Pass(p_args...);


		//Move the address of the function into EAX
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(p_pFunctionAddress));

		//Call EAX
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

		//Pop parameter
		Pop<sizeof...(_ARGS)>();
#endif
	}
	inline void PrepareTemporyMembers(int8_t p_cCount)
	{
#if defined(BIA_ARCHITECTURE_MG32)
		//Create space for member pointers
		BiaArchitecture::Operation8<OP_CODE::SUBTRACT, REGISTER::ESP>(m_output, p_cCount);
		Pass(p_cCount);

		//Allocate
		Call<false>(static_cast<const void*>(link::AllocateTemporaryMembers));

		Pop(1);
#endif
	}
	inline std::pair<int32_t, long long> GetLocation() const
	{
		return { m_nPushedElements, m_output.GetPosition() };
	}

private:
	stream::BiaOutputStream & m_output;


#if defined(BIA_ARCHITECTURE_MG32)
	inline void Pass() {}
	template<typename T, typename... _ARGS>
	inline void Pass(T p_value, _ARGS... p_args)
	{
		Pass(p_value);
		Pass(p_args...);
	}
	template<typename T>
	inline void Pass(T p_value)
	{
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
		}
	}
	template<int32_t _POP>
	inline void Pop()
	{
		if (p_nElements > 0 && p_nElements <= m_nPushedElements)
		{
			m_nPushedElements -= p_nElements;
			p_nElements *= 4;

			if (p_nElements < 128)
				BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(m_output, static_cast<int8_t>(p_nElements));
			else
				BiaArchitecture::Operation32<OP_CODE::ADD, REGISTER::ESP>(m_output, p_nElements);
		}
	}
#endif
};

}
}
}