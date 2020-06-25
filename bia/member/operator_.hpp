#ifndef BIA_MEMBER_OPERATOR_HPP_
#define BIA_MEMBER_OPERATOR_HPP_

#include <cstdint>

namespace bia {
namespace member {

enum class infix_operator : std::uint8_t
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

enum class test_operator : std::uint8_t
{
	self,
	equal,
	not_equal,
	less,
	less_equal,
	greater,
	greater_equal,
	in,
	three_way_comparison,
};

enum class self_operator : std::uint8_t
{
	unary_minus,
	bitwise_not,
};

} // namespace member
} // namespace bia

#endif
