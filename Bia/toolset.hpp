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
#include "passer.hpp"
#include "static_passer.hpp"
#include "member_passer.hpp"
#include "varg_member_passer.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if defined(BIA_COMPILER_MSVC) || defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG)
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
	typedef int32_t index_type;
	typedef int32_t temp_index_type;
	typedef register_offset<accumulator, void, false> test_result_register;
	typedef register_offset<base_pointer, int32_t, false> temp_result;
	typedef register_offset<accumulator, void, false> result_register;
	typedef register_offset<stack_pointer, int32_t, false> saved_result_register;

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
	toolset(stream::output_stream & _output, machine_context * _context) : _output(&_output), _global_passer(&_output)
	{
		this->_context = _context;

		// Create new stack frame for this entry point
		instruction<OP_CODE::PUSH, base_pointer>(_output);
		instruction<OP_CODE::MOVE, base_pointer, stack_pointer>(_output);

		// Allocate temp members
		_temp_member_pos = _output.position();

		instruction32<OP_CODE::SUB, stack_pointer>(_output, 0);

		call_member(&machine_context::create_on_stack, _context, register_offset<base_pointer, int32_t, true>(0), uint32_t(0));

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
#if defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_MSVC)
		if (true) {
#else
		if (_temp_count > 0) {
#endif
			// Overwrite temp member creation
			auto _current_pos = _output->position();

			_output->set_position(_temp_member_pos);

#if defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_MSVC)
			// Allocate temp members + shadow space + align stack
			instruction32<OP_CODE::SUB, stack_pointer>(*_output, align_stack((4 + _temp_count + 1) * element_size) - element_size);
#else
			// Allocate temp members + align stack
			instruction32<OP_CODE::SUB, stack_pointer>(*_output, align_stack((_temp_count + 1) * element_size) - element_size);
#endif

			call_member(&machine_context::create_on_stack, _context, register_offset<base_pointer, int32_t, true>((_temp_count) * -element_size), static_cast<uint32_t>(_temp_count));

			_output->set_position(_current_pos);

			// Member deletion
			call_member(&machine_context::destroy_from_stack, _context, static_cast<uint32_t>(_temp_count));

/*#if defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_MSVC)
			// Deallocate temp members + shadow space
			instruction32<OP_CODE::ADD, stack_pointer>(*_output, align_stack((4 + _temp_count + 1) * element_size) - element_size);
#else
			// Deallocate temp members
			instruction32<OP_CODE::ADD, stack_pointer>(*_output, align_stack((_temp_count + 1) * element_size) - element_size);
#endif*/

			// Clean up stack
			instruction<OP_CODE::MOVE, stack_pointer, base_pointer>(*_output);
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
		_global_passer.set_output(&_output);
	}
	/**
	 * Performs a static function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam Return The return type of the function.
	 * @tparam Arguments The arguments of the function.
	 * @tparam Arguments2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param _arguments The arguments for the function.
	 *
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass() and pop().
	*/
	template<typename Return, typename... Arguments, typename... Arguments2>
	void call_static(static_function_signature<Return, Arguments...> _function, Arguments2 &&... _arguments)
	{
		static_assert(sizeof...(Arguments) == sizeof...(Arguments2), "Argument count does not match.");

		// Push all parameters
		static_passer _passer(_global_passer);

		_passer.pass_all(std::forward<Arguments2>(_arguments)...);

		// Move the address of the function into EAX and call it
#if defined(BIA_ARCHITECTURE_X86_32)
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(_function));
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(_function));
#endif

		instruction<OP_CODE::CALL, accumulator>(*_output);

		_passer.pop_all();
	}
	/**
	 * Performs a member function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam Class The class.
	 * @tparam Return The return type of the function.
	 * @tparam Instance The instance type.
	 * @tparam Arguments The arguments of the function.
	 * @tparam Arguments2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param [in] _instance The class instance.
	 * @param _arguments The arguments for the function.
	 *
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass(), pass_instance() and pop().
	*/
	template<typename Class, typename Return, typename Instance, typename... Arguments, typename... Arguments2>
	void call_member(member_function_signature<Class, Return, Arguments...> _function, Instance _instance, Arguments2 &&... _arguments)
	{
		static_assert(std::is_const<Instance>::value == false, "Instance must not be const.");
		static_assert(sizeof...(Arguments) == sizeof...(Arguments2), "Argument count does not match.");

		// Push all parameters
		member_passer _passer(_global_passer);

		_passer.pass_all(_instance, std::forward<Arguments2>(_arguments)...);

		// Convert
		union
		{
			member_function_signature<Class, Return, Arguments...> member;
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

		_passer.pop_all();
	}
	/**
	 * Performs a member function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam Class The class.
	 * @tparam Return The return type of the function.
	 * @tparam Instance The instance type.
	 * @tparam Arguments The arguments of the function.
	 * @tparam Arguments2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param [in] _instance The class instance.
	 * @param _arguments The arguments for the function.
	 *
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass(), pass_instance() and pop().
	*/
	template<typename Class, typename Return, typename Instance, typename... Arguments, typename... Arguments2>
	void call_virtual(member_function_signature<Class, Return, Arguments...> _function, Instance _instance, Arguments2 &&... _arguments)
	{
		static_assert(std::is_const<Instance>::value == false, "Instance must not be const.");
		static_assert(sizeof...(Arguments) == sizeof...(Arguments2), "Argument count does not match.");

		// Push all parameters
		member_passer _passer(_global_passer);

		_passer.pass_all(_instance, std::forward<Arguments2>(_arguments)...);

		// Convert
		union
		{
			member_function_signature<Class, Return, Arguments...> member;
			void * address;
		} address;

		address.member = _function;

#if defined(BIA_ARCHITECTURE_X86_32) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		auto _index = reinterpret_cast<int32_t>(address.address) ^ 1;

		instruction<OP_CODE::MOVE, eax, ecx, void>(*_output);

		if (is_one_byte_value(_index)) {
			instruction<OP_CODE::CALL, eax>(*_output, static_cast<int8_t>(_index));
		} else {
			instruction<OP_CODE::CALL, eax>(*_output, _index);
		}
#elif defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		auto _index = static_cast<int32_t>(reinterpret_cast<int64_t>(address.address) ^ 1);

		instruction<OP_CODE::MOVE, rax, rdi, void>(*_output);

		if (is_one_byte_value(_index)) {
			instruction<OP_CODE::CALL, rax>(*_output, static_cast<int8_t>(_index));
		} else {
			instruction<OP_CODE::CALL, rax>(*_output, _index);
		}
#elif defined(BIA_ARCHITECTURE_X86_32)
		// Move the address of the function into EAX and call it
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(address.address));
		instruction<OP_CODE::CALL, accumulator>(*_output);
#elif defined(BIA_ARCHITECTURE_X86_64)
		// Move the address of the function into EAX and call it
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(address.address));
		instruction<OP_CODE::CALL, accumulator>(*_output);
