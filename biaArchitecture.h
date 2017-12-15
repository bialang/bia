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
	SUBTRACT,
	RETURN_NEAR
};

template<typename T>
inline uint8_t operator "" _8(T p_value)
{
	return static_cast<uint8_t>(p_value);
}

template<typename T>
inline uint32_t operator "" _32(T p_value)
{
	return static_cast<uint32_t>(p_value);
}

}
}
}