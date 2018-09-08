#pragma once

#include <type_traits>
#include <algorithm>

#include "config.hpp"
#include "exception.hpp"
#include "type_traits.hpp"
#include "output_stream.hpp"
#include "architecture.hpp"
#include "architecture_utils.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

struct reserved_parameter
{
};

#if (defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)) && (defined(BIA_COMPILER_MSVC) || defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
/**
 * @brief Passes parameters of a static function.
 *
 * Passes parameters of a static function.
 *
 * @warning If the function has at least two 32 Bit parameters, the first two parameters must be 32 Bit and the order of the rest does not matter. If the function has only one 32 Bit parameter, it must be the first one.
*/
class static_passer
{
public:
	typedef int32_t pass_count_type;

	static_passer(stream::output_stream & _output, pass_count_type & _pushed_global) noexcept : _output(_output), _pushed_global(_pushed_global)
	{
		_count_only = false;
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_COMPILER_MSVC)
		_passed = 0;
#else
		_integral_passed = 0;
		_floating_point_passed = 0;
#endif
	}
	virtual ~static_passer() = default;
	virtual void pop_all()
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		if (false) {
#elif defined(BIA_COMPILER_MSVC)
		_passed = std::max(_passed, 4) - 4;
		_pushed_global -= _passed;

		if (_passed > 0) {
#else
		auto _passed = std::max(_integral_passed, 6) - 6 + std::max(_floating_point_passed, 8) - 8;

		_pushed_global -= _passed;

		if (_passed > 0) {
#endif
			if (_passed * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(_output, static_cast<int8_t>(_passed * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(_output, static_cast<int32_t>(_passed * element_size));
			}
		}
	}
	template<typename... _Parameters>
	void pass_all(_Parameters... _parameters)
	{
		auto _old_pushed_global = _pushed_global;

#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_COMPILER_MSVC)
		auto _old_passed = _passed;
#else
		auto _old_integral_passed = _integral_passed;
		auto _old_floating_point_passed = _floating_point_passed;
#endif

		// Count parameters
		_count_only = true;
		pass(_parameters...);

		// Align stack
		auto _padding = align_stack(_pushed_global * element_size) - _pushed_global * element_size;

		if (_padding) {
			instruction8<OP_CODE::SUB, stack_pointer>(_output, _padding);
		}

		// Reset counters
		_pushed_global = _old_pushed_global;

#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_COMPILER_MSVC)
		_passed = _old_passed;
#else
		_integral_passed = _old_integral_passed;
		_floating_point_passed = _old_floating_point_passed;
#endif

		// Pass parameters
		_count_only = false;
		pass(_parameters...);

#if defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_MSVC)
		// Allocate shadow space
		if (_passed > 4) {
			instruction8<OP_CODE::SUB, stack_pointer>(_output, 4 * element_size);

			_pushed_global += 4;
			_passed += 4;
		}
#endif

		_passed += _padding / element_size;
		_pushed_global += _padding / element_size;
	}

protected:
	/** If true, nothing will be written to the output. */
	bool _count_only;
	/** The output stream. */
	stream::output_stream & _output;
	/** The global push count. Needed for stack alignment. */
	pass_count_type & _pushed_global;
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_COMPILER_MSVC)
	pass_count_type _passed;
#else
	pass_count_type _integral_passed;
	pass_count_type _floating_point_passed;
#endif


	void pass() noexcept
	{
	}
	template<typename _Ty, typename... _Args>
	void pass(_Ty _value, _Args... _args)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		if (sizeof(_Ty) <= element_size) {
			switch (_passed++) {
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
			_passed += 2;
			++_pushed_global;

			goto gt_push;
		}
#elif defined(BIA_COMPILER_MSVC)
		switch (_passed++) {
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
		switch (_integral_passed++) {
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

		// Pass rest
		pass(_args...);

		return;

	gt_push:;
		pass(_args...);

		if (!_count_only) {
			push(_value);
		}

		++_pushed_global;
	}
	template<typename... _Args>
	void pass(double _value, _Args... _args)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		_passed += 2;
		++_pushed_global;

		goto gt_push;
#elif defined(BIA_COMPILER_MSVC)
		switch (_passed++) {
		case 0:
			register_pass<xmm0>(_value);

			break;
		case 1:
			register_pass<xmm1>(_value);

			break;
		case 2:
			register_pass<xmm2>(_value);

			break;
		case 3:
			register_pass<xmm3>(_value);

			break;
		default:
			goto gt_push;
		}
#else
		switch (_floating_point_passed++) {
		case 0:
			register_pass<xmm0>(_value);

			break;
		case 1:
			register_pass<xmm1>(_value);

			break;
		case 2:
			register_pass<xmm2>(_value);

			break;
		case 3:
			register_pass<xmm3>(_value);

			break;
		case 4:
			register_pass<xmm4>(_value);

			break;
		case 5:
			register_pass<xmm5>(_value);

			break;
		case 6:
			register_pass<xmm6>(_value);

			break;
		case 7:
			register_pass<xmm7>(_value);

			break;
		default:
			goto gt_push;
	}
#endif

		// Pass rest
		pass(_args...);

		return;

	gt_push:;
		pass(_args...);
		push(_value);

		++_pushed_global;
}
	void push(reserved_parameter _value)
	{
	}
	void push(std::nullptr_t _value)
	{
		push(intptr_t(0));
	}
	template<typename _Ty>
	void push(_Ty * _ptr)
	{
		push(reinterpret_cast<intptr_t>(_ptr));
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 4>::type push(_Ty _value)
	{
		// Push onto stack
		if (is_one_byte_value(_value)) {
			instruction8<OP_CODE::PUSH>(_output, static_cast<int8_t>(_value));
		} // Push all 4 bytes
		else {
			instruction32<OP_CODE::PUSH>(_output, *reinterpret_cast<int32_t*>(&_value));
		}
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8>::type push(_Ty _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		push(static_cast<int32_t>(*reinterpret_cast<int64_t*>(&_value) >> 32));
		push(*reinterpret_cast<int32_t*>(&_value));
#else
		if (is_four_byte_value(_value)) {
			push(static_cast<int32_t>(_value));
		} else {
			instruction64<OP_CODE::MOVE, accumulator>(_output, *reinterpret_cast<int64_t*>(&_value));
			instruction<OP_CODE::PUSH, accumulator>(_output);
	}
#endif
}
	template<typename _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type push(register_offset<_Register, _Offset, true> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::LEA, accumulator, _Register>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::LEA, accumulator, _Register>(_output, _offset.offset);
		}

		// Push address
		instruction<OP_CODE::PUSH, accumulator>(_output);
	}
	template<typename _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type push(register_offset<_Register, _Offset, false> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::PUSH, _Register>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			// Push address
			instruction<OP_CODE::PUSH, _Register>(_output, _offset.offset);
		}
	}
	template<typename _Register, bool _Effective_address>
	void push(register_offset<_Register, void, _Effective_address> _offset)
	{
		instruction<OP_CODE::PUSH, _Register>(_output);
	}
	template<typename _Register>
	void register_pass(reserved_parameter _value)
	{
	}
	template<typename _Register>
	void register_pass(std::nullptr_t _value)
	{
		register_pass<_Register>(intptr_t(0));
	}
	template<typename _Register, typename _Ty>
	void register_pass(_Ty * _value)
	{
		register_pass<_Register>(reinterpret_cast<intptr_t>(_value));
	}
	template<typename _Dest, typename _Src, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type register_pass(register_offset<_Src, _Offset, true> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::LEA, _Dest, _Src>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::LEA, _Dest, _Src>(_output, _offset.offset);
		}
	}
	template<typename _Dest, typename _Src, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type register_pass(register_offset<_Src, _Offset, false> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::MOVE, _Dest, _Src>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::MOVE, _Dest, _Src>(_output, _offset.offset);
		}
	}
	template<typename _Dest, typename _Src>
	void register_pass(register_offset<_Src, void, false> _offset)
	{
		instruction<OP_CODE::MOVE, _Dest, _Src>(_output);
	}
	template<typename _Register>
	void register_pass(double _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		BIA_IMPLEMENTATION_ERROR;
#elif defined(BIA_ARCHITECTURE_X86_64)
		instruction64<OP_CODE::MOVE, accumulator>(_output, *reinterpret_cast<int64_t*>(&_value));
		instruction<OP_CODE::MOVE_QUADWORD, _Register, accumulator>(_output);
#endif
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_integral<_Ty>::value && sizeof(_Ty) == 4>::type register_pass(_Ty _value)
	{
		instruction32<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int32_t*>(&_value));
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_integral<_Ty>::value && sizeof(_Ty) == 8>::type register_pass(_Ty _value)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		BIA_IMPLEMENTATION_ERROR;
#else
		instruction64<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int64_t*>(&_value));
#endif
	}
};


