#ifndef BIA_MEMBER_NATIVE_OPERATIONS_HPP_
#define BIA_MEMBER_NATIVE_OPERATIONS_HPP_

#include "../../member.hpp"
#include "../../operator_.hpp"

#include <bia/error/exception.hpp>
#include <cmath>
#include <type_traits>

namespace bia {
namespace member {
namespace native {
namespace detail {

template<typename Type>
inline typename std::enable_if<std::is_integral<Type>::value, Type>::type
    operation(Type left, Infix_operator op, Type right)
{
	switch (op) {
	case Infix_operator::bitwise_or: return left | right;
	case Infix_operator::bitwise_xor: return left ^ right;
	case Infix_operator::bitwise_and: return left & right;
	case Infix_operator::bitwise_left_shift: return left << right;
	case Infix_operator::bitwise_right_shift: return left >> right;
	case Infix_operator::addition: return left + right;
	case Infix_operator::subtraction: return left - right;
	case Infix_operator::multiplication: return left * right;
	case Infix_operator::division: return left / right;
	case Infix_operator::remainder: return left % right;
	case Infix_operator::exponentation: return static_cast<Type>(std::pow(left, right));
	default: BIA_THROW(bia::error::Code::bad_infix_operator);
	}
}

template<typename Type>
inline typename std::enable_if<std::is_floating_point<Type>::value, Type>::type
    operation(Type left, Infix_operator op, Type right)
{
	switch (op) {
	case Infix_operator::addition: return left + right;
	case Infix_operator::subtraction: return left - right;
	case Infix_operator::multiplication: return left * right;
	case Infix_operator::division: return left / right;
	case Infix_operator::remainder: return std::fmod(left, right);
	case Infix_operator::exponentation: return std::pow(left, right);
	default: BIA_THROW(bia::error::Code::bad_infix_operator);
	}
}

template<typename Type>
inline member::test_type test_operation(Type left, test_operator op, Type right)
{
	switch (op) {
	case test_operator::equal: return left == right;
	case test_operator::not_equal: return left != right;
	case test_operator::less: return left < right;
	case test_operator::less_equal: return left <= right;
	case test_operator::greater: return left > right;
	case test_operator::greater_equal: return left >= right;
	case test_operator::three_way_comparison: return left < right ? -1 : (left > right ? 1 : 0);
	default: BIA_THROW(bia::error::Code::bad_test_operator);
	}
}

} // namespace detail
} // namespace native
} // namespace member
} // namespace bia

#endif
