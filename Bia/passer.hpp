#pragma once

#include <type_traits>

#include "config.hpp"
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

#if defined(BIA_ARCHITECTURE_X86_32) && (defined (BIA_COMPILER_MSVC) || defined(BIA_COMPILER_GNU) || defined(BIA_COMPILER_CLANG))
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

	static_passer(stream::output_stream & _output) noexcept : _output(_output)
	{
		_passed = 0;
	}
	virtual ~static_passer() = default;
	virtual void pop_all()
	{
	}
	void pass_all() noexcept
	{
	}
	template<typename _First>
	void pass_all(_First _first)
	{
		// Move to ecx
		register_pass<ecx>(0, _first);
	}
	template<typename _First, typename _Second, typename... _Parameters>
	void pass_all(_First _first, _Second _second, _Parameters ... _parameters)
	{
		// Push to stack
		pass(_parameters...);

		// Move first to ecx
		auto _tmp = _passed;

		register_pass<ecx>(0, _first);

		// Move second to edx
		register_pass<edx>(_passed - _tmp, _second);
	}

protected:
	stream::output_stream & _output;
	pass_count_type _passed;


	void pass() noexcept
	{
	}
	template<typename _Ty, typename... _Args>
	void pass(_Ty _value, _Args... _args)
	{
		pass(_args...);
		pass(_value);
	}
	void pass(std::nullptr_t)
	{
		pass(intptr_t(0));
	}
	void pass(reserved_parameter _value)
	{
		pass(0);
	}
	template<typename _Ty>
	void pass(_Ty * _ptr)
	{
		pass(reinterpret_cast<intptr_t>(_ptr));
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 4>::type pass(_Ty _value)
	{
		// Push onto stack
		if (is_one_byte_value(_value)) {
			instruction8<OP_CODE::PUSH>(_output, static_cast<int8_t>(_value));
		} // Push all 4 bytes
		else {
			instruction32<OP_CODE::PUSH>(_output, *reinterpret_cast<int32_t*>(&_value));
		}

		++_passed;
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8>::type pass(_Ty _value)
	{
		pass(static_cast<int32_t>(*reinterpret_cast<int64_t*>(&_value) >> 32));
		pass(*reinterpret_cast<int32_t*>(&_value));

		_passed += 2;
	}
	template<typename _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type pass(register_offset<_Register, _Offset, true> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::LEA, accumulator, _Register>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::LEA, accumulator, _Register>(_output, _offset.offset);
		}

		// Push address
		instruction<OP_CODE::PUSH, accumulator>(_output);

		++_passed;
	}
	template<typename _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type pass(register_offset<_Register, _Offset, false> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::PUSH, _Register>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			// Push address
			instruction<OP_CODE::PUSH, _Register>(_output, _offset.offset);
		}

		++_passed;
	}
	template<typename _Register>
	void pass(register_offset<_Register, void, false> _offset)
	{
		instruction<OP_CODE::PUSH, _Register>(_output);

		++_passed;
	}
	template<typename _Register>
	void register_pass(pass_count_type _left_passed, reserved_parameter _value)
	{
		if ((std::is_same<_Register, ecx>::value && !_left_passed) || (std::is_same<_Register, edx>::value && _left_passed == 1)) {
			++_passed;
		} // Just push
		else {
			pass(_value);
		}
	}
	template<typename _Register>
	void register_pass(pass_count_type _left_passed, std::nullptr_t _value)
	{
		if ((std::is_same<_Register, ecx>::value && !_left_passed) || (std::is_same<_Register, edx>::value && _left_passed == 1)) {
			instruction32<OP_CODE::MOVE, _Register>(_output, 0);

			++_passed;
		} // Just push
		else {
			pass(nullptr);
		}
	}
	template<typename _Register, typename _Ty>
	void register_pass(pass_count_type _left_passed, _Ty * _value)
	{
		register_pass<_Register>(_left_passed, reinterpret_cast<intptr_t>(_value));
	}
	template<typename _Dest, typename _Src, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type register_pass(pass_count_type _left_passed, register_offset<_Src, _Offset, true> _offset)
	{
		if ((std::is_same<_Dest, ecx>::value && !_left_passed) || (std::is_same<_Dest, edx>::value && _left_passed == 1)) {
			// Save 3 bytes
			if (is_one_byte_value(_offset.offset)) {
				instruction<OP_CODE::LEA, _Dest, _Src>(_output, static_cast<int8_t>(_offset.offset));
			} else {
				instruction<OP_CODE::LEA, _Dest, _Src>(_output, _offset.offset);
			}

			++_passed;
		} // Just push
		else {
			pass(_offset);
		}
	}
	template<typename _Dest, typename _Src, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type register_pass(pass_count_type _left_passed, register_offset<_Src, _Offset, false> _offset)
	{
		if ((std::is_same<_Dest, ecx>::value && !_left_passed) || (std::is_same<_Dest, edx>::value && _left_passed == 1)) {
			// Save 3 bytes
			if (is_one_byte_value(_offset.offset)) {
				instruction<OP_CODE::MOVE, _Dest, _Src>(_output, static_cast<int8_t>(_offset.offset));
			} else {
				instruction<OP_CODE::MOVE, _Dest, _Src>(_output, _offset.offset);
			}

			++_passed;
		} // Just push
		else {
			pass(_offset);
		}
	}
	template<typename _Dest, typename _Src>
	void register_pass(pass_count_type _left_passed, register_offset<_Src, void, false> _offset)
	{
		if ((std::is_same<_Dest, ecx>::value && !_left_passed) || (std::is_same<_Dest, edx>::value && _left_passed == 1)) {
			instruction<OP_CODE::MOVE, _Dest, _Src>(_output);

			++_passed;
		} // Just push
		else {
			pass(_offset);
		}
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 4>::type register_pass(pass_count_type _left_passed, _Ty _value)
	{
		if ((std::is_same<_Register, ecx>::value && !_left_passed) || (std::is_same<_Register, edx>::value && _left_passed == 1)) {
			instruction32<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int32_t*>(&_value));

			++_passed;
		} // Just push
		else {
			pass(_value);
		}
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8>::type register_pass(pass_count_type _left_passed, _Ty _value)
	{
		// Just push
		pass(_value);
	}
};


