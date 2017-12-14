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

template<typename T>
inline uint8_t operator "" _8(T p_value)
{
	return static_cast<uint8_t>(p_value);
}

class Biax86
{
public:
	template<OP_CODE _OP_CODE>
	inline static void Operation(stream::BiaStream & p_output)
	{
		switch (_OP_CODE)
		{
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
			p_output.Write(0xff_8);
			p_output.Write(0xf0 | 0x1);

			break;
		}
		default:
		}
	}
	template<OP_CODE _OP_CODE>
	inline static void Operation(REGISTER p_source, REGISTER p_desitnation);
	template<OP_CODE _OP_CODE>
	inline static void Operation(REGISTER p_source, int p_nOffset, REGISTER p_desitnation);
	template<OP_CODE _OP_CODE>
	inline static void Operation(REGISTER p_source, REGISTER p_desitnation, int p_nOffset);

};

}
}
}