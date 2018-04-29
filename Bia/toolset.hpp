#pragma once

#include <cstdint>
#include <type_traits>
#include <tuple>
#include <initializer_list>
#include <utility>

#include "config.hpp"
#include "architecture.hpp"
#include "output_stream.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if defined(BIA_COMPILER_MSVC) || defined(BIA_COMPILER_GNU)
class toolset
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
	typedef register_offset<REGISTER::EBP, int8_t, false> temp_result;
	typedef int32_t pass_count;
	typedef int32_t temp_index_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param [in] _output The output stream.
	 *
	 * @throws See architecture::add_instruction().
	*/
	toolset(stream::output_stream & _output) : _output(&_output)
	{
		_passed = 0;

		// Create new stack frame for this entry point
		architecture::add_instruction<OP_CODE::PUSH, REGISTER::EBP>(*this->_output);
		architecture::add_instruction<OP_CODE::MOVE, REGISTER::EBP, REGISTER::ESP>(*this->_output, 0);
	}
	/**
	 * Adds some necessary cleanup instruction to the output stream.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @throws See architecture::add_instruction().
	*/
	void finalize()
	{
		// Cleanup stack frame and return
		architecture::add_instruction<OP_CODE::LEAVE>(*_output);
		architecture::add_instruction<OP_CODE::RETURN_NEAR>(*_output);
	}
	/**
	 * Sets the output stream.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param [in] _output The new output stream.
	*/
	void set_output(stream::output_stream & _output) noexcept
	{
		this->_output = &_output;
	}
	/**
	 * Performs a static function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam _Return The return type of the function.
	 * @tparam _Args The arguments of the function.
	 * @tparam _Args2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param _args The arguments for the function.
	 *
	 * @throws See architecture::add_instruction32() and architecture::add_instruction().
	 * @throws See pass() and pop().
	*/
	template<typename _Return, typename... _Args, typename... _Args2>
	void call(static_function_signature<_Return, _Args...> _function, _Args2 &&... _args)
	{
		static_assert(sizeof...(_Args) != sizeof...(_Args2), "Argument count does not match.");

		// Push all parameters
		auto _passed = pass(std::forward<_Args2>(_args)...);

		// Move the address of the function into EAX and call it
		architecture::add_instruction32<OP_CODE::MOVE, REGISTER::EAX>(*_output, reinterpret_cast<int32_t>(_function));
		architecture::add_instruction<OP_CODE::CALL, REGISTER::EAX>(*_output);

		// Pop parameter
		pop(_passed);
	}
	/**
	 * Performs a member function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam _Class The class.
	 * @tparam _Return The return type of the function.
	 * @tparam _Instance The instance type.
	 * @tparam _Args The arguments of the function.
	 * @tparam _Args2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param [in] _instance The class instance.
	 * @param _args The arguments for the function.
	 *
	 * @throws See architecture::add_instruction32() and architecture::add_instruction().
	 * @throws See pass() and pop().
	*/
	template<typename _Class, typename _Return, typename _Instance, typename... _Args, typename... _Args2>
	void call(member_function_signature<_Class, _Return, _Args...> _function, _Instance _instance, _Args2 &&... _args)
	{
		static_assert(std::is_const<_Instance>::value == false, "Instance must not be const.");

		// Push all parameters
		auto _passed = pass(std::forward<_Args2>(_args)...);
		
		pass_instance(_instance);

		// Convert
		union
		{
			_Return(_Class::*member)(_Args...);
			void * address;
		} address;
		
		address.member = _function;

		// Move the address of the function into EAX and call it
		architecture::add_instruction32<OP_CODE::MOVE, REGISTER::EAX>(*_output, reinterpret_cast<int32_t>(address.address));
		architecture::add_instruction<OP_CODE::CALL, REGISTER::EAX>(*_output);

#if defined(BIA_COMPILER_GNU)
		// Pop
		pop(_passed);
#endif
	}
	/**
	 * Performs a member function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam _Class The class.
	 * @tparam _Return The return type of the function.
	 * @tparam _Instance The instance type.
	 * @tparam _Args The arguments of the function.
	 * @tparam _Args2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param _instance The class instance.
	 * @param _args The arguments for the function.
	 *
	 * @throws See architecture::add_instruction32() and architecture::add_instruction().
	 * @throws See pass() and pop().
	*/
	template<typename _Class, typename _Return, typename _Instance, typename... _Args, typename... _Args2>
	void call(const_member_function_signature<_Class, _Return, _Args...> _function, _Instance _instance, _Args2 &&... _args)
	{
		// Push all parameters
		auto _passed = pass(std::forward<_Args2>(_args)...);
		
		pass_instance(_instance);

		// Convert
		union
		{
			_Return(_Class::*member)(_Args...) const;
			void * address;
		} address;
		
		address.member = _function;

		// Move the address of the function into EAX and call it
		architecture::add_instruction32<OP_CODE::MOVE, REGISTER::EAX>(*_output, reinterpret_cast<int32_t>(address.address));
		architecture::add_instruction<OP_CODE::CALL, REGISTER::EAX>(*_output);

#if defined(BIA_COMPILER_GNU)
		// Pop
		pop(_passed);
#endif
	}
	inline void CommitTemporaryMembers(BiaMachineContext & p_context, temp_members p_parameter, int8_t p_cCount)
	{
		//Get position
		auto llPosition = _output->GetPosition();

		//Ovewrite
		_output->SetPosition(std::get<0>(p_parameter));

		PrepareTemporyMembers(p_cCount, &p_context);

		_output->SetPosition(llPosition);

		//Destruct
		Call(&BiaMachineContext::DestructTemporaryAddresses, &p_context, p_cCount, register_offset<REGISTER::EBP, int8_t, true>(p_cCount * -4));

		//Clean up stack
		BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(*_output, static_cast<int8_t>(p_cCount * 4));
	}
	inline void DiscardTemporaryMembers(temp_members p_parameter)
	{
		_output->Move(std::get<0>(p_parameter), std::get<1>(p_parameter), _output->GetPosition() - std::get<1>(p_parameter));
	}
	void write_empty_test()
	{
		architecture::add_instruction<OP_CODE::TEST, REGISTER::EAX, REGISTER::EAX>(*_output, 0);
	}
	pass_count pass() noexcept
	{
		return 0;
	}
	template<typename _Ty, typename... _Args>
	pass_count pass(_Ty _value, _Args &&... _args)
	{
		auto _passed = pass(std::forward<_Args>(_args)...);

		return _passed + pass(_value);
	}
	template<typename _Ty>
	typename std::enable_if<sizeof(_Ty) == 1, pass_count>::type pass(_Ty _value)
	{
		architecture::add_instruction8<OP_CODE::PUSH>(*_output, static_cast<int8_t>(_value));

		return 1;
	}
	template<typename _Ty>
	typename std::enable_if<sizeof(_Ty) == 4, pass_count>::type pass(_Ty _value)
	{
		// Save 3 bytes
		if (is_one_byte_value(_value)) {
			architecture::add_instruction8<OP_CODE::PUSH>(*_output, static_cast<int8_t>(_value));
		}
		// Push all 4 bytes
		else {
			architecture::add_instruction32<OP_CODE::PUSH>(*_output, *reinterpret_cast<int32_t*>(&_value));
		}

		return 1;
	}
	template<typename _Ty>
	typename std::enable_if<sizeof(_Ty) == 8, pass_count>::type pass(_Ty _value)
	{
		pass(static_cast<int32_t>(*reinterpret_cast<int64_t*>(&_value) >> 32));
		pass(*reinterpret_cast<int32_t*>(&_value));

		return 2;
	}
	template<typename _Ty>
	pass_count pass(_Ty * _ptr)
	{
		return pass(reinterpret_cast<intptr_t>(_ptr));
	}
	template<REGISTER _Register, typename _Offset, bool _Effective_address>
	pass_count pass(register_offset<_Register, _Offset, _Effective_address> _offset)
	{
		static_assert(std::is_same<_Offset, int32_t>::value || std::is_same<_Offset, int8_t>::value, "Invalid offset type.");

		// Push address
		if (_Effective_address) {
			architecture::add_instruction<OP_CODE::LEA, REGISTER::EAX, _Register, _Offset>(*_output, _offset.offset);
			architecture::add_instruction<OP_CODE::PUSH, REGISTER::EAX>(*_output);
		} else {
			// 32 bit signed offset
			if (std::is_same<_Offset, int32_t>::value) {
				architecture::add_instruction32<OP_CODE::PUSH, _Register>(*_output, _offset.offset);
			}
			// 8 bit signed offset
			else {
				architecture::add_instruction8<OP_CODE::PUSH, _Register>(*_output, _offset.offset);
			}
		}

		return 1;
	}
	template<REGISTER _Register, bool _Effective_address>
	pass_count pass(register_offset<_Register, void, _Effective_address> _offset)
	{
		// Push address
		if (_Effective_address) {
			architecture::add_instruction<OP_CODE::LEA, REGISTER::EAX, _Register, int8_t>(*_output, 0);
			architecture::add_instruction<OP_CODE::PUSH, REGISTER::EAX>(*_output);
		}
		// Push register
		else {
			architecture::add_instruction<OP_CODE::PUSH, _Register>(*_output);
		}

		return 1;
	}
	inline position WriteJump(JUMP p_jump, position p_destination = 0, position p_start = -1)
	{
		auto oldPos = _output->GetPosition();

		//Override
		if (p_start != -1)
			_output->SetPosition(p_start);
		
		auto pos = _output->GetPosition();

		switch (p_jump)
		{
		case JUMP::JUMP:
			BiaArchitecture::Operation32<OP_CODE::JUMP_RELATIVE>(*_output, p_destination - 5 - p_start);

			break;
		case JUMP::JUMP_IF_TRUE:
			BiaArchitecture::Operation32<OP_CODE::JUMP_NOT_EQUAL>(*_output, p_destination - 6 - p_start);

			break;
		case JUMP::JUMP_IF_FALSE:
			BiaArchitecture::Operation32<OP_CODE::JUMP_EQUAL>(*_output, p_destination - 6 - p_start);

			break;
		}

		//Go back
		if (p_start != -1)
			_output->SetPosition(oldPos);

		return pos;
	}
	inline temp_members ReserveTemporyMembers()
	{
		temp_members tmp;

		std::get<0>(tmp) = _output->GetPosition();

		PrepareTemporyMembers(0, nullptr);

		std::get<1>(tmp) = _output->GetPosition();

		return tmp;
	}
	static temp_result to_temp_member(int8_t _index) noexcept
	{
		return temp_result(_index * -4);
	}
	stream::output_stream & get_output_stream() noexcept
	{
		return *_output;
	}
	static register_offset<REGISTER::EAX, void, false> get_test_result_value() noexcept
	{
		return register_offset<REGISTER::EAX, void, false>();
	}
	static register_offset<REGISTER::EAX, void, false> get_result_value() noexcept
	{
		return register_offset<REGISTER::EAX, void, false>();
	}