/**
 * @brief Passes parameters of a member function.
 *
 * Passes parameters of a member function.
*/
typedef static_passer member_passer;

class varg_member_passer : protected static_passer
{
public:
	varg_member_passer(stream::output_stream & _output, pass_count_type & _pushed_global) noexcept : static_passer(_output, _pushed_global)
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		// Push everything onto the stack
		_passed = 2;
#elif defined(BIA_COMPILER_MSVC)
		// Reserve 4 registers because of framework::member::execute_count() and framework::member::execute_format()
		_passed = 4;
#else
		// Reserve 4 registers because of framework::member::execute_count() and framework::member::execute_format() and with 2 more the vargs are going to be pushed onto the stack
		_integral_passed = 6;
		_floating_point_passed = 8;
#endif
	}
	void pop_all()
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		_passed = std::max(_passed, 2) - 2;
		_pushed_global -= _passed;

		if (_passed > 0) {
			if (_passed * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(_output, static_cast<int8_t>(_passed * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(_output, static_cast<int32_t>(_passed * element_size));
			}
		}
#else
		static_passer::pop_all();
#endif
		}
	template<typename _Ty>
	void pass_varg(_Ty _value)
	{
		pass(_value);
	}
	template<typename _First, typename _Second, typename _Third, typename _Fourth>
	void pass_all(_First _first, _Second _second, _Third _third, _Fourth _fourth)
	{
		static_assert(!(std::is_floating_point<_First>::value || std::is_floating_point<_Second>::value || std::is_floating_point<_Third>::value || std::is_floating_point<_Fourth>::value), "All parameters must be of integral types.");

#if defined(BIA_ARCHITECTURE_X86_32)
		return static_passer::pass_all(_first, _second, _third, _fourth);
#elif defined(BIA_COMPILER_MSVC)
		auto _tmp = _passed;

		_passed = 0;

		pass(_first, _second, _third, _fourth);

		_passed = _tmp;

		static_passer::pass_all();
#else
		auto _tmp = _integral_passed;

		_integral_passed = 0;

		pass(_first, _second, _third, _fourth);

		_integral_passed = _tmp;

		static_passer::pass_all();

		// All floating point values are pushed onto the stack (mov al, 0)
		_output.write_all(0xb0_8, 0x00_8);
#endif
	}
	pass_count_type compensatory_pushes()
	{
		return (align_stack(_pushed_global * element_size) - _pushed_global * element_size) / element_size;
	}
	};
#endif

}
}
}
