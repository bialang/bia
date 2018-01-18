#pragma once

#include <cstdint>
#include <type_traits>

#include "biaConfig.hpp"
#include "biaOutputStream.hpp"
#include "biaException.hpp"

#define BIA_THROW_INVALID_OP_CODE throw BIA_IMPLEMENTATION_EXCEPTION("Invalid op code.");


namespace bia
{
namespace machine
{
namespace architecture
{

#if defined(BIA_ARCHITECTURE_MG32)
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

inline uint8_t operator "" _8(unsigned long long p_ullValue)
{
	return static_cast<uint8_t>(p_ullValue);
}

inline uint16_t operator "" _16(unsigned long long p_ullValue)
{
	return static_cast<uint16_t>(p_ullValue);
}

inline uint32_t operator "" _32(unsigned long long p_ullValue)
{
	return static_cast<uint32_t>(p_ullValue);
}

template<REGISTER _REGISTER, typename _OFFSET, bool _EFFECTIVE_ADDRESS>
struct RegisterOffset
{
	_OFFSET offset;

	inline RegisterOffset(_OFFSET p_offset)
	{
		offset = p_offset;
	}
};

template<REGISTER _REGISTER, bool _EFFECTIVE_ADDRESS>
struct RegisterOffset<_REGISTER, void, _EFFECTIVE_ADDRESS>
{
};

class BiaArchitecture
{
public:
	template<OP_CODE _OP_CODE>
	inline static void Operation(stream::BiaOutputStream & p_output)
	{
		static_assert(_OP_CODE == OP_CODE::LEAVE || _OP_CODE == OP_CODE::RETURN_NEAR, "This opcode is not supported.");

		switch (_OP_CODE)
		{
		case OP_CODE::LEAVE:
			return p_output.WriteAll(0xc9_8);
		case OP_CODE::RETURN_NEAR:
			return p_output.WriteAll(0xc3_8);
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _REGISTER>
	inline static void Operation(stream::BiaOutputStream & p_output)
	{
		static_assert(_OP_CODE == OP_CODE::PUSH || _OP_CODE == OP_CODE::CALL, "This opcode is not supported.");

		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(static_cast<uint8_t>(0x50 | Register<_REGISTER>()));
		case OP_CODE::CALL:
			return p_output.WriteAll(0xff_8, static_cast<uint8_t>(0320 | Register<_REGISTER>()));
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _DESTINATION, REGISTER _SOURCE, typename _OFFSET>
	inline static void Operation(stream::BiaOutputStream & p_output, _OFFSET p_offset)
	{
		static_assert(_OP_CODE == OP_CODE::MOVE || _OP_CODE == OP_CODE::LEA || _OP_CODE == OP_CODE::TEST, "This opcode is not supported.");
		static_assert(std::is_same<int8_t, _OFFSET>::value || std::is_same<int32_t, _OFFSET>::value, "Offset must be int8_t or int32_t.");

		switch (_OP_CODE)
		{
		case OP_CODE::MOVE:
		{
			//No offset
			if (p_offset == 0)
				return p_output.WriteAll(0x89_8, static_cast<uint8_t>(0300 | Register<_SOURCE>() << 3 | Register<_DESTINATION>()));
			//8 bit offset
			else if (std::is_same<_OFFSET, int8_t>::value)
				return p_output.WriteAll(0x8b_8, static_cast<uint8_t>(0100 | Register<_SOURCE>() | Register<_DESTINATION>() << 3), static_cast<uint8_t>(p_offset));
			//32 bit offset
			else
				return p_output.WriteAll(0x8b_8, static_cast<uint8_t>(0200 | Register<_SOURCE>() | Register<_DESTINATION>() << 3), static_cast<uint32_t>(p_offset));
		}
		case OP_CODE::LEA:
		{
			//Add SIB byte
			if (_SOURCE == REGISTER::ESP)
			{
				static_assert(!(_SOURCE == REGISTER::ESP && _OP_CODE == OP_CODE::LEA), "SIB not implemented.");
			}
			else
			{
				//8 bit offset
				if (std::is_same<int8_t, _OFFSET>::value)
					return p_output.WriteAll(0x8d_8, static_cast<uint8_t>(0100 | Register<_SOURCE>() | Register<_DESTINATION>() << 3), static_cast<uint8_t>(p_offset));
				//32 bit offset
				else
					return p_output.WriteAll(0x8d_8, static_cast<uint8_t>(0200 | Register<_SOURCE>() | Register<_DESTINATION>() << 3), static_cast<uint32_t>(p_offset));
			}
		}
		case OP_CODE::TEST:
		{
			static_assert(RegisterSize<_DESTINATION>() == RegisterSize<_SOURCE>() || _OP_CODE != OP_CODE::TEST, "Registers must be the same size for testing.");

			//8 bit register
			if (RegisterSize<_DESTINATION>() == 8)
				return p_output.WriteAll(0x84_8, static_cast<uint8_t>(0300 | Register<_SOURCE>() << 3 | Register<_DESTINATION>()));
			//32 bit register
			else
				return p_output.WriteAll(0x85_8, static_cast<uint8_t>(0300 | Register<_SOURCE>() << 3 | Register<_DESTINATION>()));
		}
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation32(stream::BiaOutputStream & p_output, int32_t p_nConstant)
	{
		static_assert(_OP_CODE == OP_CODE::PUSH || _OP_CODE == OP_CODE::JUMP_RELATIVE || _OP_CODE == OP_CODE::JUMP_EQUAL || _OP_CODE == OP_CODE::JUMP_NOT_EQUAL, "This opcode is not supported.");

		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0x68_8, static_cast<uint32_t>(p_nConstant));
		case OP_CODE::JUMP_RELATIVE:
			return p_output.WriteAll(0xe9_8, static_cast<uint32_t>(p_nConstant));
		case OP_CODE::JUMP_EQUAL:
			return p_output.WriteAll(0x840f_16, static_cast<uint32_t>(p_nConstant));
		case OP_CODE::JUMP_NOT_EQUAL:
			return p_output.WriteAll(0x850f_16, static_cast<uint32_t>(p_nConstant));
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation8(stream::BiaOutputStream & p_output, int8_t p_cConstant)
	{
		static_assert(_OP_CODE == OP_CODE::PUSH || _OP_CODE == OP_CODE::JUMP_RELATIVE || _OP_CODE == OP_CODE::JUMP_EQUAL || _OP_CODE == OP_CODE::JUMP_NOT_EQUAL, "This opcode is not supported.");

		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0x6a_8, static_cast<uint8_t>(p_cConstant));
		case OP_CODE::JUMP_RELATIVE:
			return p_output.WriteAll(0xeb_8, static_cast<uint8_t>(p_cConstant));
		case OP_CODE::JUMP_EQUAL:
			return p_output.WriteAll(0x74_8, static_cast<uint8_t>(p_cConstant));
		case OP_CODE::JUMP_NOT_EQUAL:
			return p_output.WriteAll(0x75_8, static_cast<uint8_t>(p_cConstant));
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _REGISTER>
	inline static void Operation32(stream::BiaOutputStream & p_output, int32_t p_nConstant)
	{
		static_assert(_OP_CODE == OP_CODE::PUSH || _OP_CODE == OP_CODE::MOVE || _OP_CODE == OP_CODE::ADD || _OP_CODE == OP_CODE::SUBTRACT, "This opcode is not supported.");

		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0xff_8, static_cast<uint8_t>(0260 | Register<_REGISTER>()), static_cast<uint32_t>(p_nConstant));
		case OP_CODE::MOVE:
			return p_output.WriteAll(static_cast<uint8_t>(0xb8 | Register<_REGISTER>()), static_cast<uint32_t>(p_nConstant));
		case OP_CODE::ADD:
		{
			//Special opcode for EAX
			if (_REGISTER == REGISTER::EAX)
				return p_output.WriteAll(0x05_8, static_cast<uint32_t>(p_nConstant));
			else
				return p_output.WriteAll(0x81_8, static_cast<uint8_t>(0300 | Register<_REGISTER>()), static_cast<uint32_t>(p_nConstant));
		}
		case OP_CODE::SUBTRACT:
		{
			//Special opcode for EAX
			if (_REGISTER == REGISTER::EAX)
				return p_output.WriteAll(0x2d_8, static_cast<uint32_t>(p_nConstant));
			else
				return p_output.WriteAll(0x81_8, static_cast<uint8_t>(0350 | Register<_REGISTER>()), static_cast<uint32_t>(p_nConstant));
		}
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _REGISTER>
	inline static void Operation8(stream::BiaOutputStream & p_output, int8_t p_cConstant)
	{
		static_assert(_OP_CODE == OP_CODE::PUSH || _OP_CODE == OP_CODE::ADD || _OP_CODE == OP_CODE::SUBTRACT, "This opcode is not supported.");

		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
		{
			//If constant displacement is 0 the push register directly, otherwise push with one byte displacement
			if (!p_cConstant)
				return Operation<OP_CODE::PUSH, _REGISTER>(p_output);
			else
				return p_output.WriteAll(0xff_8, static_cast<uint8_t>(0160 | Register<_REGISTER>()), static_cast<uint8_t>(p_cConstant));
		}
		case OP_CODE::ADD:
		{
			//Special opcode for EAX
			if (_REGISTER == REGISTER::EAX)
				return p_output.WriteAll(0x04_8, static_cast<uint8_t>(p_cConstant));
			else
				return p_output.WriteAll(0x83_8, static_cast<uint8_t>(0300 | Register<_REGISTER>()), static_cast<uint8_t>(p_cConstant));
		}
		case OP_CODE::SUBTRACT:
		{
			//Special opcode for EAX
			if (_REGISTER == REGISTER::EAX)
				return p_output.WriteAll(0x2c_8, static_cast<uint8_t>(p_cConstant));
			else
				return p_output.WriteAll(0x83_8, static_cast<uint8_t>(0350 | Register<_REGISTER>()), static_cast<uint8_t>(p_cConstant));
		}
		}
	}

private:
	template<REGISTER _REGISTER>
	inline constexpr static uint8_t Register()
	{
		static_assert(_REGISTER == REGISTER::AL || _REGISTER == REGISTER::EAX || _REGISTER == REGISTER::ECX || _REGISTER == REGISTER::ESP || _REGISTER == REGISTER::EBP, "This register is not supported.");

		switch (_REGISTER)
		{
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
			return 0;
		}
	}
	template<REGISTER _REGISTER>
	inline constexpr static int RegisterSize()
	{
		static_assert(_REGISTER == REGISTER::AL || _REGISTER == REGISTER::EAX || _REGISTER == REGISTER::ECX || _REGISTER == REGISTER::ESP || _REGISTER == REGISTER::EBP, "This register is not supported.");

		switch (_REGISTER)
		{
		case REGISTER::AL:
			return 8;
		case REGISTER::EAX:
		case REGISTER::ECX:
		case REGISTER::ESP:
		case REGISTER::EBP:
			return 32;
		default:
			return 0;
		}
	}
};
#endif

}
}
}