#endif

		_passer.pop_all();
	}
	/**
	 * Performs a member function call.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.64.127.716
	 * @date 29-Apr-18
	 *
	 * @tparam Class The class.
	 * @tparam Return The return type of the function.
	 * @tparam Instance The instance type.
	 * @tparam Arguments The arguments of the function.
	 * @tparam Arguments2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param _instance The class instance.
	 * @param _arguments The arguments for the function.
	 *
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass(), pass_instance() and pop().
	*/
	template<typename Class, typename Return, typename Instance, typename... Arguments, typename... Arguments2>
	void call_virtual(const_member_function_signature<Class, Return, Arguments...> _function, Instance _instance, Arguments2 &&... _arguments)
	{
		static_assert(sizeof...(Arguments) == sizeof...(Arguments2), "Argument count does not match.");

		// Push all parameters
		member_passer _passer(_global_passer);

		_passer.pass_all(_instance, std::forward<Arguments2>(_arguments)...);

		// Convert
		union
		{
			const_member_function_signature<Class, Return, Arguments...> member;
			void * address;
		} address;

		address.member = _function;

#if defined(BIA_ARCHITECTURE_X86_32) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		auto _index = reinterpret_cast<int32_t>(address.address) ^ 1;

		instruction<OP_CODE::MOVE, eax, ecx, void>(*_output);

		if (is_one_byte_value(_index)) {
			instruction<OP_CODE::CALL, eax>(*_output, static_cast<int8_t>(_index));
		} else {
			instruction<OP_CODE::CALL, eax>(*_output, _index);
		}
#elif defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		auto _index = static_cast<int32_t>(reinterpret_cast<int64_t>(address.address) ^ 1);

		instruction<OP_CODE::MOVE, rax, rdi, void>(*_output);

		if (is_one_byte_value(_index)) {
			instruction<OP_CODE::CALL, rax>(*_output, static_cast<int8_t>(_index));
		} else {
			instruction<OP_CODE::CALL, rax>(*_output, _index);
		}
#elif defined(BIA_ARCHITECTURE_X86_32)
		// Move the address of the function into EAX and call it
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(address.address));
		instruction<OP_CODE::CALL, accumulator>(*_output);
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(address.address));
		instruction<OP_CODE::CALL, accumulator>(*_output);
