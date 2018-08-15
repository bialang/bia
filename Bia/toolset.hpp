#pragma once

#include <cstdint>
#include <type_traits>
#include <tuple>
#include <initializer_list>
#include <utility>
#include <limits>

#include "config.hpp"
#include "architecture.hpp"
#include "output_stream.hpp"
#include "machine_context.hpp"
#include "member.hpp"
#include "type_traits.hpp"


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
	typedef int32_t pass_count;
	typedef int32_t temp_index_type;
	typedef register_offset<REGISTER::EAX, void, false> test_result_register;
#if defined(BIA_ARCHITECTURE_X86_32)
	typedef register_offset<REGISTER::EBP, int8_t, false> temp_result;
	typedef register_offset<REGISTER::EAX, void, false> result_register;
	typedef register_offset<REGISTER::ESP, int8_t, false> saved_result_register;
#elif defined(BIA_ARCHITECTURE_X86_64)
	typedef register_offset<REGISTER::RBP, int8_t, false> temp_result;
	typedef register_offset<REGISTER::RAX, void, false> result_register;
	typedef register_offset<REGISTER::RSP, int8_t, false> saved_result_register;
#endif

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param [in] _output The output stream.
	 * @param [in] _context The machine context.
	 *
	 * @throws See architecture::instruction().
	*/
	toolset(stream::output_stream & _output, machine_context * _context) : _output(&_output)
	{
		this->_context = _context;

		// Create new stack frame for this entry point
		instruction<OP_CODE::PUSH, base_pointer>(_output);
		instruction<OP_CODE::MOVE, base_pointer, stack_pointer>(_output);

		// Allocate temp members
		_temp_member_pos = _output.position();

		instruction32<OP_CODE::SUB, stack_pointer>(_output, 0);
		call(&machine_context::create_on_stack, _context, register_offset<base_pointer, int32_t, true>(0), uint32_t(0));

		_setup_end_pos = _output.position();
	}
	/**
	 * Adds some necessary cleanup instruction to the output stream.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @param _temp_count The amount of temp variables.
	 *
	 * @throws See architecture::instruction().
	*/
	void finalize(temp_index_type _temp_count)
	{
		if (_temp_count > std::numeric_limits<temp_index_type>::max() / static_cast<int>(sizeof(void*)) || _temp_count < 0) {
			throw 1;
		}

		// Adjust setup
		if (_temp_count > 0) {
			// Overwrite temp member creation
			auto _current_pos = _output->position();

			_output->set_position(_temp_member_pos);

			instruction32<OP_CODE::SUB, stack_pointer>(*_output, _temp_count * element_size);
			call(&machine_context::create_on_stack, _context, register_offset<base_pointer, int32_t, true>(-_temp_count * element_size), static_cast<uint32_t>(_temp_count));

			_output->set_position(_current_pos);

			// Member deletion
			call(&machine_context::destroy_from_stack, _context, static_cast<uint32_t>(_temp_count));
			instruction32<OP_CODE::ADD, stack_pointer>(*_output, _temp_count * sizeof(void*));

			// Clean up stack
			instruction<OP_CODE::POP, base_pointer>(*_output);
		} // Skip setup
		else {
			_output->set_beginning(_setup_end_pos);
		}

		// Return
		instruction<OP_CODE::RETURN_NEAR>(*_output);
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
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass() and pop().
	*/
	template<typename _Return, typename... _Args, typename... _Args2>
	void call(static_function_signature<_Return, _Args...> _function, _Args2 &&... _args)
	{
		static_assert(sizeof...(_Args) == sizeof...(_Args2), "Argument count does not match.");

		// Push all parameters
		auto _passed = pass(std::forward<_Args2>(_args)...);

		// Move the address of the function into EAX and call it
#if defined(BIA_ARCHITECTURE_X86_32)
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(_function));
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(_function));
#endif

		instruction<OP_CODE::CALL, accumulator>(*_output);

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
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass(), pass_instance() and pop().
	*/
	template<typename _Class, typename _Return, typename _Instance, typename... _Args, typename... _Args2>
	void call(member_function_signature<_Class, _Return, _Args...> _function, _Instance _instance, _Args2 &&... _args)
	{
		static_assert(std::is_const<_Instance>::value == false, "Instance must not be const.");
		static_assert(sizeof...(_Args) == sizeof...(_Args2), "Argument count does not match.");

		// Push all parameters
		auto _passed = pass(std::forward<_Args2>(_args)...);

		pass_instance(_instance);

		// Convert
		union
		{
			member_function_signature<_Class, _Return, _Args...> member;
			void * address;
		} address;

		address.member = _function;

		// Move the address of the function into EAX and call it
#if defined(BIA_ARCHITECTURE_X86_32)
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(address.address));
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(address.address));
#endif

		instruction<OP_CODE::CALL, accumulator>(*_output);

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
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass(), pass_instance() and pop().
	*/
	template<typename _Class, typename _Return, typename _Instance, typename... _Args, typename... _Args2>
	void call(const_member_function_signature<_Class, _Return, _Args...> _function, _Instance _instance, _Args2 &&... _args)
	{
		static_assert(sizeof...(_Args) == sizeof...(_Args2), "Argument count does not match.");

		// Push all parameters
		auto _passed = pass(std::forward<_Args2>(_args)...);

		pass_instance(_instance);

		// Convert
		union
		{
			const_member_function_signature<_Class, _Return, _Args...> member;
			void * address;
		} address;

		address.member = _function;

		// Move the address of the function into EAX and call it
#if defined(BIA_ARCHITECTURE_X86_32)
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(address.address));
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(address.address));
#endif

		instruction<OP_CODE::CALL, accumulator>(*_output);

