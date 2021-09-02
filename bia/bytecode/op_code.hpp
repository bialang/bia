#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <bia/error/exception.hpp>
#include <cstdint>
#include <type_traits>

namespace bia {
namespace bytecode {

enum class Op_code : std::uint8_t
{
	store,

	load_resource,

	load_from_namespace,
	copy,
	copy_to_namespace,
	add,
	fadd,
	sub,
	fsub,
	mul,
	fmul,
	sdiv,
	udiv,
	fdiv,
	srem,
	urem,
	frem,
	bitwise_and,
	bitwise_or,
	bitwise_xor,
	equal,
	not_equal,
	sless_than,
	uless_than,
	sless_equal_than,
	uless_equal_than,
	sgreater_than,
	ugreater_than,
	sgreater_equal_than,
	ugreater_equal_than,

	invoke,
	test,
	negate,

	jump,
	jump_true,
	jump_false
};

enum class Size
{
	bit_8,
	bit_16,
	bit_32,
	bit_64
};

typedef std::uint32_t Address;

inline std::size_t size_to_bits(Size size)
{
	switch (size) {
	case Size::bit_8: return 8;
	case Size::bit_16: return 16;
	case Size::bit_32: return 32;
	case Size::bit_64: return 64;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
}

inline Size bits_to_size(std::size_t bits)
{
	switch (bits) {
	case 8: return Size::bit_8;
	case 16: return Size::bit_16;
	case 32: return Size::bit_32;
	case 64: return Size::bit_64;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
}

} // namespace bytecode
} // namespace bia

#endif
