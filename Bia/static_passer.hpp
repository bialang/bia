#pragma once

#include <type_traits>
#include <algorithm>
#include <tuple>

#include "config.hpp"
#include "passer.hpp"
#include "architecture.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if (defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)) && (defined(BIA_COMPILER_MSVC) || defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
/**
 * @brief Passes parameters of a static function.
 *
 * Passes parameters of a static function.
*/
class static_passer
{
public:
	typedef passer::pass_count_type pass_count_type;

	static_passer(passer & _passer) noexcept : _passer(_passer)
	{
		_count_only = false;
		_caller_pops_parameters = false;
		_caller_pops_padding = true;
		_pushed = 0;
		_integral_passed = 0;
		_floating_point_passed = 0;
	}
	virtual ~static_passer() = default;
	virtual void pop_all()
	{
		_passer.pop();
	}
	template<typename... Arguments>
	void pass_all(Arguments... _arguments)
	{
		pass_count_type _to_be_pushed;

		// Count parameters
		std::tie(_to_be_pushed, std::ignore, std::ignore) = count_arguments(_arguments...);

#if defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_MSVC)
		// Allocate shadow space
		if (_to_be_pushed + _pushed) {
			_pushed += 4;
			_passer._stack_offset += 4;
		}
#endif

		_passer.prepare_pushing(_pushed, _to_be_pushed, _caller_pops_parameters, _caller_pops_padding);

		// Pass arguments
		pass(_arguments...);

#if defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_MSVC)
		// Allocate shadow space
		if (_pushed) {
			instruction8<OP_CODE::SUB, stack_pointer>(_passer._output, 4 * element_size);
		}
#endif
	}

protected:
	/** If true, nothing will be written to the._output. */
	bool _count_only;
	/** Whether the caller cleans the parameters after a funtion call or not. */
	bool _caller_pops_parameters;
	/** Whether the caller cleans the padding after a function call or not. */
	bool _caller_pops_padding;
	/** The._output stream. */
	passer & _passer;
	/** The amount of pushed elements. */
	pass_count_type _pushed;
	/** The amount of integer values passed by register. */
	pass_count_type _integral_passed;
	/** The amount of floating point values passed by register. */
	pass_count_type _floating_point_passed;


	void pass() noexcept
	{
	}
	template<typename Type, typename... Arguments>
	void pass(Type _value, Arguments... _arguments)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		if (sizeof(Type) <= element_size) {
			switch (_integral_passed) {
			case 0:
			{
				if (!_count_only) {
					register_pass<ecx>(_value);
				}

				break;
			}
			case 1:
			{
				if (!_count_only) {
					register_pass<edx>(_value);
				}

				break;
			}
			default:
				goto gt_push;
			}
		} else {
#if defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG)
			_integral_passed += 2;
#endif

			++_pushed;
			++_passer._stack_offset;

			goto gt_push;
		}
#elif defined(BIA_COMPILER_MSVC)
		switch (_integral_passed + _floating_point_passed) {
		case 0:
		{
			if (!_count_only) {
				register_pass<rcx>(_value);
			}

			break;
		}
		case 1:
		{
			if (!_count_only) {
				register_pass<rdx>(_value);
			}

			break;
		}
		case 2:
		{
			if (!_count_only) {
				register_pass<r8>(_value);
			}

			break;
		}
		case 3:
		{
			if (!_count_only) {
				register_pass<r9>(_value);
			}

			break;
		}
		default:
			goto gt_push;
		}
#else
		switch (_integral_passed) {
		case 0:
		{
			if (!_count_only) {
				register_pass<rdi>(_value);
			}

			break;
		}
		case 1:
		{
			if (!_count_only) {
				register_pass<rsi>(_value);
			}

			break;
		}
		case 2:
		{
			if (!_count_only) {
				register_pass<rdx>(_value);
			}

			break;
		}
		case 3:
		{
			if (!_count_only) {
				register_pass<rcx>(_value);
			}

			break;
		}
		case 4:
		{
			if (!_count_only) {
				register_pass<r8>(_value);
			}

			break;
		}
		case 5:
		{
			if (!_count_only) {
				register_pass<r9>(_value);
			}

			break;
		}
		default:
			goto gt_push;
		}
#endif

