#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>
#include <initializer_list>

#include "biaArchitecture.hpp"
#include "biaOutputStream.hpp"
#include "biaManagement.hpp"
#include "biaMachineContext.hpp"


namespace bia
{
namespace machine
{
namespace architecture
{

#if defined(BIA_ARCHITECTURE_MG32)
class BiaToolset
{
public:
	typedef std::pair<long long, long long> temp_members;

	inline BiaToolset(stream::BiaOutputStream & p_output) : m_output(p_output)
	{
		BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EBP>(m_output);
		BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::EBP, REGISTER::ESP>(m_output);
	}
	inline ~BiaToolset()
	{
		BiaArchitecture::Operation<OP_CODE::LEAVE>(m_output);
		BiaArchitecture::Operation<OP_CODE::RETURN_NEAR>(m_output);
	}	
	template<typename _RETURN, typename... _ARGS>
	inline void SafeCall(_RETURN(*p_pFunctionAddress)(_ARGS...), _ARGS... p_args)
	{
		//Push all parameters
		Pass(p_args...);

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(p_pFunctionAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

		//Pop parameter
		Pop<sizeof...(_ARGS)>();
	}
	template<typename _RETURN, typename _CLASS, typename... _ARGS>
	inline void SafeCall(_RETURN(__thiscall _CLASS::*p_pFunctionAddress)(_ARGS...), _CLASS * p_pInstance, _ARGS... p_args)
	{
		//Push all parameters
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::ECX>(m_output, reinterpret_cast<uint32_t>(p_pInstance));
		Pass(p_args...);

		union
		{
			_RETURN(_CLASS::*pMember)(_ARGS...);
			void * pAddress;
		} address;
		
		address.pMember = p_pFunctionAddress;

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

		//Pop parameter
		Pop<sizeof...(_ARGS)>();
	}
	template<bool _POP, typename T, typename... _ARGS>
	inline void Call(T * p_pFunctionAddress, _ARGS... p_args)
	{
		//Push all
		Pass(p_args...);

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(p_pFunctionAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

		//Pop all
		if (_POP)
			Pop<sizeof...(_ARGS)>();
	}
	template<bool _POP, typename _RETURN, typename _CLASS, typename... _ARGS, typename... _ARGS2>
	inline void Call(_RETURN(__thiscall _CLASS::*p_pFunctionAddress)(_ARGS...), _CLASS * p_pInstance, _ARGS2... p_args)
	{
		//Push all parameters
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::ECX>(m_output, reinterpret_cast<uint32_t>(p_pInstance));
		Pass(p_args...);

		union
		{
			_RETURN(_CLASS::*pMember)(_ARGS...);
			void * pAddress;
		} address;

		address.pMember = p_pFunctionAddress;

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

		//Pop all
		if (_POP)
			Pop<sizeof...(_ARGS)>();
	}
	inline void CommitTemporaryMembers(BiaMachineContext & p_context, temp_members p_parameter, int8_t p_cCount)
	{
		//Get position
		auto llPosition = m_output.GetPosition();

		//Ovewrite
		m_output.SetPosition(p_parameter.second);

		PrepareTemporyMembers(p_cCount, &p_context);

		m_output.SetPosition(llPosition);

		//Leave
		BiaArchitecture::Operation<OP_CODE::LEAVE>(m_output);
	}
	inline temp_members ReserveTemporyMembers()
	{
		temp_members tmp;

		tmp.first = GetLocation();

		BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EBP>(m_output);
		BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::EBP, REGISTER::ESP>(m_output);

		tmp.second = GetLocation();

		PrepareTemporyMembers(0, nullptr);

		return tmp;
	}
	inline long long GetLocation() const
	{
		return m_output.GetPosition();
	}

private:
	stream::BiaOutputStream & m_output;


	inline void Pass() {}
	template<typename T, typename... _ARGS>
	inline void Pass(T p_value, _ARGS... p_args)
	{
		Pass(p_args...);
		Pass(p_value);
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
	template<typename T>
	inline void Pass(T * p_pAddress)
	{
		BiaArchitecture::Operation32<OP_CODE::PUSH>(m_output, reinterpret_cast<uint32_t>(p_pAddress));
	}
	inline void Pass(REGISTER p_register)
	{
		BiaArchitecture::PushRegister(m_output, p_register);
	}
	template<int32_t _POP>
	inline void Pop()
	{
		if (_POP > 0)
		{
			if (_POP * 4 < 128)
				BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(m_output, static_cast<int8_t>(_POP * 4));
			else
				BiaArchitecture::Operation32<OP_CODE::ADD, REGISTER::ESP>(m_output, _POP * 4);
		}
	}
	inline void PrepareTemporyMembers(int8_t p_cCount, BiaMachineContext * p_pContext)
	{
		//Create space for member pointers
		BiaArchitecture::Operation8<OP_CODE::SUBTRACT, REGISTER::ESP>(m_output, p_cCount);

		//Push count and not esp because it is already on the stack
		Call<true>(&BiaMachineContext::AllocateTemporaryAddresses, p_pContext, REGISTER::ESP, p_cCount);
	}
};
#endif

}
}
}