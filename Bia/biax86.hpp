#pragma once

#include <cstdint>

#include "biaArchitecture.hpp"
#include "biaOutputStream.hpp"


namespace bia
{
namespace machine
{
namespace architecture
{

class Biax86
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
			
			throw 1;
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation(stream::BiaOutputStream & p_output, REGISTER p_register)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(static_cast<uint8_t>(0x50 | Register(p_register)));
		case OP_CODE::CALL:
			return p_output.WriteAll(0xff_8, static_cast<uint8_t>(0xd0 | Register(p_register)));
		default:
			throw 1;
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation32(stream::BiaOutputStream & p_output, uint32_t p_unConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0x68_8, p_unConstant);
		default:
			throw 1;
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation16(stream::BiaOutputStream & p_output, uint16_t p_usConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::RETURN_NEAR:
			return p_output.WriteAll(0xc2_8, p_usConstant);
		default:
			throw 1;
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation8(stream::BiaOutputStream & p_output, uint8_t p_ucConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
			return p_output.WriteAll(0x6a_8, p_ucConstant);
		default:
			throw 1;
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation32(stream::BiaOutputStream & p_output, uint32_t p_unConstant, REGISTER p_destination)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::MOVE:
			return p_output.WriteAll(static_cast<uint8_t>(0xb8 | Register(p_destination)), p_unConstant);
		case OP_CODE::ADD:
		{
			//Special opcode for EAX
			if (p_destination == REGISTER::EAX)
				return p_output.WriteAll(0x05_8, p_unConstant);
			else
				return p_output.WriteAll(0x81_8, static_cast<uint8_t>(0300 | Register(p_destination)), p_unConstant);
		}
		case OP_CODE::SUBTRACT:
		{
			//Special opcode for EAX
			if (p_destination == REGISTER::EAX)
				return p_output.WriteAll(0x2d_8, p_unConstant);
			else
				return p_output.WriteAll(0x81_8, static_cast<uint8_t>(0xe8 | Register(p_destination)), p_unConstant);
		}
		default:
			throw 1;
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation8(stream::BiaOutputStream & p_output, uint8_t p_ucConstant, REGISTER p_destination)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::MOVE:
			return p_output.WriteAll(static_cast<uint8_t>(0xb8 | Register(p_destination)), static_cast<uint32_t>(p_ucConstant));
		case OP_CODE::ADD:
		{
			//Special opcode for EAX
			if (p_destination == REGISTER::EAX)
				return p_output.WriteAll(0x04_8, p_ucConstant);
			else
				return p_output.WriteAll(0x83_8, static_cast<uint8_t>(0300 | Register(p_destination)), p_ucConstant);
		}
		case OP_CODE::SUBTRACT:
		{
			//Special opcode for EAX
			if (p_destination == REGISTER::EAX)
				return p_output.WriteAll(0x2c_8, p_ucConstant);
			else
				return p_output.WriteAll(0x83_8, static_cast<uint8_t>(0xe8 | Register(p_destination)), p_ucConstant);
		}
		default:
			throw 1;
		}
	}

private:
	inline static uint8_t Register(REGISTER p_register)
	{
		switch (p_register)
		{
		case REGISTER::EAX:
			return 0;
		case REGISTER::ESP:
			return 4;
		case REGISTER::EBP:
			return 5;
		default:
			throw 1;
		}
	}
};

}
}
}