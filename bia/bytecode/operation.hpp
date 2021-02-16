#ifndef BIA_BYTECODE_OPERATION_HPP_
#define BIA_BYTECODE_OPERATION_HPP_

#include <cstdint>

namespace bia {
namespace bytecode {

enum class Infix_operation : std::uint8_t
{
	bitwise_or,
	bitwise_xor,
	bitwise_and,
	bitwise_left_shift,
	bitwise_right_shift,
	addition,
	subtraction,
	multiplication,
	division,
	remainder,
	exponentation,
};

enum class Test_operation : std::uint8_t
{
	equal,
	not_equal,
	less,
	less_equal,
	greater,
	greater_equal,
	in,
	three_way_comparison,
};

enum class Self_operation : std::uint8_t
{
	unary_minus,
	bitwise_not,
};

} // namespace member
} // namespace bia

#endif
