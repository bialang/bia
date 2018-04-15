#pragma once

#include <cstdint>
#include <type_traits>

#include "type_traits.hpp"
#include "exception.hpp"
#include "operator.hpp"


namespace bia
{
namespace compiler
{

template<typename _Left, typename _Right>
inline typename std::enable_if<std::is_integral<_Left>::value && std::is_integral<_Right>::value, typename utility::native_operation_result<_Left, _Right>::type>::type constant_operation(_Left _left, _Right _right, framework::OPERATOR _operator)
{
	using namespace framework;

	switch (_operator) {
	case O_PLUS:
	case O_ASSIGN_PLUS:
		return _left + _right;
	case O_MINUS:
	case O_ASSIGN_MINUS:
		return _left - _right;
	case O_DIVIDE:
	case O_ASSIGN_DIVIDE:
		return _left / _right;
	case O_MULTIPLY:
	case O_ASSIGN_MULTIPLY:
		return _left * _right;
	case O_MODULUS:
	case O_ASSIGN_MODULUS:
		return _left % _right;
	case O_BITWISE_OR:
	case O_BITWISE_ASSIGN_OR:
		return _left | _right;
	case O_BITWISE_AND:
	case O_BITWISE_ASSIGN_AND:
		return _left & _right;
	case O_BITWISE_XOR:
	case O_BITWISE_ASSIGN_XOR:
		return _left ^ _right;
	case O_BITWISE_ARITHMETIC_LEFT_SHIFT:
	case O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		return static_cast<typename utility::native_operation_result<_Left, _Right>::type>(_left) << _right;
	case O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
	case O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		return _left >> _right;
	case O_BITWISE_LOGICAL_RIGHT_SHIFT:
	case O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		return static_cast<typename std::make_unsigned<_Left>::type>(_left) >> _right;
	default:
		throw exception::operator_error();
	}
}

template<typename _Left, typename _Right>
inline typename std::enable_if<utility::negation<std::is_integral<_Left>::value && std::is_integral<_Right>::value>::value, typename utility::native_operation_result<_Left, _Right>::type>::type constant_operation(_Left _left, _Right _right, framework::OPERATOR _operator)
{
	using namespace framework;

	switch (_operator) {
	case O_PLUS:
	case O_ASSIGN_PLUS:
		return _left + _right;
	case O_MINUS:
	case O_ASSIGN_MINUS:
		return _left - _right;
	case O_DIVIDE:
	case O_ASSIGN_DIVIDE:
		return _left / _right;
	case O_MULTIPLY:
	case O_ASSIGN_MULTIPLY:
		return _left * _right;
	default:
		throw exception::operator_error();
	}
}

}
}