private:
	/** The output stream for the machine code. */
	stream::output_stream * _output;

	pass_count _passed;


	template<typename _Ty>
	void pass_instance(_Ty * _instance)
	{
		architecture::add_instruction32<OP_CODE::MOVE, REGISTER::ECX>(*_output, reinterpret_cast<int32_t>(_instance));
	}
	template<REGISTER _Register, typename _Offset, bool _Effective_address>
	void pass_instance(register_offset<_Register, _Offset, _Effective_address> _offset)
	{
		static_assert(std::is_same<_Offset, int32_t>::value || std::is_same<_Offset, int8_t>::value, "Invalid offset type.");

		//Effective address
		if (_Effective_address) {
			architecture::add_instruction<OP_CODE::LEA, REGISTER::ECX, _Register, _Offset>(*_output, _offset.offset);
		}
		// Just content
		else {
			architecture::add_instruction<OP_CODE::MOVE, REGISTER::ECX, _Register, _Offset>(*_output, _offset.offset);
		}
	}
	template<REGISTER _Register, bool _Effective_address>
	void pass_instance(register_offset<_Register, void, _Effective_address> _offset)
	{
		//Effective address
		if (_Effective_address) {
			architecture::add_instruction<OP_CODE::LEA, REGISTER::ECX, _Register, int8_t>(*_output, 0);
		}
		//Just content
		else {
			architecture::add_instruction<OP_CODE::MOVE, REGISTER::ECX, _Register, int8_t>(*_output, 0);
		}
	}
	inline void Pop(pass_count p_pop)
	{
		if (p_pop > 0)
		{
			if (p_pop * 4 < 128)
				BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(*_output, static_cast<int8_t>(p_pop * 4));
			else
				BiaArchitecture::Operation32<OP_CODE::ADD, REGISTER::ESP>(*_output, p_pop * 4);
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
	void PrepareTemporyMembers(int8_t p_cCount, BiaMachineContext * p_pContext)
	{
		//Create space for member pointers; add because -128 is better than 127
		BiaArchitecture::Operation8<OP_CODE::ADD, REGISTER::ESP>(*_output, p_cCount * -4);

		//Push count and not esp because it is already on the stack
		Call(&BiaMachineContext::ConstructTemporaryAddresses, p_pContext, p_cCount, register_offset<REGISTER::EBP, int8_t, true>(p_cCount * -4));
	}
	template<typename _Ty>
	static bool is_one_byte_value(_Ty _value) noexcept
	{
		return false;
	}
	static bool is_one_byte_value(int32_t _value) noexcept
	{
		return _value <= 127 && _value >= -128;
	}
	static bool is_one_byte_value(uint32_t _value) noexcept
	{
		return _value <= 127;
	}
};
#endif

}
}
}