		++_integral_passed;

		// Pass rest
		pass(_arguments...);

		return;

	gt_push:;
		pass(_arguments...);

		if (!_count_only) {
			push(_value);
		}

		++_pushed;
		++_passer._stack_offset;
	}
	template<typename... Arguments>
	void pass(double _value, Arguments... _arguments)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
#if defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG)
		_integral_passed += 2;
#endif

		++_pushed;
		++_passer._stack_offset;

		goto gt_push;
#elif defined(BIA_COMPILER_MSVC)
		switch (_floating_point_passed + _integral_passed) {
		case 0:
		{
			if (!_count_only) {
				register_pass<xmm0>(_value);
			}

			break;
		}
		case 1:
		{
			if (!_count_only) {
				register_pass<xmm1>(_value);
			}

			break;
		}
		case 2:
		{
			if (!_count_only) {
				register_pass<xmm2>(_value);
			}

			break;
		}
		case 3:
		{
			if (!_count_only) {
				register_pass<xmm3>(_value);
			}

			break;
		}
		default:
			goto gt_push;
		}
#else
		switch (_floating_point_passed) {
		case 0:
		{
			if (!_count_only) {
				register_pass<xmm0>(_value);
			}

			break;
		}
		case 1:
		{
			if (!_count_only) {
				register_pass<xmm1>(_value);
			}

			break;
		}
		case 2:
		{
			if (!_count_only) {
				register_pass<xmm2>(_value);
			}

			break;
		}
		case 3:
		{
			if (!_count_only) {
				register_pass<xmm3>(_value);
			}

			break;
		}
		case 4:
		{
			if (!_count_only) {
				register_pass<xmm4>(_value);
			}

			break;
		}
		case 5:
		{
			if (!_count_only) {
				register_pass<xmm5>(_value);
			}

			break;
		}
		case 6:
		{
			if (!_count_only) {
				register_pass<xmm6>(_value);
			}

			break;
		}
		case 7:
		{
			if (!_count_only) {
				register_pass<xmm7>(_value);
			}

			break;
		}
		default:
			goto gt_push;
		}