#if defined(BIA_COMPILER_GNU)
		// Pop
		pop(_passed);
#endif
	}
	/**
	 * Performs a member function call with varg.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.66.135.745
	 * @date 3-Aug-18
	 *
	 * @tparam _Class The class.
	 * @tparam _Return The return type of the function.
	 * @tparam _Instance The instance type.
	 * @tparam _Args The arguments of the function.
	 * @tparam _Args2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param [in] _instance The class instance.
	 * @param _variable_parameter An array with the variable parameters.
	 * @param _count The size of @a _variable_parameter.
	 * @param _args The arguments for the function.
	 *
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass() and pop().
	*/
	template<typename _Class, typename _Return, typename _Instance, typename... _Args, typename... _Args2>
	void call(varg_member_function_signature<_Class, _Return, _Args...> _function, _Instance _instance, pass_count _passed_vargs, _Args2 &&... _args)
	{
		static_assert(std::is_const<_Instance>::value == false, "Instance must not be const.");
		static_assert(sizeof...(_Args) == sizeof...(_Args2), "Argument count does not match.");

		pass_count _passed = _passed_vargs;

		// Push all parameters
		_passed += pass(std::forward<_Args2>(_args)...);

		// Push instance
		if (std::is_same<_Instance, result_register>::value) {
			// +1 for the saved result value
			_passed += pass(saved_result_value(_passed)) + 1;
		} else {
			_passed += pass(_instance);
		}

		// Convert
		union
		{
			varg_member_function_signature<_Class, _Return, _Args...> member;
			void * address;
		} address;

		address.member = _function;

		// Move the address of the function into EAX and call it
#if defined(BIA_ARCHITECTURE_X86_32)
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(address.address));
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(address.address));
#endif

		instruction<OP_CODE::CALL, accumulator>(*_output);

		// Pop
		pop(_passed);
	}
	void write_test()
	{
		instruction<OP_CODE::XOR, REGISTER::EAX, REGISTER::EAX>(*_output);
	}
	/**
	 * Reverts the last action with the parameter.
	 *
	 * @since 3.67.135.749
	 * @date 6-Aug-18
	 *
	 * @param _code The return code the revertable action.
	 *
	 * @throws See stream::output_stream::set_position().
	*/
	void revert_action(position _code)
	{
		_output->set_position(_code);
	}
	/**
	 * Saves the result value.
	 *
	 * @since 3.67.135.749
	 * @date 6-Aug-18
	 *
	 * @throws See architecture::instruction().
	*/
	void save_result_value()
	{
		instruction<OP_CODE::PUSH, result_register::register_value>(*_output);
	}
	template<typename _Ty>
	pass_count pass_varg(_Ty _value)
	{
		return pass(_value);
	}
	position jump(JUMP _type, position _destination = 0, position _start = -1)
	{
		auto _old = _output->position();

		// Override
		if (_start != -1) {
			_output->set_position(_start);
		}

		switch (_type) {
		case JUMP::JUMP:
			instruction32<OP_CODE::JUMP_RELATIVE>(*_output, _destination - 5 - _start);

			break;
		case JUMP::JUMP_IF_TRUE:
			instruction32<OP_CODE::JUMP_NOT_EQUAL>(*_output, _destination - 6 - _start);

			break;
		case JUMP::JUMP_IF_FALSE:
			instruction32<OP_CODE::JUMP_EQUAL>(*_output, _destination - 6 - _start);

			break;
		}

		// Go back
		if (_start != -1) {
			_output->set_position(_old);

			return _start;
		}

		return _old;
	}
	static temp_result to_temp_member(temp_index_type _index) noexcept
	{
		return temp_result(_index * -4);
	}
	stream::output_stream & output_stream() noexcept
	{
		return *_output;
	}
	static test_result_register test_result_value() noexcept
	{
		return test_result_register();
	}
	static result_register result_value() noexcept
	{
		return result_register();
	}

