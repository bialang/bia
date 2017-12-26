#pragma once

#include <cstdint>

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
	EAX,
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
	RETURN_NEAR
};

inline uint8_t operator "" _8(unsigned long long p_ullValue)
{
	return static_cast<uint8_t>(p_ullValue);
}

inline uint32_t operator "" _32(unsigned long long p_ullValue)
{
	return static_cast<uint32_t>(p_ullValue);
}

class BiaArchitecture
{
public:
	template<OP_CODE _OP_CODE>
	inline static void Operation(stream::BiaOutputStream & p_output)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::RETURN_NEAR:
			return p_output.WriteAll(0xc3_8);
		default:
			BIA_THROW_INVALID_OP_CODE
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _REGISTER>
	inline static void Operation(stream::BiaOutputStream & p_output)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(static_cast<uint8_t>(0x50 | Register<_REGISTER>()));
		case OP_CODE::CALL:
			return p_output.WriteAll(0xff_8, static_cast<uint8_t>(0320 | Register<_REGISTER>()));
		default:
			BIA_THROW_INVALID_OP_CODE
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation32(stream::BiaOutputStream & p_output, int32_t p_nConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0x68_8, static_cast<uint32_t>(p_nConstant));
		default:
			BIA_THROW_INVALID_OP_CODE
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation8(stream::BiaOutputStream & p_output, int8_t p_cConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0x6a_8, static_cast<uint8_t>(p_cConstant));
		default:
			BIA_THROW_INVALID_OP_CODE
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _REGISTER>
	inline static void Operation32(stream::BiaOutputStream & p_output, int32_t p_nConstant)
	{
		switch (_OP_CODE)
		{
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
		default:
			BIA_THROW_INVALID_OP_CODE
		}
	}
	template<OP_CODE _OP_CODE, REGISTER _REGISTER>
	inline static void Operation8(stream::BiaOutputStream & p_output, int8_t p_cConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
		{
			//If constant displacement is 0 the push register directly, otherwise push with one byte displacement
			if (p_cConstant == 0)
				return p_output.WriteAll(0xff_8, static_cast<uint8_t>(0160 | Register<_REGISTER>()), static_cast<uint8_t>(p_cConstant));
			else
				return Operation<OP_CODE::PUSH>(p_output, _REGISTER);
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
		default:
			BIA_THROW_INVALID_OP_CODE
		}
	}

private:
	template<REGISTER _REGISTER>
	inline constexpr static uint8_t Register()
	{
		static_assert(_REGISTER == REGISTER::EAX || _REGISTER == REGISTER::ESP || _REGISTER == REGISTER::EBP, "Invalid register.");

		switch (_REGISTER)
		{
		case REGISTER::EAX:
			return 0;
		case REGISTER::ESP:
			return 4;
		case REGISTER::EBP:
			return 5;
		}
	}
};
#endif

}
}
}