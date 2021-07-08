#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

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
	less_than,
	less_equal_than,
	greater_than,
	greater_equal_than,

	invoke,

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

} // namespace bytecode
} // namespace bia

#endif