/**
 * @brief Passes parameters of a member function.
 *
 * Passes parameters of a member function.
 *
 * @warning If the function has at least one 32 Bit parameter, the first parameter must be 32 Bit and the order of the rest does not matter.
*/
class member_passer : public static_passer
{
public:
	member_passer(stream::output_stream & _output) noexcept : static_passer(_output)
	{
	}
};

class varg_member_passer : protected static_passer
{
public:
	varg_member_passer(stream::output_stream & _output) noexcept : static_passer(_output)
	{
	}

	virtual void pop_all() override
	{
		if (_passed > 0) {
			if (_passed * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(_output, static_cast<int8_t>(_passed * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(_output, static_cast<int32_t>(_passed * element_size));
			}
		}
	}
	template<typename _Ty>
	void pass_varg(_Ty _value)
	{
		pass(_value);
	}
	template<typename _First, typename _Second, typename _Third, typename _Fourth>
	void pass_all(_First _first, _Second _second, _Third _third, _Fourth _fourth)
	{
#if defined(BIA_COMPILER_MSVC)
		// Push to stack
		pass(_first, _second, _third, _fourth);
#else
		// Push to stack
		pass(_second, _third, _fourth);

		// Move first to ecx because it is needed in the toolset to calculate the function address
		register_pass<ecx>(0, _first);
		instruction<OP_CODE::PUSH, ecx>(_output);
#endif
	}
};
#elif defined(BIA_ARCHITECTURE_X86_64) && defined(BIA_COMPILER_GNU)
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

	static_passer(stream::output_stream & _output) noexcept : _output(_output)
	{
		_integral_passed = 0;
		_floating_point_passed = 0;
	}
	virtual ~static_passer() = default;
	virtual void pop_all()
	{
		auto _pushed = std::max(_integral_passed, 6) - 6 + std::max(_floating_point_passed, 8) - 8;

		if (_pushed > 0) {
			if (_pushed * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(_output, static_cast<int8_t>(_pushed * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(_output, static_cast<int32_t>(_pushed * element_size));
			}
		}
	}
	template<typename... _Parameters>
	void pass_all(_Parameters ... _parameters)
	{
		pass(_parameters...);
	}

protected:
	stream::output_stream & _output;
	pass_count_type _integral_passed;
	pass_count_type _floating_point_passed;


	void pass() noexcept
	{
	}
	template<typename _Ty, typename... _Args>
	typename std::enable_if<utility::negation<std::is_floating_point<_Ty>::value>::value>::type pass(_Ty _value, _Args... _args)
	{
		switch (_integral_passed) {
		case 0:
			register_pass<rdi>(_value);

			break;
		case 1:
			register_pass<rsi>(_value);

			break;
		case 2:
			register_pass<rdx>(_value);

			break;
		case 3:
			register_pass<rcx>(_value);

			break;
		case 4:
			register_pass<r8>(_value);

			break;
		case 5:
			register_pass<r9>(_value);

			break;
		default:
			push(_value);

			break;
		}

		++_integral_passed;

		// Pass rest
		pass(_args...);
	}
	template<typename _Ty, typename... _Args>
	typename std::enable_if<std::is_floating_point<_Ty>::value>::type pass(_Ty _value, _Args... _args)
	{
		switch (_floating_point_passed) {
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
			push(_value);

			break;
		}

		++_floating_point_passed;

		// Pass rest
		pass(_args...);
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
		if (is_four_byte_value(_value)) {
			push(static_cast<int32_t>(_value));
		} else {
			instruction64<OP_CODE::MOVE, accumulator>(_output, *reinterpret_cast<int64_t*>(&_value));
			instruction<OP_CODE::PUSH, accumulator>(_output);
		}
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
		instruction64<OP_CODE::MOVE, accumulator>(_output, *reinterpret_cast<int64_t*>(&_value));
		instruction<OP_CODE::MOVE_QUADWORD, _Register, accumulator>(_output);
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_integral<_Ty>::value && sizeof(_Ty) == 4>::type register_pass(_Ty _value)
	{
		instruction32<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int32_t*>(&_value));
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8>::type register_pass(_Ty _value)
	{
		instruction64<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int64_t*>(&_value));
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
	varg_member_passer(stream::output_stream & _output) noexcept : static_passer(_output)
	{
		// Reserve 4 registers because of framework::member::execute_count() and framework::member::execute_format() and with 2 more the vargs are going to be pushed onto the stack
		_integral_passed = 6;
		_floating_point_passed = 8;
	}
	void pop_all()
	{
		static_passer::pop_all();
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

		auto _tmp = _integral_passed;

		_integral_passed = 0;

		pass(_first, _second, _third, _fourth);

		_integral_passed = _tmp;

		// All floating point values are pushed onto the stack (mov al, 0)
		_output.write_all(0xb0_8, 0x00_8);
	}
};
#elif defined(BIA_ARCHITECTURE_X86_64) && defined (BIA_COMPILER_MSVC)
/**
 * @brief Passes parameters of a static function.
 *
 * Passes parameters of a static function.
*/
class static_passer
{
public:
	typedef int32_t pass_count_type;

	static_passer(stream::output_stream & _output) noexcept : _output(_output)
	{
		_passed = 0;
	}
	virtual ~static_passer() = default;
	virtual void pop_all()
	{
	}
	void pass_all() noexcept
	{
	}
	template<typename _First>
	void pass_all(_First _first)
	{
		register_pass<arg_destination<0, _First>::register_type>(0, _first);
	}
	template<typename _First, typename _Second>
	void pass_all(_First _first, _Second _second)
	{
		// Move first to registers
		auto _tmp = _passed;

		register_pass<arg_destination<0, _First>::register_type>(0, _first);
		register_pass<arg_destination<1, _Second>::register_type>(_passed - _tmp, _second);
	}
	template<typename _First, typename _Second, typename _Third>
	void pass_all(_First _first, _Second _second, _Third _third)
	{
		// Move first to registers
		auto _tmp = _passed;

		register_pass<arg_destination<0, _First>::register_type>(0, _first);
		register_pass<arg_destination<1, _Second>::register_type>(_passed - _tmp, _second);
		register_pass<arg_destination<2, _Third>::register_type>(_passed - _tmp, _third);
	}
	template<typename _First, typename _Second, typename _Third, typename _Fourth, typename... _Parameters>
	void pass_all(_First _first, _Second _second, _Third _third, _Fourth _fourth, _Parameters ... _parameters)
	{
		// Push to stack
		pass(_parameters...);

		// Move first to registers
		auto _tmp = _passed;

		register_pass<arg_destination<0, _First>::register_type>(0, _first);
		register_pass<arg_destination<1, _Second>::register_type>(_passed - _tmp, _second);
		register_pass<arg_destination<2, _Third>::register_type>(_passed - _tmp, _third);
		register_pass<arg_destination<3, _Fourth>::register_type>(_passed - _tmp, _fourth);
	}

protected:
	template<int _Index, typename _Ty>
	struct arg_destination;

	template<typename _Ty>
	struct arg_destination<0, _Ty>
	{
		typedef typename std::conditional<std::is_same<_Ty, double>::value, xmm0, rcx>::type register_type;
	};

	template<typename _Ty>
	struct arg_destination<1, _Ty>
	{
		typedef typename std::conditional<std::is_same<_Ty, double>::value, xmm1, rdx>::type register_type;
	};

	template<typename _Ty>
	struct arg_destination<2, _Ty>
	{
		typedef typename std::conditional<std::is_same<_Ty, double>::value, xmm2, r8>::type register_type;
	};

	template<typename _Ty>
	struct arg_destination<3, _Ty>
	{
		typedef typename std::conditional<std::is_same<_Ty, double>::value, xmm3, r9>::type register_type;
	};


	stream::output_stream & _output;
	pass_count_type _passed;


	void pass() noexcept
	{
	}
	template<typename _Ty, typename... _Args>
	void pass(_Ty _value, _Args... _args)
	{
		pass(_args...);
		pass(_value);
	}
	void pass(std::nullptr_t)
	{
		pass(intptr_t(0));
	}
	void pass(reserved_parameter _value)
	{
		pass(0);
	}
	template<typename _Ty>
	void pass(_Ty * _ptr)
	{
		pass(reinterpret_cast<intptr_t>(_ptr));
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 4>::type pass(_Ty _value)
	{
		// Push onto stack
		if (is_one_byte_value(_value)) {
			instruction8<OP_CODE::PUSH>(_output, static_cast<int8_t>(_value));
		} // Push all 4 bytes
		else {
			instruction32<OP_CODE::PUSH>(_output, *reinterpret_cast<int32_t*>(&_value));
		}

		++_passed;
	}
	template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8>::type pass(_Ty _value)
	{
		if (is_four_byte_value(_value)) {
			pass(static_cast<int32_t>(_value));
		} else {
			instruction64<OP_CODE::MOVE, accumulator>(_output, *reinterpret_cast<int64_t*>(&_value));
			instruction<OP_CODE::PUSH, accumulator>(_output);

			++_passed;
		}
	}
	template<typename _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type pass(register_offset<_Register, _Offset, true> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::LEA, accumulator, _Register>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			instruction<OP_CODE::LEA, accumulator, _Register>(_output, _offset.offset);
		}

		// Push address
		instruction<OP_CODE::PUSH, accumulator>(_output);

		++_passed;
	}
	template<typename _Register, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type pass(register_offset<_Register, _Offset, false> _offset)
	{
		// Save 3 bytes
		if (is_one_byte_value(_offset.offset)) {
			instruction<OP_CODE::PUSH, _Register>(_output, static_cast<int8_t>(_offset.offset));
		} else {
			// Push address
			instruction<OP_CODE::PUSH, _Register>(_output, _offset.offset);
		}

		++_passed;
	}
	template<typename _Register>
	void pass(register_offset<_Register, void, false> _offset)
	{
		instruction<OP_CODE::PUSH, _Register>(_output);

		++_passed;
	}
	template<typename _Register>
	void register_pass(pass_count_type _left_passed, reserved_parameter _value)
	{
		if (valid_register_pass<_Register>(_left_passed)) {
			++_passed;
		} // Just push
		else {
			pass(_value);
		}
	}
	template<typename _Register>
	void register_pass(pass_count_type _left_passed, std::nullptr_t _value)
	{
		if (valid_register_pass<_Register>(_left_passed)) {
			instruction32<OP_CODE::MOVE, _Register>(_output, 0);

			++_passed;
		} // Just push
		else {
			pass(nullptr);
		}
	}
	template<typename _Register, typename _Ty>
	typename void register_pass(pass_count_type _left_passed, _Ty * _value)
	{
		register_pass<_Register>(_left_passed, reinterpret_cast<intptr_t>(_value));
	}
	template<typename _Dest, typename _Src, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type register_pass(pass_count_type _left_passed, register_offset<_Src, _Offset, true> _offset)
	{
		if (valid_register_pass<_Dest>(_left_passed)) {
			// Save 3 bytes
			if (is_one_byte_value(_offset.offset)) {
				instruction<OP_CODE::LEA, _Dest, _Src>(_output, static_cast<int8_t>(_offset.offset));
			} else {
				instruction<OP_CODE::LEA, _Dest, _Src>(_output, _offset.offset);
			}

			++_passed;
		} // Just push
		else {
			pass(_offset);
		}
	}
	template<typename _Dest, typename _Src, typename _Offset>
	typename std::enable_if<utility::negation<std::is_void<_Offset>::value>::value>::type register_pass(pass_count_type _left_passed, register_offset<_Src, _Offset, false> _offset)
	{
		if (valid_register_pass<_Dest>(_left_passed)) {
			// Save 3 bytes
			if (is_one_byte_value(_offset.offset)) {
				instruction<OP_CODE::MOVE, _Dest, _Src>(_output, static_cast<int8_t>(_offset.offset));
			} else {
				instruction<OP_CODE::MOVE, _Dest, _Src>(_output, _offset.offset);
			}

			++_passed;
		} // Just push
		else {
			pass(_offset);
		}
	}
	template<typename _Dest, typename _Src>
	void register_pass(pass_count_type _left_passed, register_offset<_Src, void, false> _offset)
	{
		if (valid_register_pass<_Dest>(_left_passed)) {
			instruction<OP_CODE::MOVE, _Dest, _Src>(_output);

			++_passed;
		} // Just push
		else {
			pass(_offset);
		}
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 4>::type register_pass(pass_count_type _left_passed, _Ty _value)
	{
		if (valid_register_pass<_Register>(_left_passed)) {
			instruction32<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int32_t*>(&_value));

			++_passed;
		} // Just push
		else {
			pass(_value);
		}
	}
	template<typename _Register>
	void register_pass(pass_count_type _left_passed, double _value)
	{
		if (valid_register_pass<_Register>(_left_passed)) {
			instruction64<OP_CODE::MOVE, accumulator>(_output, *reinterpret_cast<int64_t*>(&_value));
			instruction<OP_CODE::MOVE_QUADWORD, _Register, accumulator>(_output);

			++_passed;
		} // Just push
		else {
			pass(_value);
		}
	}
	template<typename _Register, typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 8>::type register_pass(pass_count_type _left_passed, _Ty _value)
	{
		if (valid_register_pass<_Register>(_left_passed)) {
			instruction64<OP_CODE::MOVE, _Register>(_output, *reinterpret_cast<int64_t*>(&_value));

			++_passed;
		} // Just push
		else {
			pass(_value);
		}
	}
	template<typename _Register>
	bool valid_register_pass(pass_count_type _left_passed)
	{
		return true;
	}
};


/**
 * @brief Passes parameters of a member function.
 *
 * Passes parameters of a member function.
 *
 * @warning If the function has at least one 32 Bit parameter, the first parameter must be 32 Bit and the order of the rest does not matter.
*/
class member_passer : public static_passer
{
public:
	member_passer(stream::output_stream & _output) noexcept : static_passer(_output)
	{
	}
};

class varg_member_passer : protected static_passer
{
public:
	varg_member_passer(stream::output_stream & _output) noexcept : static_passer(_output)
	{
	}

	virtual void pop_all() override
	{
		_passed -= 4;

		if (_passed > 0) {
			if (_passed * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(_output, static_cast<int8_t>(_passed * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(_output, static_cast<int32_t>(_passed * element_size));
			}
		}
	}
	template<typename _Ty>
	void pass_varg(_Ty _value)
	{
		pass(_value);
	}
	template<typename _First, typename _Second, typename _Third, typename _Fourth>
	void pass_all(_First _first, _Second _second, _Third _third, _Fourth _fourth)
	{
		static_passer::pass_all(_first, _second, _third, _fourth);
	}
};
#endif

}
}
}
