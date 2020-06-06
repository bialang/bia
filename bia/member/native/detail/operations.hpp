#ifndef BIA_MEMBER_NATIVE_OPERATIONS_HPP_
#define BIA_MEMBER_NATIVE_OPERATIONS_HPP_

#include "../../operator_.hpp"

#include <cmath>

namespace bia {
namespace member {
namespace native {
namespace detail {

template<typename Left, typename Right>
inline Left operation(Left left, infix_operator op, Right right)
{
	switch (op) {
	case infix_operator::bitwise_or: return left | right;
	case infix_operator::bitwise_xor: return left ^ right;
	case infix_operator::bitwise_and: return left & right;
	case infix_operator::equal: return left == right;
	case infix_operator::not_equal: return left != right;
	case infix_operator::less: return left < right;
	case infix_operator::less_equal: return left <= right;
	case infix_operator::greater: return left > right;
	case infix_operator::greater_equal: return left >= right;
	case infix_operator::in: return 0;
	case infix_operator::bitwise_left_shift: return left << right;
	case infix_operator::bitwise_right_shift: return left >> right;
	case infix_operator::addition: return left + right;
	case infix_operator::subtraction: return left - right;
	case infix_operator::multiplication: return left * right;
	case infix_operator::division: return left / right;
	case infix_operator::remainder: return left % right;
	case infix_operator::exponentation: return static_cast<Left>(pow(left, right));
	}
}

} // namespace detail
} // namespace native
} // namespace member
} // namespace bia

#endif