#endif

		_passer.pop_all();
	}
	/**
	 * Performs a member function call with varg.
	 *
	 * @remarks Passing invalid parameters can lead to undefined behavior.
	 *
	 * @since 3.66.135.745
	 * @date 3-Aug-18
	 *
	 * @tparam Class The class.
	 * @tparam Return The return type of the function.
	 * @tparam Instance The instance type.
	 * @tparam Arguments The arguments of the function.
	 * @tparam Arguments2 The arguemtns that should be passed.
	 *
	 * @param _function The function address.
	 * @param [in] _instance The class instance.
	 * @param _variable_parameter An array with the variable parameters.
	 * @param _count The size of @a _variable_parameter.
	 * @param _arguments The arguments for the function.
	 *
	 * @throws See architecture::instruction32() and architecture::instruction().
	 * @throws See pass() and pop().
	*/
	template<typename Class, typename Return, typename Instance, typename... Arguments, typename... Arguments2>
	void call_virtual(varg_member_function_signature<Class, Return, Arguments...> _function, Instance _instance, varg_member_passer & _passer, Arguments2 &&... _arguments)
	{
		static_assert(std::is_const<Instance>::value == false, "Instance must not be const.");
		static_assert(sizeof...(Arguments) == sizeof...(Arguments2), "Argument count does not match.");

		// Push all parameters
		_passer.pass_all(_instance, std::forward<Arguments2>(_arguments)...);

		// Convert
		union
		{
			varg_member_function_signature<Class, Return, Arguments...> member;
			void * address;
		} address;

		address.member = _function;

#if defined(BIA_ARCHITECTURE_X86_32) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		auto _index = reinterpret_cast<int32_t>(address.address) ^ 1;

		instruction<OP_CODE::MOVE, eax, ecx, void>(*_output);

		if (is_one_byte_value(_index)) {
			instruction<OP_CODE::CALL, eax>(*_output, static_cast<int8_t>(_index));
		} else {
			instruction<OP_CODE::CALL, eax>(*_output, _index);
		}
#elif defined(BIA_ARCHITECTURE_X86_64) && (defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
		auto _index = static_cast<int32_t>(reinterpret_cast<int64_t>(address.address) ^ 1);

		instruction<OP_CODE::MOVE, r11, rdi, void>(*_output);

		if (is_one_byte_value(_index)) {
			instruction<OP_CODE::CALL, r11>(*_output, static_cast<int8_t>(_index));
		} else {
			instruction<OP_CODE::CALL, r11>(*_output, _index);
		}
#elif defined(BIA_ARCHITECTURE_X86_32)
		// Move the address of the function into EAX and call it
		instruction32<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int32_t>(address.address));
		instruction<OP_CODE::CALL, accumulator>(*_output);
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(*_output, reinterpret_cast<int64_t>(address.address));
		instruction<OP_CODE::CALL, accumulator>(*_output);
#endif

		_passer.pop_all();
}
	void write_test()
	{
		instruction<OP_CODE::TEST, eax, eax>(*_output);
	}
	varg_member_passer create_varg_passer() noexcept
	{
		return varg_member_passer(_global_passer);
	}
	position jump(JUMP _type, position _destination = 0, position _overwrite_pos = -1)
	{
		auto _old = _output->position();
		auto _current = _old;

		// Override
		if (_overwrite_pos != -1) {
			_current = _overwrite_pos;

			_output->set_position(_overwrite_pos);
		}

		switch (_type) {
		case JUMP::JUMP:
			instruction32<OP_CODE::JUMP_RELATIVE>(*_output, _destination - _current);

			break;
		case JUMP::JUMP_IF_TRUE:
			instruction32<OP_CODE::JUMP_NOT_EQUAL>(*_output, _destination - _current);

			break;
		case JUMP::JUMP_IF_FALSE:
			instruction32<OP_CODE::JUMP_EQUAL>(*_output, _destination - _current);

			break;
		}

		// Go back
		if (_overwrite_pos != -1) {
			_output->set_position(_old);

			return _overwrite_pos;
		}

		return _old;
	}
	static temp_result to_temp_member(temp_index_type _index) noexcept
	{
		return temp_result((0 + _index) * -element_size);
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
	/** The parameter passer manager. */
	passer _global_passer;
};
#endif

}
}
}
