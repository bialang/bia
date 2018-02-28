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
	enum class JUMP
	{
		JUMP,
		JUMP_IF_TRUE,
		JUMP_IF_FALSE
	};

	typedef long long position;
	typedef std::tuple<position, position, position> temp_members;
	typedef RegisterOffset<REGISTER::EBP, int8_t, false> temporary_result;
	typedef int32_t pass_count;

	/**
	 * Constructor.
	 *
	 * @param	[in]	p_output	Defines the output stream.
	*/
	inline BiaToolset(stream::BiaOutputStream & p_output) : m_pOutput(&p_output)
	{
		m_nPassed = 0;

		//Create new stack frame for this entry point
		BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EBP>(*m_pOutput);
		BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::EBP, REGISTER::ESP>(*m_pOutput, 0);
	}
	inline ~BiaToolset()
	{
		//Cleanup stack frame and return
		BiaArchitecture::Operation<OP_CODE::LEAVE>(*m_pOutput);
		BiaArchitecture::Operation<OP_CODE::RETURN_NEAR>(*m_pOutput);
	}	
	inline void SetOutput(stream::BiaOutputStream & p_output)
	{
		m_pOutput = &p_output;
	}
	template<typename _RETURN, typename... _ARGS>
	inline void SafeCall(_RETURN(BIA_STATIC_CALLING_CONEVENTION *p_pFunctionAddress)(_ARGS...), _ARGS... p_args)
	{
		//Push all parameters
		auto passed = Pass(p_args...);

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(*m_pOutput, reinterpret_cast<int32_t>(p_pFunctionAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(*m_pOutput);

		//Pop parameter
		Pop(passed);
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
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(*m_pOutput, reinterpret_cast<int32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(*m_pOutput);
	}
	template<typename _RETURN, typename _CLASS, typename _INSTANCE, typename... _ARGS, typename... _ARGS2>
	inline void Call(pass_count p_passed, _RETURN(BIA_MEMBER_VARARG_CALLING_CONVENTION _CLASS::*p_pFunctionAddress)(_ARGS..., ...), _INSTANCE p_instance, _ARGS2... p_args)
	{
		//Push all parameters
		auto passed = Pass(p_instance, p_args...);

		union
		{
			_RETURN(_CLASS::*pMember)(_ARGS..., ...);
			void * pAddress;
		} address;

		address.pMember = p_pFunctionAddress;

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(*m_pOutput, reinterpret_cast<int32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(*m_pOutput);

		//Pop
		Pop(passed + p_passed);
	}
	template<typename T, typename... _ARGS>
	inline void Call(T * p_pFunctionAddress, _ARGS... p_args)
	{
		//Push all
		auto passed = Pass(p_args...);

		//Move the address of the function into EAX and call it
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(*m_pOutput, reinterpret_cast<int32_t>(p_pFunctionAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(*m_pOutput);

		//Pop all
		Pop(passed);
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
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::EAX>(*m_pOutput, reinterpret_cast<int32_t>(address.pAddress));
		BiaArchitecture::Operation<OP_CODE::CALL, REGISTER::EAX>(*m_pOutput);
	}
	inline void CommitTemporaryMembers(BiaMachineContext & p_context, temp_members p_parameter, int8_t p_cCount)
	{
		//Get position
		auto llPosition = m_pOutput->GetPosition();

		//Ovewrite
		m_pOutput->SetPosition(std::get<0>(p_parameter));

		PrepareTemporyMembers(p_cCount, &p_context);

		m_pOutput->SetPosition(llPosition);

		//Destruct
		Call(&BiaMachineContext::DestructTemporaryAddresses, &p_context, p_cCount, RegisterOffset<REGISTER::EBP, int8_t, true>(p_cCount * -4));

		//Clean up stack
		BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(*m_pOutput, static_cast<int8_t>(p_cCount * 4));
	}
	inline void DiscardTemporaryMembers(temp_members p_parameter)
	{
		m_pOutput->Move(std::get<0>(p_parameter), std::get<1>(p_parameter), m_pOutput->GetPosition() - std::get<1>(p_parameter));
	}
	inline void WriteTest()
	{
		BiaArchitecture::Operation<OP_CODE::TEST, REGISTER::EAX, REGISTER::EAX>(*m_pOutput, 0);
	}
	inline pass_count Pass()
	{
		return 0;
	}
	template<typename T, typename... _ARGS>
	inline pass_count Pass(T p_value, _ARGS... p_args)
	{
		auto passed = Pass(p_args...);

		return passed + Pass(p_value);
	}
	template<typename T>
	inline pass_count Pass(T p_value)
	{
		static_assert(sizeof(T) == 1 || sizeof(T) == 4 || sizeof(T) == 8, "Push parameter must of size 1, 4 or 8.");

		//8 bit
		if (sizeof(T) == 1)
			BiaArchitecture::Operation8<OP_CODE::PUSH>(*m_pOutput, *reinterpret_cast<int32_t*>(&p_value));
		//32 bit
		else if (sizeof(T) == 4)
		{
			//Save 3 bytes
			if (std::is_integral<T>::value && p_value <= 127 && p_value >= -128)
				BiaArchitecture::Operation8<OP_CODE::PUSH>(*m_pOutput, static_cast<int8_t>(p_value));
			//Push all 4 bytes
			else
				BiaArchitecture::Operation32<OP_CODE::PUSH>(*m_pOutput, *reinterpret_cast<int32_t*>(&p_value));
		}
		//64 bit
		else
		{
			BiaArchitecture::Operation32<OP_CODE::PUSH>(*m_pOutput, *reinterpret_cast<int64_t*>(&p_value) >> 32);
			BiaArchitecture::Operation32<OP_CODE::PUSH>(*m_pOutput, *reinterpret_cast<int32_t*>(&p_value));
		}

		return sizeof(T) == 8 ? 2 : 1;
	}
	template<typename T>
	inline pass_count Pass(T * p_pAddress)
	{
		BiaArchitecture::Operation32<OP_CODE::PUSH>(*m_pOutput, reinterpret_cast<int32_t>(p_pAddress));

		return 1;
	}
	template<REGISTER _REGISTER, typename _OFFSET, bool _EFFECTIVE_ADDRESS>
	inline pass_count Pass(RegisterOffset<_REGISTER, _OFFSET, _EFFECTIVE_ADDRESS> p_offset)
	{
		static_assert(std::is_same<_OFFSET, int32_t>::value || std::is_same<_OFFSET, int8_t>::value, "Invalid offset type.");

		//Push address
		if (_EFFECTIVE_ADDRESS)
		{
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::EAX, _REGISTER, _OFFSET>(*m_pOutput, p_offset.offset);
			BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EAX>(*m_pOutput);
		}
		else
		{
			//32 bit signed offset
			if (std::is_same<_OFFSET, int32_t>::value)
				BiaArchitecture::Operation32<OP_CODE::PUSH, _REGISTER>(*m_pOutput, p_offset.offset);
			//8 bit signed offset
			else
				BiaArchitecture::Operation8<OP_CODE::PUSH, _REGISTER>(*m_pOutput, p_offset.offset);
		}

		return 1;
	}
	template<REGISTER _REGISTER, bool _EFFECTIVE_ADDRESS>
	inline pass_count Pass(RegisterOffset<_REGISTER, void, _EFFECTIVE_ADDRESS> p_offset)
	{
		//Push address
		if (_EFFECTIVE_ADDRESS)
		{
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::EAX, _REGISTER, int8_t>(*m_pOutput, 0);
			BiaArchitecture::Operation<OP_CODE::PUSH, REGISTER::EAX>(*m_pOutput);
		}
		//Push register
		else
			BiaArchitecture::Operation<OP_CODE::PUSH, _REGISTER>(*m_pOutput);

		return 1;
	}
	inline position WriteJump(JUMP p_jump, int32_t p_nOffset = 0, position p_position = -1)
	{
		auto oldPos = m_pOutput->GetPosition();

		//Override
		if (p_position != -1)
			m_pOutput->SetPosition(p_position);
		
		auto pos = m_pOutput->GetPosition();

		switch (p_jump)
		{
		case JUMP::JUMP:
			BiaArchitecture::Operation32<OP_CODE::JUMP_RELATIVE>(*m_pOutput, p_nOffset - 5 - p_position);

			break;
		case JUMP::JUMP_IF_TRUE:
			BiaArchitecture::Operation32<OP_CODE::JUMP_NOT_EQUAL>(*m_pOutput, p_nOffset - 6 - p_position);

			break;
		case JUMP::JUMP_IF_FALSE:
			BiaArchitecture::Operation32<OP_CODE::JUMP_EQUAL>(*m_pOutput, p_nOffset - 6 - p_position);

			break;
		}

		//Go back
		if (p_position != -1)
			m_pOutput->SetPosition(oldPos);

		return pos;
	}
	inline temp_members ReserveTemporyMembers()
	{
		temp_members tmp;

		std::get<0>(tmp) = m_pOutput->GetPosition();

		PrepareTemporyMembers(0, nullptr);

		std::get<1>(tmp) = m_pOutput->GetPosition();

		return tmp;
	}
	inline static temporary_result TemporaryMember(int8_t p_cIndex)
	{
		return temporary_result(p_cIndex * -4);
	}
	inline stream::BiaOutputStream & GetBuffer()
	{
		return *m_pOutput;
	}
	inline static RegisterOffset<REGISTER::EAX, void, false> TestValueResult()
	{
		return RegisterOffset<REGISTER::EAX, void, false>();
	}
	inline static RegisterOffset<REGISTER::EAX, void, false> ResultValue()
	{
		return RegisterOffset<REGISTER::EAX, void, false>();
	}

private:
	stream::BiaOutputStream * m_pOutput;

	pass_count m_nPassed;


	template<typename T>
	inline void PassInstance(T * p_pInstance)
	{
		BiaArchitecture::Operation32<OP_CODE::MOVE, REGISTER::ECX>(*m_pOutput, reinterpret_cast<int32_t>(p_pInstance));
	}
	template<REGISTER _REGISTER, typename _OFFSET, bool _EFFECTIVE_ADDRESS>
	inline void PassInstance(RegisterOffset<_REGISTER, _OFFSET, _EFFECTIVE_ADDRESS> p_offset)
	{
		static_assert(std::is_same<_OFFSET, int32_t>::value || std::is_same<_OFFSET, int8_t>::value, "Invalid offset type.");

		//Effective address
		if (_EFFECTIVE_ADDRESS)
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::ECX, _REGISTER, _OFFSET>(*m_pOutput, p_offset.offset);
		//Just content
		else
			BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::ECX, _REGISTER, _OFFSET>(*m_pOutput, p_offset.offset);
	}
	template<REGISTER _REGISTER, bool _EFFECTIVE_ADDRESS>
	inline void PassInstance(RegisterOffset<_REGISTER, void, _EFFECTIVE_ADDRESS> p_offset)
	{
		//Effective address
		if (_EFFECTIVE_ADDRESS)
			BiaArchitecture::Operation<OP_CODE::LEA, REGISTER::ECX, _REGISTER, int8_t>(*m_pOutput, 0);
		//Just content
		else
			BiaArchitecture::Operation<OP_CODE::MOVE, REGISTER::ECX, _REGISTER, int8_t>(*m_pOutput, 0);
	}
	inline void Pop(pass_count p_pop)
	{
		if (p_pop > 0)
		{
			if (p_pop * 4 < 128)
				BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(*m_pOutput, static_cast<int8_t>(p_pop * 4));
			else
				BiaArchitecture::Operation32<OP_CODE::ADD, REGISTER::ESP>(*m_pOutput, p_pop * 4);
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
		BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(*m_pOutput, p_cCount * -4);

		//Push count and not esp because it is already on the stack
		Call(&BiaMachineContext::ConstructTemporaryAddresses, p_pContext, p_cCount, RegisterOffset<REGISTER::EBP, int8_t, true>(p_cCount * -4));
	}
};
#endif

}
}
}