#endif

		++_floating_point_passed;

		// Pass rest
		pass(_arguments...);

		return;

	gt_push:;
		pass(_arguments...);

		if (!_count_only) {
			push(_value);
		}

		++_pushed;
		++_passer._stack_offset;
	}
	void push(reserved_parameter _value)
	{
		push(register_offset<accumulator, void, false>());
	}
	void push(std::nullptr_t _value)
	{
		push(intptr_t(0));
	}
	template<typename Type>
	void push(Type * _ptr)
	{
		push(reinterpret_cast<intptr_t>(_ptr));
	}
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value && sizeof(Type) == 4>::type push(Type _value)
	{
		// Push onto stack
		if (is_one_byte_value(_value)) {
			instruction8<OP_CODE::PUSH>(_passer._output, static_cast<int8_t>(_value));
		} // Push all 4 bytes
		else {
			instruction32<OP_CODE::PUSH>(_passer._output, *reinterpret_cast<int32_t*>(&_value));
		}
	}
	template<typename Type>
	typename std::enable_if<std::is_arithmetic<Type>::value && sizeof(Type) == 8>::type push(Type _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		push(static_cast<int32_t>(*reinterpret_cast<int64_t*>(&_value) >> 32));
		push(*reinterpret_cast<int32_t*>(&_value));
#else
		if (is_four_byte_value(_value)) {
			push(static_cast<int32_t>(_value));
		} else {
			instruction64<OP_CODE::MOVE, accumulator>(_passer._output, *reinterpret_cast<int64_t*>(&_value));
			instruction<OP_CODE::PUSH, accumulator>(_passer._output);
		}
#endif
	}
	template<typename Register, typename Offset_type>
	typename std::enable_if<utility::negation<std::is_void<Offset_type>::value>::value>::type push(register_offset<Register, Offset_type, true> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::LEA, accumulator, Register>(_passer._output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::LEA, accumulator, Register>(_passer._output, _offset.offset);
		}

		// Push address
		instruction<OP_CODE::PUSH, accumulator>(_passer._output);
	}
	template<typename Register, typename Offset_type>
	typename std::enable_if<utility::negation<std::is_void<Offset_type>::value>::value>::type push(register_offset<Register, Offset_type, false> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::PUSH, Register>(_passer._output, static_cast<int8_t>(_offset.offset));
		} else {
			// Push address
			instruction<OP_CODE::PUSH, Register>(_passer._output, _offset.offset);
		}
	}
	template<typename Register, bool Effective_address>
	void push(register_offset<Register, void, Effective_address> _offset)
	{
		instruction<OP_CODE::PUSH, Register>(_passer._output);
	}
	template<typename Register>
	void register_pass(reserved_parameter _value)
	{
	}
	template<typename Register>
	void register_pass(std::nullptr_t _value)
	{
		register_pass<Register>(intptr_t(0));
	}
	template<typename Register, typename Type>
	void register_pass(Type * _value)
	{
		register_pass<Register>(reinterpret_cast<intptr_t>(_value));
	}
	template<typename Destination, typename Source, typename Offset_type>
	typename std::enable_if<utility::negation<std::is_void<Offset_type>::value>::value>::type register_pass(register_offset<Source, Offset_type, true> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::LEA, Destination, Source>(_passer._output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::LEA, Destination, Source>(_passer._output, _offset.offset);
		}
	}
	template<typename Destination, typename Source, typename Offset_type>
	typename std::enable_if<utility::negation<std::is_void<Offset_type>::value>::value>::type register_pass(register_offset<Source, Offset_type, false> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::MOVE, Destination, Source>(_passer._output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::MOVE, Destination, Source>(_passer._output, _offset.offset);
		}
	}
	template<typename Destination, typename Source>
	void register_pass(register_offset<Source, void, false> _offset)
	{
		instruction<OP_CODE::MOVE, Destination, Source>(_passer._output);
	}
	template<typename Register>
	void register_pass(double _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		BIA_IMPLEMENTATION_ERROR;
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(_passer._output, *reinterpret_cast<int64_t*>(&_value));
		instruction<OP_CODE::MOVE_QUADWORD, Register, accumulator>(_passer._output);
#endif
	}
	template<typename Register, typename Type>
	typename std::enable_if<std::is_integral<Type>::value && sizeof(Type) == 4>::type register_pass(Type _value)
	{
		instruction32<OP_CODE::MOVE, Register>(_passer._output, *reinterpret_cast<int32_t*>(&_value));
	}
	template<typename Register, typename Type>
	typename std::enable_if<std::is_integral<Type>::value && sizeof(Type) == 8>::type register_pass(Type _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		BIA_IMPLEMENTATION_ERROR;
#else
		instruction64<OP_CODE::MOVE, Register>(_passer._output, *reinterpret_cast<int64_t*>(&_value));
#endif
	}
	template<typename... Arguments>
	std::tuple<pass_count_type, pass_count_type, pass_count_type> count_arguments(Arguments... _arguments)
	{
		auto _old_stack_offset = _passer._stack_offset;
		auto _old_pushed = _pushed;
		auto _old_integral_passed = _integral_passed;
		auto _old_floating_point_passed = _floating_point_passed;

		// Count parameters
		_count_only = true;
		pass(_arguments...);
		_count_only = false;

		std::swap(_old_stack_offset, _passer._stack_offset);
		std::swap(_old_pushed, _pushed);
		std::swap(_old_integral_passed, _integral_passed);
		std::swap(_old_floating_point_passed, _floating_point_passed);

		return std::make_tuple(_old_pushed - _pushed, _old_integral_passed - _integral_passed, _old_floating_point_passed - _floating_point_passed);
	}
};
#endif

}
}
}
