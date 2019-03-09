#pragma once

#include "type_traits.hpp"
#include "operator.hpp"
#include "exception.hpp"
#include "member.hpp"
#include "create_member.hpp"


namespace bia
{
namespace framework
{
namespace native
{

/**
 * Executes the operator for the left and right value.
 *
 * @remarks If both operands are of integral type, use integral_operation().
 *
 * @since 3.64.127.716
 * @date 6-May-18
 *
 * @tparam Allow_assign ture if the left hand value can be modified.
 * @tparam Left The left value type.
 * @tparam Right The right value type.
 *
 * @param _left The left hand value.
 * @param _operator The operator.
 * @param _right The right hand value.
 *
 * @throws exception::operator_error The given operator is unkown or invalid.
 * @throws exception::access_violation The left hand value is immutable.
 *
 * @return The result of the operation.
*/
template<bool Allow_assign, typename Left, typename Right>
inline typename utility::native_operation_result<Left, Right>::type arithmetic_operation(Left _left, operator_t _operator, Right _right)
{
	typedef typename utility::native_operation_result<Left, Right>::type return_type;

	switch (_operator) {
	case O_ASSIGN:
		if (!Allow_assign) {
			break;
		}

		return static_cast<return_type>(_right);
	case O_ASSIGN_PLUS:
		if (!Allow_assign) {
			break;
		}
	case O_PLUS:
		return static_cast<return_type>(_left + _right);
	case O_ASSIGN_MINUS:
		if (!Allow_assign) {
			break;
		}
	case O_MINUS:
		return static_cast<return_type>(_left - _right);
	case O_ASSIGN_DIVIDE:
		if (!Allow_assign) {
			break;
		}
	case O_DIVIDE:
		return static_cast<return_type>(_left / _right);
	case O_ASSIGN_MULTIPLY:
		if (!Allow_assign) {
			break;
		}
	case O_MULTIPLY:
		return static_cast<return_type>(_left * _right);
	default:
		throw exception::operator_error(BIA_EM_UNSUPPORTED_OPERATOR);
	}

	throw exception::access_violation(BIA_EM_ASSIGN_ON_CONST);
}

/**
 * Executes the operator for the left and right value.
 *
 * @remarks If one of the operands is a floating point value, use arithmetic_operation().
 *
 * @since 3.64.127.716
 * @date 6-May-18
 *
 * @tparam Allow_assign ture if the left hand value can be modified.
 * @tparam Left The left value type.
 * @tparam Right The right value type.
 *
 * @param _left The left hand value.
 * @param _operator The operator.
 * @param _right The right hand value.
 *
 * @throws See arithmetic_operation().
 * @throws exception::access_violation The left hand value is immutable.
 *
 * @return The result of the operation.
*/
template<bool Allow_assign, typename Left, typename Right>
inline typename utility::native_operation_result<Left, Right>::type integral_operation(Left _left, operator_t _operator, Right _right)
{
	typedef typename utility::native_operation_result<Left, Right>::type return_type;

	switch (_operator) {
	case O_ASSIGN_MODULUS:
		if (!Allow_assign) {
			break;
		}
	case O_MODULUS:
		return static_cast<return_type>(_left % _right);
	case O_BITWISE_ASSIGN_OR:
		if (!Allow_assign) {
			break;
		}
	case O_BITWISE_OR:
		return static_cast<return_type>(_left | _right);
	case O_BITWISE_ASSIGN_AND:
		if (!Allow_assign) {
			break;
		}
	case O_BITWISE_AND:
		return static_cast<return_type>(_left & _right);
	case O_BITWISE_ASSIGN_XOR:
		if (!Allow_assign) {
			break;
		}
	case O_BITWISE_XOR:
		return static_cast<return_type>(_left ^ _right);
	case O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		if (!Allow_assign) {
			break;
		}
	case O_BITWISE_ARITHMETIC_LEFT_SHIFT:
		return static_cast<return_type>(static_cast<typename utility::native_operation_result<Left, Right>::type>(_left) << _right);
	case O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		if (!Allow_assign) {
			break;
		}
	case O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
		return static_cast<return_type>(_left >> _right);
	case O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		if (!Allow_assign) {
			break;
		}
	case O_BITWISE_LOGICAL_RIGHT_SHIFT:
		return static_cast<return_type>(static_cast<typename std::make_unsigned<Left>::type>(_left) >> _right);
	default:
		return arithmetic_operation<Allow_assign>(_left, _operator, _right);
	}

	throw exception::access_violation(BIA_EM_ASSIGN_ON_CONST);
}


template<bool Allow_assign>
struct native_operation
{
	template<typename Left, typename Right>
	static void operate_integral(Left & _left, operator_t _operator, Right _right, bool _allow_assign = true)
	{
		if (_allow_assign) {
			_left = static_cast<Left>(integral_operation<true>(_left, _operator, _right));
		} else {
			integral_operation<false>(_left, _operator, _right);
		}
	}
	template<typename Left, typename Right>
	static void operate_integral(member * _destination, Left _left, operator_t _operator, Right _right)
	{
		create_member(_destination, integral_operation<true>(_left, _operator, _right));
	}
	template<typename Left, typename Right>
	static void operate_arithmetic(Left & _left, operator_t _operator, Right _right, bool _allow_assign = true)
	{
		if (_allow_assign) {
			_left = static_cast<Left>(arithmetic_operation<true>(_left, _operator, _right));
		} else {
			arithmetic_operation<false>(_left, _operator, _right);
		}
	}
	template<typename Left, typename Right>
	static void operate_arithmetic(member * _destination, Left _left, operator_t _operator, Right _right)
	{
		create_member(_destination, arithmetic_operation<true>(_left, _operator, _right));
	}
};

template<>
struct native_operation<false>
{
	template<typename Left, typename Right>
	static void operate_integral(Left _left, operator_t _operator, Right _right)
	{
		integral_operation<false>(_left, _operator, _right);
	}
	template<typename Left, typename Right>
	static void operate_integral(member * _destination, Left _left, operator_t _operator, Right _right)
	{
		create_member(_destination, integral_operation<false>(_left, _operator, _right));
	}
	template<typename Left, typename Right>
	static void operate_arithmetic(Left _left, operator_t _operator, Right _right)
	{
		arithmetic_operation<false>(_left, _operator, _right);
	}
	template<typename Left, typename Right>
	static void operate_arithmetic(member * _destination, Left _left, operator_t _operator, Right _right)
	{
		create_member(_destination, arithmetic_operation<false>(_left, _operator, _right));
	}
};

}
}
}
