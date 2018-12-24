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
#if defined(BIA_ARCHITECTURE_X86_64)
template<typename Register>
constexpr inline int8_t register_prefix()
{
	return std::is_base_of<register64_extended, Register>::value ? 0x41 : 0;
}

template<typename Destination, typename Source>
constexpr inline int8_t register_prefix()
{
	return register_prefix<Source>() | (std::is_base_of<register64_extended, Destination>::value ? 0x4c : 0);
}
#endif

template<OP_CODE Op_code>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(Op_code == OP_CODE::RETURN_NEAR, "This opcode is not supported.");

	switch (Op_code) {
	case OP_CODE::RETURN_NEAR:
		return _output.write_all(0xc3_8);
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE Op_code, typename Register>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(Op_code == OP_CODE::PUSH || Op_code == OP_CODE::POP || Op_code == OP_CODE::CALL, "This opcode is not supported.");

	size_t _written = 0;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(Register::size() == 32, "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert(Register::size() == 64, "Register is not supported.");

	if (register_prefix<Register>()) {
		_written = _output.write_all(register_prefix<Register>());
	}
#endif

	switch (Op_code) {
	case OP_CODE::PUSH:
		return _written + _output.write_all(static_cast<uint8_t>(0x50 | Register::value()));
	case OP_CODE::POP:
		return _written + _output.write_all(static_cast<uint8_t>(0x58 | Register::value()));
	case OP_CODE::CALL:
		return _written + _output.write_all(0xff_8, static_cast<uint8_t>(0320 | Register::value()));
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE Op_code, typename Register, typename Offset_type>
inline size_t instruction(stream::output_stream & _output, Offset_type _offset)
{
	static_assert(Op_code == OP_CODE::PUSH || Op_code == OP_CODE::CALL, "This opcode is not supported.");
	static_assert(std::is_same<Offset_type, int8_t>::value || std::is_same<Offset_type, int32_t>::value, "Offset must be int8_t or int32_t.");

	size_t _written = 0;
	constexpr auto _mode = std::is_same<Offset_type, int8_t>::value ? 0100 : 0200;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(Register::size() == 32, "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert(Register::size() == 64, "Register is not supported.");

	if (register_prefix<Register>()) {
		_written = _output.write_all(register_prefix<Register>());
	}
#endif

	switch (Op_code) {
	case OP_CODE::PUSH:
	{
#if defined(BIA_ARCHITECTURE_X86_32)
		constexpr auto _special_register = std::is_same<Register, esp>::value;
#elif defined(BIA_ARCHITECTURE_X86_64)
		constexpr auto _special_register = std::is_same<Register, rsp>::value;
#endif

		if (_special_register) {
			return _written + _output.write_all(0xff_8, static_cast<uint8_t>(_mode | 060 | Register::value()), 0x24_8, _offset);
		}

		return _written + _output.write_all(0xff_8, static_cast<uint8_t>(_mode | 060 | Register::value()), _offset);
	}
	case OP_CODE::CALL:
		return _written + _output.write_all(0xff_8, static_cast<uint8_t>(_mode | 020 | Register::value()), _offset);
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE Op_code, typename Destination, typename Source>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(
		Op_code == OP_CODE::MOVE
		|| Op_code == OP_CODE::TEST
#if defined(BIA_ARCHITECTURE_X86_64)
		|| Op_code == OP_CODE::MOVE_QUADWORD
#endif
		, "This opcode is not supported.");

	size_t _written = 0;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(Destination::size() == 32 && Source::size() == 32, "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert(Op_code == OP_CODE::MOVE_QUADWORD || ((Destination::size() == 32 || Destination::size() == 64) && Destination::size() == Source::size()), "Register is not supported.");

	// Write prefix for 64 bit register
	if (Op_code != OP_CODE::MOVE_QUADWORD && Destination::size() == 64) {
		_written = _output.write_all(static_cast<uint8_t>(0x48 | register_prefix<Destination, Source>()));
	}
#endif

	switch (Op_code) {
	case OP_CODE::MOVE:
		return _written + _output.write_all(0x89_8, static_cast<uint8_t>(0300 | Source::value() << 3 | Destination::value()));
	case OP_CODE::TEST:
		return _written + _output.write_all(0x85_8, static_cast<uint8_t>(0300 | Source::value() << 3 | Destination::value()));
#if defined(BIA_ARCHITECTURE_X86_64)
	case OP_CODE::MOVE_QUADWORD:
		static_assert(Op_code != OP_CODE::MOVE_QUADWORD || (std::is_base_of<xmm, Destination>::value && Source::size() == 64), "Register is not supported.");

		return _output.write_all(0x66_8, static_cast<uint8_t>(0x48 | register_prefix<Destination, Source>()), 0x0f_8, 0x6e_8, static_cast<uint8_t>(0300 | Destination::value() << 3 | Source::value()));
#endif
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE Op_code, typename Destination, typename Source, typename Source_offset_type>
inline size_t instruction(stream::output_stream & _output, Source_offset_type _offset)
{
	static_assert(Op_code == OP_CODE::MOVE || Op_code == OP_CODE::LEA, "This opcode is not supported.");
	static_assert(std::is_same<Source_offset_type, int8_t>::value || std::is_same<Source_offset_type, int32_t>::value, "Offset must be int8_t or int32_t.");

	int8_t _op_code = 0;
	constexpr auto _mode = std::is_same<Source_offset_type, int8_t>::value ? 0100 : 0200;

	switch (Op_code) {
	case OP_CODE::MOVE:
		_op_code = 0x8b;

		break;
	case OP_CODE::LEA:
		_op_code = 0x8d;

		break;
	default:
		BIA_IMPLEMENTATION_ERROR;
	}

	size_t _written = 0;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(Source::size() == 32 && Destination::size() == 32, "Register is not supported.");

	// Add SIB byte for stack pointer register
	constexpr auto _special_register = std::is_same<Source, esp>::value;
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert((Op_code != OP_CODE::MOVE && Op_code != OP_CODE::LEA) || ((Destination::size() == 32 || Destination::size() == 64) && Source::size() == 64), "Register is not supported.");

	// Add SIB byte for stack pointer register
	constexpr auto _special_register = std::is_same<Source, rsp>::value;

	// Write prefix for 64 bit register
	_written = _output.write_all(static_cast<uint8_t>(0x48 | register_prefix<Destination, Source>()));
#endif

	if (_special_register) {
		return _written + _output.write_all(_op_code, static_cast<uint8_t>(_mode | Destination::value() << 3 | Source::value()), 0x24_8, _offset);
	}

	return _written + _output.write_all(_op_code, static_cast<uint8_t>(_mode | Destination::value() << 3 | Source::value()), _offset);
}

template<OP_CODE Op_code, typename Destination, typename Source, typename Source_offset_type>
inline size_t instruction(stream::output_stream & _output)
{
	static_assert(Op_code == OP_CODE::MOVE, "This opcode is not supported.");
	static_assert(std::is_void<Source_offset_type>::value, "Offset must be void.");

	size_t _written = 0;

	#if defined(BIA_ARCHITECTURE_X86_32)
		static_assert(Source::size() == 32 && Destination::size() == 32, "Register is not supported.");

		// Add SIB byte for stack pointer register
		constexpr auto _special_register = std::is_same<Source, esp>::value;
	#elif defined(BIA_ARCHITECTURE_X86_64)
		static_assert((Destination::size() == 32 || Destination::size() == 64) && Source::size() == 64, "Register is not supported.");

		// Add SIB byte for stack pointer register
		constexpr auto _special_register = std::is_same<Source, rsp>::value;

		// Write prefix for 64 bit register
		_written = _output.write_all(static_cast<uint8_t>(0x48 | register_prefix<Destination, Source>()));
	#endif

	switch (Op_code) {
	case OP_CODE::MOVE:
	{
		if (_special_register) {
			return _written + _output.write_all(0x8b_8, static_cast<uint8_t>(Destination::value() << 3 | Source::value()), 0x24_8);
		}

		return _written + _output.write_all(0x8b_8, static_cast<uint8_t>(Destination::value() << 3 | Source::value()));
	}
	default:
		BIA_IMPLEMENTATION_ERROR;
	}
}



template<OP_CODE Op_code, typename Register>
inline size_t instruction8(stream::output_stream & _output, int8_t _value)
{
	static_assert(Op_code == OP_CODE::ADD || Op_code == OP_CODE::SUB, "This opcode is not supported.");

	size_t _written = 0;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(Register::size() == 32, "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert(Register::size() == 32 || Register::size() == 64, "Register is not supported.");

	// Write prefix for 64 bit register
	if (Register::size() == 64) {
		_written = _output.write_all(static_cast<uint8_t>(0x48 | register_prefix<Register>()));
	}
#endif

	switch (Op_code) {
	case OP_CODE::ADD:
		return _written + _output.write_all(0x83_8, static_cast<uint8_t>(0300 | Register::value()), _value);
	case OP_CODE::SUB:
		return _written + _output.write_all(0x83_8, static_cast<uint8_t>(0350 | Register::value()), _value);
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE Op_code, typename Register>
inline size_t instruction32(stream::output_stream & _output, int32_t _value)
{
	static_assert(Op_code == OP_CODE::MOVE || Op_code == OP_CODE::ADD || Op_code == OP_CODE::SUB, "This opcode is not supported.");

	size_t _written = 0;

#if defined(BIA_ARCHITECTURE_X86_32)
	static_assert(Register::size() == 32, "Register is not supported.");
#elif defined(BIA_ARCHITECTURE_X86_64)
	static_assert(Register::size() == 32 || Register::size() == 64, "Register is not supported.");

	// Write prefix for 64 bit register
	if (Register::size() == 64) {
		_written = _output.write_all(static_cast<uint8_t>(0x48 | register_prefix<Register>()));
	}
#endif

	switch (Op_code) {
	case OP_CODE::MOVE:
	{
#if defined(BIA_ARCHITECTURE_X86_64)
		// Other op code for x64 register
		if (Register::size() == 64) {
			return _written + _output.write_all(0xc7_8, static_cast<uint8_t>(0300 | Register::value()), _value);
		}
#endif

		return _output.write_all(static_cast<uint8_t>(0xb8 | Register::value()), _value);
	}
	case OP_CODE::ADD:
	{
		// Special opcode for EAX or RAX
		if (std::is_same<Register, eax>::value
#if defined(BIA_ARCHITECTURE_X86_64)
			|| std::is_same<Register, rax>::value
#endif
			) {
			return _written + _output.write_all(0x05_8, _value);
		}

		return _written + _output.write_all(0x81_8, static_cast<uint8_t>(0300 | Register::value()), _value);
	}
	case OP_CODE::SUB:
	{
		// Special opcode for EAX or RAX
		if (std::is_same<Register, eax>::value
#if defined(BIA_ARCHITECTURE_X86_64)
			|| std::is_same<Register, rax>::value
#endif
			) {
			return _output.write_all(0x2d_8, static_cast<uint32_t>(_value));
		}

		return _output.write_all(0x81_8, static_cast<uint8_t>(0350 | Register::value()), _value);
	}
	}

	BIA_IMPLEMENTATION_ERROR;
}

#if defined(BIA_ARCHITECTURE_X86_64)
template<OP_CODE Op_code, typename Register>
inline size_t instruction64(stream::output_stream & _output, int64_t _value)
{
	static_assert(Op_code == OP_CODE::MOVE, "This opcode is not supported.");
	static_assert(Register::size() == 64, "Register is not supported.");

	switch (Op_code) {
	case OP_CODE::MOVE:
		return _output.write_all(static_cast<uint8_t>(0x48 | register_prefix<Register>()), static_cast<uint8_t>(0xb8 | Register::value()), _value);
	}

	BIA_IMPLEMENTATION_ERROR;
}
#endif



template<OP_CODE Op_code>
inline size_t instruction8(stream::output_stream & _output, int8_t _value)
{
	static_assert(Op_code == OP_CODE::PUSH, "This opcode is not supported.");

	switch (Op_code) {
	case OP_CODE::PUSH:
		return _output.write_all(0x6a_8, _value);
	}

	BIA_IMPLEMENTATION_ERROR;
}

template<OP_CODE Op_code>
inline size_t instruction32(stream::output_stream & _output, int32_t _value)
{
	static_assert(Op_code == OP_CODE::PUSH || Op_code == OP_CODE::JUMP_RELATIVE || Op_code == OP_CODE::JUMP_EQUAL || Op_code == OP_CODE::JUMP_NOT_EQUAL, "This opcode is not supported.");

	switch (Op_code) {
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
