#pragma once

#include <cstdint>
#include <type_traits>

#include "config.hpp"
#include "architecture_utils.hpp"
#include "output_stream.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
template<OP_CODE _Op_code>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(_Op_code == OP_CODE::RETURN_NEAR, "This opcode is not supported.");

	switch (_Op_code) {
	case OP_CODE::RETURN_NEAR:
		return _output.write_all(0xc3_8);
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE _Op_code, typename _Register>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::POP || _Op_code == OP_CODE::CALL, "This opcode is not supported.");

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(_Register::size() == 32, "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert(_Register::size() == 64, "Register is not supported.");
#endif

	switch (_Op_code) {
	case OP_CODE::PUSH:
		return _output.write_all(static_cast<uint8_t>(0x50 | _Register::value()));
	case OP_CODE::POP:
		return _output.write_all(static_cast<uint8_t>(0x58 | _Register::value()));
	case OP_CODE::CALL:
		return _output.write_all(0xff_8, static_cast<uint8_t>(0320 | _Register::value()));
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE _Op_code, typename _Register, typename _Offset>
inline size_t instruction(stream::output_stream & _output, _Offset _offset)
{
	static_assert(_Op_code == OP_CODE::PUSH, "This opcode is not supported.");
	static_assert(std::is_same<_Offset, int8_t>::value || std::is_same<_Offset, int32_t>::value, "Offset must be int8_t or int32_t.");

	switch (_Op_code) {
	case OP_CODE::PUSH:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::PUSH && _Register::size() != 32), "Register is not supported.");
		constexpr auto _special_register = std::is_same<_Register, esp>::value;
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::PUSH && _Register::size() != 64), "Register is not supported.");
		constexpr auto _special_register = std::is_same<_Register, rsp>::value;
#endif

		if (_special_register) {
			// 8 bit offset
			if (std::is_same<int8_t, _Offset>::value) {
				return _output.write_all(0xff_8, static_cast<uint8_t>(0160 | _Register::value()), 0x24_8, _offset);
			}

			// 32 bit offset
			return _output.write_all(0xff_8, static_cast<uint8_t>(0260 | _Register::value()), 0x24_8, _offset);
		}

		// 8 bit offset
		if (std::is_same<int8_t, _Offset>::value) {
			return _output.write_all(0xff_8, static_cast<uint8_t>(0160 | _Register::value()), _offset);
		}

		// 32 bit offset
		return _output.write_all(0xff_8, static_cast<uint8_t>(0260 | _Register::value()), _offset);
	}
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE _Op_code, typename _Dest, typename _Src>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(_Op_code == OP_CODE::MOVE || _Op_code == OP_CODE::XOR, "This opcode is not supported.");
	static_assert(_Dest::size() == _Src::size(), "Registers must be of the same size.");

	switch (_Op_code) {
	case OP_CODE::MOVE:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::MOVE && _Dest::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::MOVE && _Dest::size() != 32 && _Dest::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Dest::size() == 64) {
			return _output.write_all(0x48_8, 0x89_8, static_cast<uint8_t>(0300 | _Src::value() << 3 | _Dest::value()));
		}
#endif

		return _output.write_all(0x89_8, static_cast<uint8_t>(0300 | _Src::value() << 3 | _Dest::value()));
	}
	case OP_CODE::XOR:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::XOR && _Dest::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::XOR && _Dest::size() != 32 && _Dest::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Dest::size() == 64) {
			return _output.write_all(0x48_8, 0x31_8, static_cast<uint8_t>(0300 | _Src::value() << 3 | _Dest::value()));
		}
#endif

		return _output.write_all(0x31_8, static_cast<uint8_t>(0300 | _Src::value() << 3 | _Dest::value()));
	}
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE _Op_code, typename _Dest, typename _Src, typename _Src_offset>
inline size_t instruction(stream::output_stream & _output, _Src_offset _offset)
{
	static_assert(_Op_code == OP_CODE::MOVE || _Op_code == OP_CODE::LEA, "This opcode is not supported.");
	static_assert(std::is_same<_Src_offset, int8_t>::value || std::is_same<_Src_offset, int32_t>::value, "Offset must be int8_t or int32_t.");

	int8_t _op_code = 0;

	switch (_Op_code) {
	case OP_CODE::MOVE:
		_op_code = 0x8b;

		break;
	case OP_CODE::LEA:
		_op_code = 0x8d;

		break;
	default:
		BIA_IMPLEMENTATION_ERROR;
	}

	constexpr auto _mode = std::is_same<_Src_offset, int8_t>::value ? 0100 : 0200;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(_Src::size() == 32 && _Dest::size() == 32, "Register is not supported.");

	// Add SIB byte for stack pointer register
	constexpr auto _special_register = std::is_same<_Src, esp>::value;
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert((_Dest::size() == 32 || _Dest::size() == 64) && _Src::size() == 64, "Register is not supported.");

	// Add SIB byte for stack pointer register
	constexpr auto _special_register = std::is_same<_Src, esp>::value || std::is_same<_Src, rsp>::value;

	// Write prefix for 64 bit register
	if (_Dest::size() == 64) {
		if (_special_register) {
			return _output.write_all(0x48_8, _op_code, static_cast<uint8_t>(_mode | _Dest::value() << 3 | _Src::value()), 0x24_8, _offset);
		}

		return _output.write_all(0x48_8, _op_code, static_cast<uint8_t>(_mode | _Dest::value() << 3 | _Src::value()), _offset);
	}
#endif

	if (_special_register) {
		return _output.write_all(_op_code, static_cast<uint8_t>(_mode | _Dest::value() << 3 | _Src::value()), 0x24_8, _offset);
	}

	return _output.write_all(_op_code, static_cast<uint8_t>(_mode | _Dest::value() << 3 | _Src::value()), _offset);
}



