#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <cstdint>
#include <type_traits>

namespace bia {
namespace bytecode {

enum class Op_code : std::uint8_t
{
	// 2 bit variations
	load                   = 0,
	load_from_namespace    = load + 4,
	copy                   = load_from_namespace + 4,
	unsigned_raw_operation = copy + 4,
	truthy                 = unsigned_raw_operation + 4,
	falsey                 = truthy + 4,
	jump                   = falsey + 4,
	jump_if_false          = jump + 4,
	jump_if_true           = jump_if_false + 4,

	// 0 bit variations
	booleanize         = jump_if_true + 4,
	load_resource      = booleanize + 4,
	resource_operation = load_resource + 4,
	invoke             = resource_operation + 4,
};

inline Op_code read_op_code(typename std::underlying_type<Op_code>::type value) noexcept
{
	return static_cast<Op_code>(value & 0xfc);
}

inline std::uint8_t get_op_code_size(typename std::underlying_type<Op_code>::type value) noexcept
{
	return static_cast<std::uint8_t>(value & 0x03);
}

} // namespace bytecode
} // namespace bia

#endif
