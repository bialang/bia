#pragma once

#include <cstdint>
#include <type_traits>

#include "config.hpp"
#include "type_traits.hpp"
#include "exception.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
struct register32
{
	constexpr static size_t size()
	{
		return 32;
	}
};

struct eax : register32
{
	constexpr static size_t value()
	{
		return 0;
	}
};

struct ecx : register32
{
	constexpr static size_t value()
	{
		return 1;
	}
};

struct esp : register32
{
	constexpr static size_t value()
	{
		return 4;
	}
};

struct ebp : register32
{
	constexpr static size_t value()
	{
		return 5;
	}
};

#if defined(BIA_ARCHITECTURE_X86_64)
struct register64
{
	constexpr static size_t size()
	{
		return 64;
	}
};

struct rax : register64
{
	constexpr static size_t value()
	{
		return 0;
	}
};

struct rcx : register64
{
	constexpr static size_t value()
	{
		return 1;
	}
};

struct rsp : register64
{
	constexpr static size_t value()
	{
		return 4;
	}
};

struct rbp : register64
{
	constexpr static size_t value()
	{
		return 5;
	}
};
#endif

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
typedef eax accumulator;
typedef esp stack_pointer;
typedef ebp base_pointer;
#elif defined(BIA_ARCHITECTURE_X86_64)
constexpr auto element_size = 8;
typedef rax accumulator;
typedef rsp stack_pointer;
typedef rbp base_pointer;
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

template<typename _Register, typename _Offset, bool _Effective_address>
struct register_offset
{
	typedef _Register register_type;
	_Offset offset;

	register_offset(_Offset _offset) noexcept
	{
		offset = _offset;
	}
};

template<typename _Register, bool _Effective_address>
struct register_offset<_Register, void, _Effective_address>
{
	typedef _Register register_type;
};
#endif

}
}
}