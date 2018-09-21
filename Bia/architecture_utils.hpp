#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>

#include "config.hpp"
#include "type_traits.hpp"
#include "exception.hpp"


namespace bia
{
namespace machine
{
namespace platform
{

template<typename Type>
inline bool is_one_byte_value(Type _value) noexcept
{
	return false;
}

inline bool is_one_byte_value(int32_t _value) noexcept
{
	return _value <= std::numeric_limits<int8_t>::max() && _value >= std::numeric_limits<int8_t>::min();
}

inline bool is_one_byte_value(uint32_t _value) noexcept
{
	return _value <= std::numeric_limits<int8_t>::max();
}

template<typename Type>
inline bool is_four_byte_value(Type _value) noexcept
{
	return false;
}

inline bool is_four_byte_value(int64_t _value) noexcept
{
	return _value <= std::numeric_limits<int32_t>::max() && _value >= std::numeric_limits<int32_t>::min();
}

inline bool is_four_byte_value(uint64_t _value) noexcept
{
	return _value <= std::numeric_limits<int32_t>::max();
}

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

struct edx : register32
{
	constexpr static size_t value()
	{
		return 2;
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
struct register64_basic
{
	constexpr static size_t size()
	{
		return 64;
	}
};

struct register64_extended
{
	constexpr static size_t size()
	{
		return 64;
	}
};

struct xmm
{
	constexpr static size_t size()
	{
		return 128;
	}
};

struct rax : register64_basic
{
	constexpr static size_t value()
	{
		return 0;
	}
};

struct rcx : register64_basic
{
	constexpr static size_t value()
	{
		return 1;
	}
};

struct rdx : register64_basic
{
	constexpr static size_t value()
	{
		return 2;
	}
};

struct rsp : register64_basic
{
	constexpr static size_t value()
	{
		return 4;
	}
};

struct rbp : register64_basic
{
	constexpr static size_t value()
	{
		return 5;
	}
};

struct rsi : register64_basic
{
	constexpr static size_t value()
	{
		return 6;
	}
};

struct rdi : register64_basic
{
	constexpr static size_t value()
	{
		return 7;
	}
};

struct r8 : register64_extended
{
	constexpr static size_t value()
	{
		return 0;
	}
};

struct r9 : register64_extended
{
	constexpr static size_t value()
	{
		return 1;
	}
};

struct r11 : register64_extended
{
	constexpr static size_t value()
	{
		return 3;
	}
};

struct xmm0 : xmm
{
	constexpr static size_t value()
	{
		return 0;
	}
};

struct xmm1 : xmm
{
	constexpr static size_t value()
	{
		return 1;
	}
};

struct xmm2 : xmm
{
	constexpr static size_t value()
	{
		return 2;
	}
};

struct xmm3 : xmm
{
	constexpr static size_t value()
	{
		return 3;
	}
};

struct xmm4 : xmm
{
	constexpr static size_t value()
	{
		return 4;
	}
};

struct xmm5 : xmm
{
	constexpr static size_t value()
	{
		return 5;
	}
};

struct xmm6 : xmm
{
	constexpr static size_t value()
	{
		return 6;
	}
};

struct xmm7 : xmm
{
	constexpr static size_t value()
	{
		return 7;
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

#if defined(BIA_ARCHITECTURE_X86_64)
	MOVE_QUADWORD,
#endif
};

#if defined(BIA_ARCHITECTURE_X86_32)
constexpr auto element_size = 4;

#if defined(BIA_COMPILER_MSVC)
constexpr auto stack_alignment = 4;
#else
constexpr auto stack_alignment = 16;
#endif

typedef eax accumulator;
typedef esp stack_pointer;
typedef ebp base_pointer;
#elif defined(BIA_ARCHITECTURE_X86_64)
constexpr auto element_size = 8;
constexpr auto stack_alignment = 16;

typedef rax accumulator;
typedef rsp stack_pointer;
typedef rbp base_pointer;
#endif

static_assert(element_size == sizeof(void*), "Invalid element size.");

inline int8_t operator "" _8(unsigned long long _value) noexcept
{
	return static_cast<int8_t>(_value);
}

inline int16_t operator "" _16(unsigned long long _value) noexcept
{
	return static_cast<int16_t>(_value);
}

inline int32_t operator "" _32(unsigned long long _value) noexcept
{
	return static_cast<int32_t>(_value);
}

inline int64_t operator "" _64(unsigned long long _value) noexcept
{
	return static_cast<int64_t>(_value);
}

inline int32_t align_stack(int32_t _value) noexcept
{
	auto _tmp = _value % stack_alignment;

	if (_tmp) {
		_value += stack_alignment - _tmp;
	}

	return _value;
}

template<typename Register, typename Offset_type, bool Effective_address>
struct register_offset
{
	typedef Register register_type;
	Offset_type offset;

	register_offset(Offset_type _offset) noexcept
	{
		offset = _offset;
	}
};

template<typename Register, bool Effective_address>
struct register_offset<Register, void, Effective_address>
{
	typedef Register register_type;
};
#endif

}
}
}
