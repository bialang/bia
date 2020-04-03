#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <cstdint>
#include <type_traits>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {

typedef std::uint8_t op_code_type;
constexpr auto max_instruction_size = sizeof(op_code_type) + 4;

enum op_code : op_code_type
{
	oc_return_void,
	oc_jump,
	oc_jump_true,
	oc_jump_false
};

} // namespace bytecode
} // namespace bia

#endif