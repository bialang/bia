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
 * @tparam _Allow_assign ture if the left hand value can be modified.
 * @tparam _Left The left value type.
 * @tparam _Right The right value type.
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
template<bool _Allow_assign, typename _Left, typename _Right>
inline typename utility::native_operation_result<_Left, _Right>::type arithmetic_operation(_Left _left, operator_type _operator, _Right _right)
{
	typedef typename utility::native_operation_result<_Left, _Right>::type return_type;

	switch (_operator) {
	case O_ASSIGN:
		if (!_Allow_assign) {
			break;
		}

		return static_cast<return_type>(_right);
	case O_ASSIGN_PLUS:
		if (!_Allow_assign) {
			break;
		}
	case O_PLUS:
		return static_cast<return_type>(_left + _right);
	case O_ASSIGN_MINUS:
		if (!_Allow_assign) {
			break;
		}
	case O_MINUS:
		return static_cast<return_type>(_left - _right);
	case O_ASSIGN_DIVIDE:
		if (!_Allow_assign) {
			break;
		}
	case O_DIVIDE:
		return static_cast<return_type>(_left / _right);
	case O_ASSIGN_MULTIPLY:
		if (!_Allow_assign) {
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
 * @tparam _Allow_assign ture if the left hand value can be modified.
 * @tparam _Left The left value type.
 * @tparam _Right The right value type.
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
template<bool _Allow_assign, typename _Left, typename _Right>
inline typename utility::native_operation_result<_Left, _Right>::type integral_operation(_Left _left, operator_type _operator, _Right _right)
{
	typedef typename utility::native_operation_result<_Left, _Right>::type return_type;

	switch (_operator) {
	case O_ASSIGN_MODULUS:
		if (!_Allow_assign) {
			break;
		}
	case O_MODULUS:
		return static_cast<return_type>(_left % _right);
	case O_BITWISE_ASSIGN_OR:
		if (!_Allow_assign) {
			break;
		}
	case O_BITWISE_OR:
		return static_cast<return_type>(_left | _right);
	case O_BITWISE_ASSIGN_AND:
		if (!_Allow_assign) {
			break;
		}
	case O_BITWISE_AND:
		return static_cast<return_type>(_left & _right);
	case O_BITWISE_ASSIGN_XOR:
		if (!_Allow_assign) {
			break;
		}
	case O_BITWISE_XOR:
		return static_cast<return_type>(_left ^ _right);
	case O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		if (!_Allow_assign) {
			break;
		}
	case O_BITWISE_ARITHMETIC_LEFT_SHIFT:
		return static_cast<return_type>(static_cast<typename utility::native_operation_result<_Left, _Right>::type>(_left) << _right);
	case O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		if (!_Allow_assign) {
			break;
		}
	case O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
		return static_cast<return_type>(_left >> _right);
	case O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		if (!_Allow_assign) {
			break;
		}
	case O_BITWISE_LOGICAL_RIGHT_SHIFT:
		return static_cast<return_type>(static_cast<typename std::make_unsigned<_Left>::type>(_left) >> _right);
	default:
		return arithmetic_operation<_Allow_assign>(_left, _operator, _right);
	}

	throw exception::access_violation(BIA_EM_ASSIGN_ON_CONST);
}

template<bool _Both_integral>
struct operation_type_chooser;

template<>
struct operation_type_chooser<true>
{
	template<typename _Left, typename _Right>
	using result_type = typename utility::native_operation_result<_Left, _Right>::type;

	template<bool _Allow_assign, typename _Left, typename _Right>
	static result_type<_Left, _Right> operate(_Left _left, operator_type _operator, _Right _right)
	{
		return integral_operation<_Allow_assign>(static_cast<typename utility::native_type_adapter<_Left, true, sizeof(_Left)>::type>(_left), _operator, _right);
	}
};

template<>
struct operation_type_chooser<false>
{
	template<typename _Left, typename _Right>
	using result_type = typename utility::native_operation_result<_Left, _Right>::type;

	template<bool _Allow_assign, typename _Left, typename _Right>
	static result_type<_Left, _Right> operate(_Left _left, operator_type _operator, _Right _right)
	{
		return arithmetic_operation<_Allow_assign>(static_cast<typename utility::native_type_adapter<_Left, std::is_integral<_Left>::value, sizeof(_Left)>::type>(_left), _operator, _right);
	}
};

template<typename _Left, typename _Right>
using operation_type_chooser_lr = operation_type_chooser<(std::is_integral<_Left>::value && std::is_integral<_Right>::value)>;


template<typename _Ty, bool _Allow_assign>
struct operation_chooser;

template<typename _Ty>
struct operation_chooser<_Ty, true>
{
	template<typename _Right>
	using result_type = typename utility::native_operation_result<_Ty, _Right>::type;

	template<typename _Right>
	static result_type<_Right> operate_result(_Ty _left, operator_type _operator, _Right _right)
	{
		return operation_type_chooser_lr<_Ty, _Right>::template operate<true>(_left, _operator, _right);
	}
	template<typename _Right>
	static void operate(_Ty & _left, operator_type _operator, _Right _right)
	{
		_left = static_cast<_Ty>(operation_type_chooser_lr<_Ty, _Right>::template operate<true>(_left, _operator, _right));
	}
};

template<typename _Ty>
struct operation_chooser<_Ty, false>
{
	template<typename _Right>
	using result_type = typename utility::native_operation_result<_Ty, _Right>::type;

	template<typename _Right>
	static result_type<_Right> operate_result(_Ty _left, operator_type _operator, _Right _right)
	{
		return operation_type_chooser_lr<_Ty, _Right>::template operate<true>(_left, _operator, _right);
	}
	template<typename _Right>
	static void operate(_Ty _left, operator_type _operator, _Right _right)
	{
		operation_type_chooser_lr<_Ty, _Right>::template operate<false>(_left, _operator, _right);
	}
};

template<typename _Ty, bool _Allow_assign = utility::negation<std::is_const<_Ty>::value>::value>
using operation_chooser_l = operation_chooser<_Ty, _Allow_assign>;

}
}
}