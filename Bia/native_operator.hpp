#pragma once

#include <type_traits>

#include "type_traits.hpp"
#include "operator.hpp"


namespace bia
{
namespace framework
{
namespace native
{

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
		throw exception::OperatorException("Invalid operation on native type.");
	}

	throw exception::AccessViolationException("Assign operations are not allowed.");
}

template<bool _Allow_assign, typename _Left, typename _Right>
inline typename utility::native_operation_result<_Left, _Right>::type IntegralOperation(_Left _left, operator_type _operator, _Right _right)
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

	throw exception::AccessViolationException("Assign operations are not allowed.");
}

template<bool _BOTH_INTEGRAL>
struct OperationTypeChooser
{
	template<bool _ALLOW_ASSIGN, typename _Left, typename _Right>
	inline static typename utility::native_operation_result<_Left, _Right>::type Operation(_Left _left, _Right _right, uint32_t p_unOperator)
	{
		return IntegralOperation<_ALLOW_ASSIGN>(static_cast<typename utility::NativeTypeAdapter<_Left, true, sizeof(_Left)>::type>(_left), _right, p_unOperator);
	}
};

template<>
struct OperationTypeChooser<false>
{
	template<bool _ALLOW_ASSIGN, typename _Left, typename _Right>
	inline static typename utility::native_operation_result<_Left, _Right>::type Operation(_Left _left, _Right _right, uint32_t p_unOperator)
	{
		return ArithmeticOperation<_ALLOW_ASSIGN>(static_cast<typename utility::NativeTypeAdapter<_Left, std::is_integral<_Left>::value, sizeof(_Left)>::type>(_left), _right, p_unOperator);
	}
};

template<typename _Left, typename _Right>
using operation_type_chooser = OperationTypeChooser<std::is_integral<_Left>::value && std::is_integral<_Right>::value>;


template<typename _Ty, bool _ALLOW_ASSIGN, bool _INTEGRAL_REFERENCE>
struct OperationChooser
{
	template<typename _Right>
	using type = typename utility::native_operation_result<_Ty, _Right>::type;

	template<typename _Right>
	inline static type<_Right> OperationResult(_Ty _left, uint32_t p_unOperator, _Right _right)
	{
		return operation_type_chooser<_Ty, _Right>::Operation<true>(_left, _right, p_unOperator);
	}
	template<typename _Right>
	inline static void Operation(_Ty & _left, uint32_t p_unOperator, _Right _right)
	{
		_left = static_cast<_Ty>(operation_type_chooser<_Ty, _Right>::Operation<true>(_left, _right, p_unOperator));
	}
};

template<typename _Ty>
struct OperationChooser<_Ty, false, true>
{
	template<typename _Right>
	using type = typename utility::native_operation_result<_Ty, _Right>::type;

	template<typename _Right>
	inline static type<_Right> OperationResult(_Ty _left, uint32_t p_unOperator, _Right _right)
	{
		return operation_type_chooser<_Ty, _Right>::Operation<true>(_left, _right, p_unOperator);
	}
	template<typename _Right>
	inline static void Operation(_Ty _left, uint32_t p_unOperator, _Right _right)
	{
		operation_type_chooser<_Ty, _Right>::Operation<false>(_left, _right, p_unOperator);
	}
};

template<typename _Ty, bool _ALLOW_ASSIGN>
struct OperationChooser<_Ty, _ALLOW_ASSIGN, false>
{
	template<typename _Right>
	using type = typename utility::native_operation_result<_Ty, _Right>::type;

	template<typename _Right>
	inline static type<_Right> OperationResult(_Ty _left, uint32_t p_unOperator, _Right _right)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
	template<typename _Right>
	inline static void Operation(_Ty _left, uint32_t p_unOperator, _Right _right)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
};

template<typename _Ty, bool _ALLOW_ASSIGN = utility::Negation<std::is_const<_Ty>::value>::value>
using operation_chooser = OperationChooser<_Ty, _ALLOW_ASSIGN, std::is_arithmetic<_Ty>::value>;

}
}
}