private:
	/** The output stream for the machine code. */
	stream::output_stream * _output;
	/** The position of the temp member creation. */
	stream::output_stream::cursor_type _temp_member_pos;
	/** The end position of the setup. */
	stream::output_stream::cursor_type _setup_end_pos;
	/** The machine context. */
	machine_context * _context;


	template<typename _Ty>
	void pass_instance(_Ty * _instance)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		instruction32<OP_CODE::MOVE, REGISTER::ECX>(*_output, reinterpret_cast<int32_t>(_instance));
#elif defined(BIA_ARCHITECTURE_X86_64)
#error "fix me"
		instruction64<OP_CODE::MOVE, REGISTER::>(*_output, reinterpret_cast<int64_t>(_instance));
#endif
	}
	template<REGISTER _Register, typename _Offset, bool _Effective_address>
	void pass_instance(register_offset<_Register, _Offset, _Effective_address> _offset)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		//Effective address
		if (_Effective_address) {
			instruction<OP_CODE::LEA, REGISTER::ECX, _offset.register_value>(*_output, _offset.offset);
		} // Just content
		else {
			instruction<OP_CODE::MOVE, REGISTER::ECX, _offset.register_value>(*_output, _offset.offset);
		}
#elif defined(BIA_ARCHITECTURE_X86_64)
#error "fix me"
#endif
	}
	/*template<REGISTER _Register, bool _Effective_address>
	void pass_instance(register_offset<_Register, void, _Effective_address> _offset)
	{
		architecture::instruction<OP_CODE::MOVE, REGISTER::ECX, _Register, int8_t>(*_output, 0);
	}*/
	void pop(pass_count _count)
	{
		if (_count > 0) {
			if (_count * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(*_output, static_cast<int8_t>(_count * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(*_output, static_cast<int32_t>(_count * element_size));
			}
		}
	}
	template<typename _Ty>
	static bool is_one_byte_value(_Ty _value) noexcept
	{
		return false;
	}
	static bool is_one_byte_value(int32_t _value) noexcept
	{
		return _value <= std::numeric_limits<int8_t>::max() && _value >= std::numeric_limits<int8_t>::min();
	}
	static bool is_one_byte_value(uint32_t _value) noexcept
	{
		return _value <= std::numeric_limits<int8_t>::max();
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
	pass_count pass(std::nullptr_t)
	{
		return pass(intptr_t(0));
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 1, pass_count>::type pass(_Ty _value)
	{
		instruction8<OP_CODE::PUSH>(*_output, *reinterpret_cast<int8_t*>(&_value));

		return 1;
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 4, pass_count>::type pass(_Ty _value)
	{
		// Save 3 bytes
		if (is_one_byte_value(_value)) {
			instruction8<OP_CODE::PUSH>(*_output, static_cast<int8_t>(_value));
		} // Push all 4 bytes
		else {
			instruction32<OP_CODE::PUSH>(*_output, *reinterpret_cast<int32_t*>(&_value));
		}

		return 1;
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8, pass_count>::type pass(_Ty _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		pass(static_cast<int32_t>(*reinterpret_cast<int64_t*>(&_value) >> 32));
		pass(*reinterpret_cast<int32_t*>(&_value));

		return 2;
#elif
#error "fix me"
#endif
	}
	template<typename _Ty>
	pass_count pass(_Ty * _ptr)
	{
		return pass(reinterpret_cast<intptr_t>(_ptr));
	}
	template<REGISTER _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value, pass_count>::type pass(register_offset<_Register, _Offset, true> _offset)
	{
		// Push address
		instruction<OP_CODE::LEA, accumulator, _offset.register_value>(*_output, _offset.offset);
		instruction<OP_CODE::PUSH, accumulator>(*_output);

		return 1;
	}
	template<REGISTER _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value, pass_count>::type pass(register_offset<_Register, _Offset, false> _offset)
	{
		// Push address
		instruction<OP_CODE::PUSH, _offset.register_value>(*_output, _offset.offset);

		return 1;
	}
	template<REGISTER _Register, bool _Effective_address>
	pass_count pass(register_offset<_Register, void, _Effective_address> _offset)
	{
		// Push address
		if (_Effective_address) {
			instruction<OP_CODE::LEA, accumulator, _offset.register_value, int8_t>(*_output, 0);
			instruction<OP_CODE::PUSH, accumulator>(*_output);
		} // Push register
		else {
			instruction<OP_CODE::PUSH, _offset.register_value>(*_output);
		}

		return 1;
	}	
	/**
	 * Returns the saved result value.
	 *
	 * @since 3.67.135.749
	 * @date 6-Aug-18
	 *
	 * @param _passed The pass count since the save.
	 *
	 * @return The save destination.
	*/
	static saved_result_register saved_result_value(pass_count _passed) noexcept
	{
		return saved_result_register(_passed * 4);
	}
};
#endif

}
}
}
