#pragma once

#include <cstdint>
#include <type_traits>
#include <tuple>
#include <initializer_list>

#include "biaArchitecture.hpp"
#include "biaOutputStream.hpp"
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
	typedef long long position;
	typedef std::tuple<position, position, position> temp_members;
	typedef RegisterOffset<REGISTER::EBP, int8_t, false> temporary_result;

	/**
	 * Constructor.
	 *
	 * @param	[in]	p_output	Defines the output stream.
	*/
	inline BiaToolset(stream::BiaOutputStream & p_output) : m_output(p_output)
	{
		//Create new stack frame for this entry point
		BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EBP>(m_output);
		BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::EBP, REGISTER::ESP>(m_output, 0);
	}
	inline ~BiaToolset()
	{
		//Cleanup stack frame and return
		BiaArchitecture::Operation<OP_CODE::LEAVE>(m_output);
		BiaArchitecture::Operation<OP_CODE::RETURN_NEAR>(m_output);
	}	
	template<typename _RETURN, typename... _ARGS>
	inline void SafeCall(_RETURN(BIA_STATIC_CALLING_CONEVENTION *p_pFunctionAddress)(_ARGS...), _ARGS... p_args)
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
	inline void SafeCall(_RETURN(BIA_MEMBER_CALLING_CONVENTION _CLASS::*p_pFunctionAddress)(_ARGS...), _CLASS * p_pInstance, _ARGS... p_args)
	{
		//Push all parameters
		Pass(p_args...);
		PassInstance(p_pInstance);

		union
		{
			_RETURN(_CLASS::*pMember)(_ARGS...);
			void * pAddress;
		} address;
		
		address.pMember = p_pFunctionAddress;

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

#if defined(BIA_COMPILER_MSCV)
#endif
	}
	template<typename T, typename... _ARGS>
	inline void Call(T * p_pFunctionAddress, _ARGS... p_args)
	{
		//Push all
		Pass(p_args...);

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(p_pFunctionAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);

		//Pop all
		Pop<sizeof...(_ARGS)>();
	}
	template<typename _RETURN, typename _CLASS, typename _INSTANCE, typename... _ARGS, typename... _ARGS2>
	inline void Call(_RETURN(BIA_MEMBER_CALLING_CONVENTION _CLASS::*p_pFunctionAddress)(_ARGS...), _INSTANCE p_instance, _ARGS2... p_args)
	{
		//Push all parameters
		Pass(p_args...);
		PassInstance(p_instance);

		union
		{
			_RETURN(_CLASS::*pMember)(_ARGS...);
			void * pAddress;
		} address;

		address.pMember = p_pFunctionAddress;

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(m_output, reinterpret_cast<uint32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(m_output);
	}
	inline void CommitTemporaryMembers(BiaMachineContext & p_context, temp_members p_parameter, int8_t p_cCount)
	{
		//Get position
		auto llPosition = m_output.GetPosition();

		//Ovewrite
		m_output.SetPosition(std::get<0>(p_parameter));

		PrepareTemporyMembers(p_cCount, &p_context);

		m_output.SetPosition(llPosition);

		//Destruct
		Call(&BiaMachineContext::DestructTemporaryAddresses, &p_context, p_cCount, RegisterOffset<REGISTER::EBP, int8_t, true>(p_cCount * -4));

		//Clean up stack
		BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(m_output, static_cast<int8_t>(p_cCount * 4));
	}
	inline void DiscardTemporaryMembers(temp_members p_parameter)
	{
		m_output.Move(std::get<0>(p_parameter), std::get<1>(p_parameter), m_output.GetPosition() - std::get<1>(p_parameter));
	}
	inline temp_members ReserveTemporyMembers()
	{
		temp_members tmp;

		std::get<0>(tmp) = m_output.GetPosition();

		PrepareTemporyMembers(0, nullptr);

		std::get<1>(tmp) = m_output.GetPosition();

		return tmp;
	}
	inline static temporary_result TemporaryMember(int8_t p_cIndex)
	{
		return temporary_result(p_cIndex * -4);
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
	template<REGISTER _REGISTER, typename _OFFSET, bool _EFFECTIVE_ADDRESS>
	inline void Pass(RegisterOffset<_REGISTER, _OFFSET, _EFFECTIVE_ADDRESS> p_offset)
	{
		static_assert(std::is_same<_OFFSET, int32_t>::value || std::is_same<_OFFSET, int8_t>::value, "Invalid offset type.");

		//Push address
		if (_EFFECTIVE_ADDRESS)
		{
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::EAX, _REGISTER, _OFFSET>(m_output, p_offset.offset);
			BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EAX>(m_output);
		}
		else
		{
			//32 bit signed offset
			if (std::is_same<_OFFSET, int32_t>::value)
				BiaArchitecture::Operation32<OP_CODE::PUSH, _REGISTER>(m_output, p_offset.offset);
			//8 bit signed offset
			else
				BiaArchitecture::Operation8<OP_CODE::PUSH, _REGISTER>(m_output, p_offset.offset);
		}
	}
	template<REGISTER _REGISTER, bool _EFFECTIVE_ADDRESS>
	inline void Pass(RegisterOffset<_REGISTER, void, _EFFECTIVE_ADDRESS> p_offset)
	{
		//Push address
		if (_EFFECTIVE_ADDRESS)
		{
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::EAX, _REGISTER, int8_t>(m_output, 0);
			BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EAX>(m_output);
		}
		//No offset
		else
			BiaArchitecture::Operation<OP_CODE::PUSH, _REGISTER>(m_output);
	}
	template<typename T>
	inline void PassInstance(T * p_pInstance)
	{
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::ECX>(m_output, reinterpret_cast<uint32_t>(p_pInstance));
	}
	template<REGISTER _REGISTER, typename _OFFSET, bool _EFFECTIVE_ADDRESS>
	inline void PassInstance(RegisterOffset<_REGISTER, _OFFSET, _EFFECTIVE_ADDRESS> p_offset)
	{
		static_assert(std::is_same<_OFFSET, int32_t>::value || std::is_same<_OFFSET, int8_t>::value, "Invalid offset type.");

		//Effective address
		if (_EFFECTIVE_ADDRESS)
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::ECX, _REGISTER, _OFFSET>(m_output, p_offset.offset);
		//Just content
		else
			BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::ECX, _REGISTER, _OFFSET>(m_output, p_offset.offset);
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
	/**
	 * Prepares a call to construct temporary addresses.
	 *
	 * @since	3.45.96.586
	 * @date	1-Jan-18
	 *
	 * @param	p_cCount	Defines the amount of addresses. The implementation limit is at 32.
	 * @param	[in]	p_pContext	(Optional)	Defines the machine context address.
	*/
	inline void PrepareTemporyMembers(int8_t p_cCount, BiaMachineContext * p_pContext)
	{
		//Create space for member pointers; add because -128 is better than 127
		BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(m_output, p_cCount * -4);

		//Push count and not esp because it is already on the stack
		Call(&BiaMachineContext::ConstructTemporaryAddresses, p_pContext, p_cCount, RegisterOffset<REGISTER::EBP, int8_t, true>(p_cCount * -4));
	}
};
#endif

}
}
}