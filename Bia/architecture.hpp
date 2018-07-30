#pragma once

#include <cstdint>
#include <type_traits>

#include "config.hpp"
#include "output_stream.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if defined(BIA_ARCHITECTURE_X86)
enum class REGISTER
{
	AL,
	EAX,
	ECX,
	ESP,
	EBP
};

enum class OP_CODE
{
	PUSH,
	MOVE,
	CALL,
	ADD,
	SUBTRACT,
	LEA,
	LEAVE,
	RETURN_NEAR,
	TEST,
	JUMP_RELATIVE,
	JUMP_EQUAL,
	JUMP_NOT_EQUAL,
};

inline int8_t operator "" _8(unsigned long long _value)
{
	return static_cast<int8_t>(_value);
}

inline int16_t operator "" _16(unsigned long long _value)
{
	return static_cast<int16_t>(_value);
}

inline int32_t operator "" _32(unsigned long long _value)
{
	return static_cast<int32_t>(_value);
}

template<REGISTER _Register, typename _Offset, bool _Effective_address>
struct register_offset
{
	_Offset offset;

	register_offset(_Offset _Offset) noexcept
	{
		offset = _Offset;
	}
};

template<REGISTER _Register, bool _Effective_address>
struct register_offset<_Register, void, _Effective_address>
{
};

class architecture
{
public:
	/**
	 * Writes the specified instruction without params to the output stream.
	 *
	 * @since 3.64.127.716
	 * @date 27-Apr-18
	 *
	 * @tparam _Op_code The operation code.
	 *
	 * @param [out] _output The output stream.
	 *
	 * @throws See stream::output_stream::write_all().
	 *
	 * @return The size of the instruction in bytes.
	*/
	template<OP_CODE _Op_code>
	static size_t add_instruction(stream::output_stream & _output)
	{
		static_assert(_Op_code == OP_CODE::LEAVE || _Op_code == OP_CODE::RETURN_NEAR, "This opcode is not supported.");

		switch (_Op_code) {
		case OP_CODE::LEAVE:
			return _output.write_all(0xc9_8);
		case OP_CODE::RETURN_NEAR:
			return _output.write_all(0xc3_8);
		}
	}
	/**
	 * Writes the specified instruction with one register to the output stream.
	 *
	 * @since 3.64.127.716
	 * @date 27-Apr-18
	 *
	 * @tparam _Op_code The operation code.
	 * @tparam _Register The register.
	 *
	 * @param [out] _output The output stream.
	 *
	 * @throws See stream::output_stream::write_all().
	 *
	 * @return The size of the instruction in bytes.
	*/
	template<OP_CODE _Op_code, REGISTER _Register>
	static size_t add_instruction(stream::output_stream & _output)
	{
		static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::CALL, "This opcode is not supported.");

