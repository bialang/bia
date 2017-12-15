#pragma once

#include <cstdint>

#include "biaArchitecture.h"
#include "biaStream.h"


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
	inline static void Operation(stream::BiaStream & p_output)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::RETURN_NEAR:
		{
			p_output.Write(0xc3_8);

			break;
		}
		default:
			
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation(stream::BiaStream & p_output, REGISTER p_register)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
		{
			p_output.Write(static_cast<uint8_t>(0x50 | Register(p_register)));

			break;
		}
		case OP_CODE::CALL:
		{
			p_output.Write(0xff_8);
			p_output.Write(static_cast<uint8_t>(0xd0 | Register(p_register)));

			break;
		}
		default:
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation32(stream::BiaStream & p_output, uint32_t p_unConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
		{
			p_output.Write(0x68_8);
			p_output.Write(p_unConstant);

			break;
		}
		default:
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation16(stream::BiaStream & p_output, uint16_t p_usConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::RETURN_NEAR:
		{
			p_output.Write(0xc2_8);
			p_output.Write(p_usConstant);

			break;
		}
		default:
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation8(stream::BiaStream & p_output, uint8_t p_ucConstant)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::PUSH:
		{
			p_output.Write(0x6a_8);
			p_output.Write(p_ucConstant);

			break;
		}
		default:
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation32(stream::BiaStream & p_output, uint32_t p_unConstant, REGISTER p_destination)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::MOVE:
		{
			p_output.Write(static_cast<uint8_t>(0xb8 | Register(p_destination)));
			p_output.Write(p_unConstant);

			break;
		}
		case OP_CODE::SUBTRACT:
		{
			//Special opcode for EAX
			if (p_destination == REGISTER::EAX)
			{
				p_output.Write(0x2d_8);
				p_output.Write(p_unConstant);
			}
			else
			{
				p_output.Write(0x81_8);
				p_output.Write(static_cast<uint8_t>(0xe8 | Register(p_desitnation)));
				p_output.Write(p_unConstant);
			}

			break;
		}
		default:
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation8(stream::BiaStream & p_output, uint8_t p_ucConstant, REGISTER p_destination)
	{
		switch (_OP_CODE)
		{
		case OP_CODE::MOVE:
		{
			p_output.Write(static_cast<uint8_t>(0xb8 | Register(p_destination)));
			p_output.Write(static_cast<uint32_t>(p_ucConstant));

			break;
		}
		case OP_CODE::SUBTRACT:
		{
			//Special opcode for EAX
			if (p_destination == REGISTER::EAX)
			{
				p_output.Write(0x2c_8);
				p_output.Write(p_ucConstant);
			}
			else
			{
				p_output.Write(0x83_8);
				p_output.Write(static_cast<uint8_t>(0xe8 | Register(p_desitnation)));
				p_output.Write(p_ucConstant);
			}
			

			break;
		}
		default:
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