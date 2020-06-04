#ifndef BIA_MEMBER_OPERATOR_HPP_
#define BIA_MEMBER_OPERATOR_HPP_

#include <cstdint>

namespace bia {
namespace member {

enum class operator_ : std::uint8_t
{
	equal,
	not_equal,
	less,
	less_equal,
	greater,
	greater_equal,
	in,
	plus,
	minus,
	times,
	divide,
	power,
	modulo,
	bitwise_or,
	bitwise_and,
	bitwise_xor,
	bitwise_not,
	unary_minus,
};

} // namespace member
} // namespace bia

#endif
