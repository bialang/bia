#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <cstdint>
#include <type_traits>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {

typedef std::uint8_t op_code_type;
constexpr auto max_instruction_size = sizeof(op_code_type) + 4;

struct local_member
{
	std::uint32_t index;
};

struct global_member
{
	std::uint32_t index;
};

enum immediate_size_flag
{
	isf_8,
	isf_32,

	isf_mask = 0x1
};

enum member_flag
{
	mf_local,
	mf_global,

	mf_mask = 0x1
};

enum constant_flag
{
	cf_int8,
	cf_int32,
	cf_int64,
	cf_float,

	cf_mask = 0x3
};

enum op_code : op_code_type
{
	oc_return_void, // ()

	oc_jump, // (immediate_size): jumps to the relative address
	oc_jump_true,
	oc_jump_false,

	oc_test, // (member): tests the member and sets the test register accordingly

	oc_push, // (constant): instantiates the constant value and pushes it onto the stack

	oc_invoke, // (member, uint8): invokes the member and passes the parameter count

	oc_instantiate, // (member, constant): instantiates the given member to the constant value
};

} // namespace bytecode
} // namespace bia

#endif