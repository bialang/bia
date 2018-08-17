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
		/*_passed -= 2;

		if (_passed > 0) {
			if (_passed * element_size <= std::numeric_limits<int8_t>::max()) {
				instruction8<OP_CODE::ADD, stack_pointer>(_output, static_cast<int8_t>(_passed * element_size));
			} else {
				instruction32<OP_CODE::ADD, stack_pointer>(_output, static_cast<int32_t>(_passed * element_size));
			}
		}*/
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

private:
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
	template<typename _Ty>
	void pass(_Ty * _ptr)
	{
		pass(reinterpret_cast<intptr_t>(_ptr));
	}
	/*template<typename _Ty>
	typename std::enable_if<std::is_arithmetic<_Ty>::value && sizeof(_Ty) == 1, pass_count_type>::type pass(_Ty _value)
	{
		instruction8<OP_CODE::PUSH>(_output, *reinterpret_cast<int8_t*>(&_value));

		return 1;
	}*/
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
	void register_pass(pass_count_type _left_passed, std::nullptr_t)
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
	typename void register_pass(pass_count_type _left_passed, _Ty * _value)
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
#endif

}
}
}