		switch (_Op_code) {
		case OP_CODE::PUSH:
			return _output.write_all(static_cast<uint8_t>(0x50 | get_register_code<_Register>()));
		case OP_CODE::CALL:
			return _output.write_all(0xff_8, static_cast<uint8_t>(0320 | get_register_code<_Register>()));
		}
	}
	/**
	 * Writes the specified instruction with a source and destination register to the output stream.
	 *
	 * @since 3.64.127.716
	 * @date 27-Apr-18
	 *
	 * @tparam _Op_code The operation code.
	 * @tparam _Dest The destination register.
	 * @tparam _Src The source register.
	 * @tparam _Offset The destination offset.
	 *
	 * @param [out] _output The output stream.
	 * @param _offset The offset.
	 *
	 * @throws See stream::output_stream::write_all().
	 *
	 * @return The size of the instruction in bytes.
	*/
	template<OP_CODE _Op_code, REGISTER _Dest, REGISTER _Src, typename _Offset>
	static size_t add_instruction(stream::output_stream & _output, _Offset _offset)
	{
		static_assert(_Op_code == OP_CODE::MOVE || _Op_code == OP_CODE::LEA || _Op_code == OP_CODE::TEST, "This opcode is not supported.");
		static_assert(std::is_same<int8_t, _Offset>::value || std::is_same<int32_t, _Offset>::value, "Offset must be int8_t or int32_t.");

		switch (_Op_code) {
		case OP_CODE::MOVE:
		{
			// No offset
			if (_offset == 0) {
				return _output.write_all(0x89_8, static_cast<uint8_t>(0300 | get_register_code<_Src>() << 3 | get_register_code<_Dest>()));
			} // 8 bit offset
			else if (std::is_same<_Offset, int8_t>::value) {
				return _output.write_all(0x8b_8, static_cast<uint8_t>(0100 | get_register_code<_Src>() | get_register_code<_Dest>() << 3), static_cast<uint8_t>(_offset));
			}

			// 32 bit offset
			return _output.write_all(0x8b_8, static_cast<uint8_t>(0200 | get_register_code<_Src>() | get_register_code<_Dest>() << 3), static_cast<uint32_t>(_offset));
		}
		case OP_CODE::LEA:
		{
			// Add SIB byte
			if (_Src == REGISTER::ESP) {
				static_assert(!(_Src == REGISTER::ESP && _Op_code == OP_CODE::LEA), "SIB not implemented.");
			}

			// 8 bit offset
			if (std::is_same<int8_t, _Offset>::value) {
				return _output.write_all(0x8d_8, static_cast<uint8_t>(0100 | get_register_code<_Src>() | get_register_code<_Dest>() << 3), static_cast<uint8_t>(_offset));
			} 
				
			// 32 bit offset
			return _output.write_all(0x8d_8, static_cast<uint8_t>(0200 | get_register_code<_Src>() | get_register_code<_Dest>() << 3), static_cast<uint32_t>(_offset));
		}
		case OP_CODE::TEST:
		{
			static_assert(RegisterSize<_Dest>() == RegisterSize<_Src>() || _Op_code != OP_CODE::TEST, "Registers must be the same size for testing.");

			// 8 bit register
			if (RegisterSize<_Dest>() == 8) {
				return _output.write_all(0x84_8, static_cast<uint8_t>(0300 | get_register_code<_Src>() << 3 | get_register_code<_Dest>()));
			}
			
			// 32 bit register
			return _output.write_all(0x85_8, static_cast<uint8_t>(0300 | get_register_code<_Src>() << 3 | get_register_code<_Dest>()));
		}
		}
	}
	template<OP_CODE _Op_code, REGISTER _Register, typename _Offset>
	static size_t add_instruction(stream::output_stream & _output, _Offset _offset)
	{
		static_assert(_Op_code == OP_CODE::PUSH, "This opcode is not supported.");
		static_assert(std::is_same<int8_t, _Offset>::value || std::is_same<int32_t, _Offset>::value, "Offset must be int8_t or int32_t.");

		switch (_Op_code) {
		case OP_CODE::PUSH:
		{
			if (std::is_same<int8_t, _Offset>::value) {
				return _output.write_all(0xff_8, static_cast<uint8_t>(0160 | get_register_code<_Register>()), _offset);
			}

			return _output.write_all(0xff_8, static_cast<uint8_t>(0260 | get_register_code<_Register>()), _offset);
		}
		}
	}
	template<OP_CODE _Op_code>
	static size_t add_instruction32(stream::output_stream & _output, int32_t _value)
	{
		static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::JUMP_RELATIVE || _Op_code == OP_CODE::JUMP_EQUAL || _Op_code == OP_CODE::JUMP_NOT_EQUAL, "This opcode is not supported.");

		switch (_Op_code) {
		case OP_CODE::PUSH:
			return _output.write_all(0x68_8, static_cast<uint32_t>(_value));
		case OP_CODE::JUMP_RELATIVE:
			return _output.write_all(0xe9_8, static_cast<uint32_t>(_value));
		case OP_CODE::JUMP_EQUAL:
			return _output.write_all(0x840f_16, static_cast<uint32_t>(_value));
		case OP_CODE::JUMP_NOT_EQUAL:
			return _output.write_all(0x850f_16, static_cast<uint32_t>(_value));
		}
	}
	template<OP_CODE _Op_code>
	static size_t add_instruction8(stream::output_stream & _output, int8_t _value)
	{
		static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::JUMP_RELATIVE || _Op_code == OP_CODE::JUMP_EQUAL || _Op_code == OP_CODE::JUMP_NOT_EQUAL, "This opcode is not supported.");

		switch (_Op_code) {
		case OP_CODE::PUSH:
			return _output.write_all(0x6a_8, static_cast<uint8_t>(_value));
		case OP_CODE::JUMP_RELATIVE:
			return _output.write_all(0xeb_8, static_cast<uint8_t>(_value));
		case OP_CODE::JUMP_EQUAL:
			return _output.write_all(0x74_8, static_cast<uint8_t>(_value));
		case OP_CODE::JUMP_NOT_EQUAL:
			return _output.write_all(0x75_8, static_cast<uint8_t>(_value));
		}
	}
	template<OP_CODE _Op_code, REGISTER _Register>
	static size_t add_instruction32(stream::output_stream & _output, int32_t _value)
	{
		static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::MOVE || _Op_code == OP_CODE::ADD || _Op_code == OP_CODE::SUBTRACT, "This opcode is not supported.");

		switch (_Op_code) {
		case OP_CODE::PUSH:
			return _output.write_all(0xff_8, static_cast<uint8_t>(0260 | get_register_code<_Register>()), static_cast<uint32_t>(_value));
		case OP_CODE::MOVE:
			return _output.write_all(static_cast<uint8_t>(0xb8 | get_register_code<_Register>()), static_cast<uint32_t>(_value));
		case OP_CODE::ADD:
		{
			// Special opcode for EAX
			if (_Register == REGISTER::EAX) {
				return _output.write_all(0x05_8, static_cast<uint32_t>(_value));
			}
			
			return _output.write_all(0x81_8, static_cast<uint8_t>(0300 | get_register_code<_Register>()), static_cast<uint32_t>(_value));
		}
		case OP_CODE::SUBTRACT:
		{
			// Special opcode for EAX
			if (_Register == REGISTER::EAX) {
				return _output.write_all(0x2d_8, static_cast<uint32_t>(_value));
			}
			
			return _output.write_all(0x81_8, static_cast<uint8_t>(0350 | get_register_code<_Register>()), static_cast<uint32_t>(_value));
		}
		}
	}
	template<OP_CODE _Op_code, REGISTER _Register>
	static size_t add_instruction8(stream::output_stream & _output, int8_t _value)
	{
		static_assert(_Op_code == OP_CODE::PUSH || _Op_code == OP_CODE::ADD || _Op_code == OP_CODE::SUBTRACT, "This opcode is not supported.");

		switch (_Op_code) {
		case OP_CODE::PUSH:
		{
			// If constant displacement is 0 the push register directly, otherwise push with one byte displacement
			if (!_value) {
				return add_instruction<OP_CODE::PUSH, _Register>(_output);
			}

			return _output.write_all(0xff_8, static_cast<uint8_t>(0160 | get_register_code<_Register>()), static_cast<uint8_t>(_value));
		}
		case OP_CODE::ADD:
		{
			// Special opcode for EAX
			if (_Register == REGISTER::EAX) {
				return _output.write_all(0x04_8, static_cast<uint8_t>(_value));
			}

			return _output.write_all(0x83_8, static_cast<uint8_t>(0300 | get_register_code<_Register>()), static_cast<uint8_t>(_value));
		}
		case OP_CODE::SUBTRACT:
		{
			// Special opcode for EAX
			if (_Register == REGISTER::EAX) {
				return _output.write_all(0x2c_8, static_cast<uint8_t>(_value));
			}
			
			return _output.write_all(0x83_8, static_cast<uint8_t>(0350 | get_register_code<_Register>()), static_cast<uint8_t>(_value));
		}
		}
	}

private:
	template<REGISTER _Register>
	constexpr static uint8_t get_register_code() noexcept
	{
		static_assert(_Register == REGISTER::AL || _Register == REGISTER::EAX || _Register == REGISTER::ECX || _Register == REGISTER::ESP || _Register == REGISTER::EBP, "This register is not supported.");

		switch (_Register) {
		case REGISTER::AL:
		case REGISTER::EAX:
			return 0;
		case REGISTER::ECX:
			return 1;
		case REGISTER::ESP:
			return 4;
		case REGISTER::EBP:
			return 5;
		default:
			break;
		}

		return 0;
	}
	template<REGISTER _Register>
	constexpr static int RegisterSize() noexcept
	{
		static_assert(_Register == REGISTER::AL || _Register == REGISTER::EAX || _Register == REGISTER::ECX || _Register == REGISTER::ESP || _Register == REGISTER::EBP, "This register is not supported.");

		switch (_Register) {
		case REGISTER::AL:
			return 8;
		case REGISTER::EAX:
		case REGISTER::ECX:
		case REGISTER::ESP:
		case REGISTER::EBP:
			return 32;
		default:
			break;
		}

		return 0;
	}
};
#endif

}
}
}