template<OP_CODE _Op_code, typename _Register>
inline size_t instruction8(stream::output_stream & _output, int8_t _value)
{
	static_assert(_Op_code == OP_CODE::ADD || _Op_code == OP_CODE::SUB, "This opcode is not supported.");

	switch (_Op_code) {
	case OP_CODE::ADD:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::ADD && _Register::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::ADD && _Register::size() != 32 && _Register::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Register::size() == 64) {
			return _output.write_all(0x48_8, 0x83_8, static_cast<uint8_t>(0300 | _Register::value()), _value);
		}
#endif

		return _output.write_all(0x83_8, static_cast<uint8_t>(0300 | _Register::value()), _value);
	}
	case OP_CODE::SUB:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::SUB && _Register::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::SUB && _Register::size() != 32 && _Register::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Register::size() == 64) {
			return _output.write_all(0x48_8, 0x83_8, static_cast<uint8_t>(0350 | _Register::value()), _value);
		}
#endif

		return _output.write_all(0x83_8, static_cast<uint8_t>(0350 | _Register::value()), _value);
	}
	}

	BIA_IMPLEMENTATION_ERROR;
	}

template<OP_CODE _Op_code, typename _Register>
inline size_t instruction32(stream::output_stream & _output, int32_t _value)
{
	static_assert(_Op_code == OP_CODE::MOVE || _Op_code == OP_CODE::ADD || _Op_code == OP_CODE::SUB, "This opcode is not supported.");

	switch (_Op_code) {
	case OP_CODE::MOVE:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::MOVE && _Register::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::MOVE && _Register::size() != 32 && _Register::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Register::size() == 64) {
			return _output.write_all(0x48_8, 0xc7_8, static_cast<uint8_t>(0300 | _Register::value()), _value);
		}
#endif

		return _output.write_all(static_cast<uint8_t>(0xb8 | _Register::value()), _value);
	}
	case OP_CODE::ADD:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::ADD && _Register::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::ADD && _Register::size() != 32 && _Register::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Register::size() == 64) {
			return _output.write_all(0x48_8, 0x81_8, static_cast<uint8_t>(0300 | _Register::value()), _value);
		}
#endif

		// Special opcode for EAX
		if (std::is_same<_Register, eax>::value) {
			return _output.write_all(0x05_8, _value);
		}

		return _output.write_all(0x81_8, static_cast<uint8_t>(0300 | _Register::value()), _value);
	}
	case OP_CODE::SUB:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(!(_Op_code == OP_CODE::SUB && _Register::size() != 32), "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert(!(_Op_code == OP_CODE::SUB && _Register::size() != 32 && _Register::size() != 64), "Register is not supported.");

		// Write prefix for 64 bit register
		if (_Register::size() == 64) {
			return _output.write_all(0x48_8, 0x81_8, static_cast<uint8_t>(0350 | _Register::value()), _value);
		}
#endif

		// Special opcode for EAX
		if (std::is_same<_Register, eax>::value) {
			return _output.write_all(0x2d_8, static_cast<uint32_t>(_value));
		}

		return _output.write_all(0x81_8, static_cast<uint8_t>(0350 | _Register::value()), _value);
	}
	}

	BIA_IMPLEMENTATION_ERROR;
}

#if defined(BIA_ARCHITECTURE_X86_64)
template<OP_CODE _Op_code, typename _Register>
inline size_t instruction64(stream::output_stream & _output, int64_t _value)
{
	static_assert(_Op_code == OP_CODE::MOVE, "This opcode is not supported.");
	static_assert(_Register::size() == 64, "Only 64 bit registers are supported.");

	switch (_Op_code) {
	case OP_CODE::MOVE:
		return _output.write_all(0x48_8, static_cast<uint8_t>(0xb8 | _Register::value()), _value);
	}

	BIA_IMPLEMENTATION_ERROR;
}
#endif



template<OP_CODE _Op_code>
inline size_t instruction8(stream::output_stream & _output, int8_t _value)
{
	static_assert(_Op_code == OP_CODE::PUSH, "This opcode is not supported.");

	switch (_Op_code) {
	case OP_CODE::PUSH:
		return _output.write_all(0x6a_8, _value);
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE _Op_code>
inline size_t instruction32(stream::output_stream & _output, int32_t _value)
{
	static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::JUMP_RELATIVE || _Op_code == OP_CODE::JUMP_EQUAL || _Op_code == OP_CODE::JUMP_NOT_EQUAL, "This opcode is not supported.");

	switch (_Op_code) {
	case OP_CODE::PUSH:
		return _output.write_all(0x68_8, _value);
	case OP_CODE::JUMP_RELATIVE:
		return _output.write_all(0xe9_8, _value);
	case OP_CODE::JUMP_EQUAL:
		return _output.write_all(0x0f_8, 0x84_8, _value);
	case OP_CODE::JUMP_NOT_EQUAL:
		return _output.write_all(0x0f_8, 0x85_8, _value);
	}

	BIA_IMPLEMENTATION_ERROR;
}
#endif

}
	}
}
