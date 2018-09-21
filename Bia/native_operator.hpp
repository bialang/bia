#pragma once

#include <type_traits>

#include "type_traits.hpp"
#include "operator.hpp"
#include "exception.hpp"


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
inline typename utility::native_operation_result<Left, Right>::type arithmetic_operation(Left _left, operator_type _operator, Right _right)
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
inline typename utility::native_operation_result<Left, Right>::type integral_operation(Left _left, operator_type _operator, Right _right)
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

template<bool _Both_integral>
struct operation_type_chooser;

template<>
struct operation_type_chooser<true>
{
	template<typename Left, typename Right>
	using result_type = typename utility::native_operation_result<Left, Right>::type;

	template<bool Allow_assign, typename Left, typename Right>
	static result_type<Left, Right> operate(Left _left, operator_type _operator, Right _right)
	{
		return integral_operation<Allow_assign>(static_cast<typename utility::native_type_adapter<Left, true, sizeof(Left)>::type>(_left), _operator, _right);
	}
};

template<>
struct operation_type_chooser<false>
{
	template<typename Left, typename Right>
	using result_type = typename utility::native_operation_result<Left, Right>::type;

	template<bool Allow_assign, typename Left, typename Right>
	static result_type<Left, Right> operate(Left _left, operator_type _operator, Right _right)
	{
		return arithmetic_operation<Allow_assign>(static_cast<typename utility::native_type_adapter<Left, std::is_integral<Left>::value, sizeof(Left)>::type>(_left), _operator, _right);
	}
};

template<typename Left, typename Right>
using operation_type_chooser_lr = operation_type_chooser<(std::is_integral<Left>::value && std::is_integral<Right>::value)>;


template<typename Type, bool Allow_assign>
struct operation_chooser;

template<typename Type>
struct operation_chooser<Type, true>
{
	template<typename Right>
	using result_type = typename utility::native_operation_result<Type, Right>::type;

	template<typename Right>
	static result_type<Right> operate_result(Type _left, operator_type _operator, Right _right)
	{
		return operation_type_chooser_lr<Type, Right>::template operate<true>(_left, _operator, _right);
	}
	template<typename Right>
	static void operate(Type & _left, operator_type _operator, Right _right)
	{
		_left = static_cast<Type>(operation_type_chooser_lr<Type, Right>::template operate<true>(_left, _operator, _right));
	}
};

template<typename Type>
struct operation_chooser<Type, false>
{
	template<typename Right>
	using result_type = typename utility::native_operation_result<Type, Right>::type;

	template<typename Right>
	static result_type<Right> operate_result(Type _left, operator_type _operator, Right _right)
	{
		return operation_type_chooser_lr<Type, Right>::template operate<true>(_left, _operator, _right);
	}
	template<typename Right>
	static void operate(Type _left, operator_type _operator, Right _right)
	{
		operation_type_chooser_lr<Type, Right>::template operate<false>(_left, _operator, _right);
	}
};

template<typename Type, bool Allow_assign = utility::negation<std::is_const<Type>::value>::value>
using operation_chooser_l = operation_chooser<Type, Allow_assign>;

}
}
}
