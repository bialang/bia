#pragma once

namespace bia
{
namespace machine
{
namespace architecture
{

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

}
}
}