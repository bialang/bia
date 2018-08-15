#pragma once

#include <cstdint>

#include "config.hpp"
#include "exception.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
enum class REGISTER
{
	EAX = 0,
	ECX = 1,
	ESP = 4,
	EBP = 5,

#if defined(BIA_ARCHITECTURE_X86_64)
	RAX = 0,
	RCX = 1,
	RSP = 4,
	RBP = 5
#endif
};

enum class OP_CODE
{
	PUSH,
	POP,
	MOVE,
	CALL,
	ADD,
	SUB,
	LEA,
	RETURN_NEAR,
	XOR,
	JUMP_RELATIVE,
	JUMP_EQUAL,
	JUMP_NOT_EQUAL,
};

#if defined(BIA_ARCHITECTURE_X86_32)
constexpr auto element_size = 4;
constexpr auto accumulator = REGISTER::EAX;
constexpr auto base_pointer = REGISTER::EBP;
constexpr auto stack_pointer = REGISTER::ESP;
#elif defined(BIA_ARCHITECTURE_X86_64)
constexpr auto element_size = 8;
constexpr auto accumulator = REGISTER::RAX;
constexpr auto base_pointer = REGISTER::RBP;
constexpr auto stack_pointer = REGISTER::RSP;
#endif

static_assert(element_size == sizeof(void*), "Invalid element size.");

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

inline int64_t operator "" _64(unsigned long long _value)
{
	return static_cast<int64_t>(_value);
}

template<REGISTER _Register>
constexpr inline size_t register_size()
{
	BIA_NOT_IMPLEMENTED;
}

template<>
constexpr inline size_t register_size<REGISTER::EAX>()
{
	return 32;
}

template<>
constexpr inline size_t register_size<REGISTER::ECX>()
{
	return 32;
}

template<>
constexpr inline size_t register_size<REGISTER::EBP>()
{
	return 32;
}

template<>
constexpr inline size_t register_size<REGISTER::ESP>()
{
	return 32;
}

#if defined(BIA_ARCHITECTURE_X86_64)
template<>
constexpr inline size_t register_size<REGISTER::RAX>()
{
	return 64;
}

template<>
constexpr inline size_t register_size<REGISTER::RCX>()
{
	return 64;
}

template<>
constexpr inline size_t register_size<REGISTER::RBP>()
{
	return 64;
}

template<>
constexpr inline size_t register_size<REGISTER::RSP>()
{
	return 64;
}
#endif

template<REGISTER _Register, typename _Offset, bool _Effective_address>
struct register_offset
{
	constexpr static REGISTER register_value = _Register;
	_Offset offset;

	register_offset(_Offset _offset) noexcept
	{
		offset = _offset;
	}
};

template<REGISTER _Register, bool _Effective_address>
struct register_offset<_Register, void, _Effective_address>
{
	constexpr static REGISTER register_value = _Register;
};
#endif

}
}
}