#pragma once

#include <type_traits>

#include "biaMember.hpp"
#include "biaTypeTraits.hpp"
#include "biaException.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
inline typename utility::NativeOperationResult<_LEFT, _RIGHT>::type ArithmeticOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	using namespace framework;

	switch (p_unOperator)
	{
	case BiaMember::O_ASSIGN:
		if (!_ALLOW_ASSIGN)
			break;

		return p_right;
	case BiaMember::O_ASSIGN_PLUS:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_PLUS:
		return p_left + p_right;
	case BiaMember::O_ASSIGN_MINUS:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_MINUS:
		return p_left - p_right;
	case BiaMember::O_ASSIGN_DIVIDE:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_DIVIDE:
		return p_left / p_right;
	case BiaMember::O_ASSIGN_MULTIPLY:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_MULTIPLY:
		return p_left * p_right;
	default:
		throw exception::OperatorException("Invalid operation on native type.");
	}

	throw exception::AccessViolationException("Assign operations are not allowed.");
}

template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
inline typename utility::NativeOperationResult<_LEFT, _RIGHT>::type IntegralOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	using namespace framework;

	switch (p_unOperator)
	{
	case BiaMember::O_ASSIGN_MODULUS:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_MODULUS:
		return p_left % p_right;
	case BiaMember::O_BITWISE_ASSIGN_OR:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_OR:
		return p_left | p_right;
	case BiaMember::O_BITWISE_ASSIGN_AND:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_AND:
		return p_left & p_right;
	case BiaMember::O_BITWISE_ASSIGN_XOR:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_XOR:
		return p_left ^ p_right;
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_ARITHMETIC_LEFT_SHIFT:
		return static_cast<typename utility::NativeOperationResult<_LEFT, _RIGHT>::type>(p_left) << p_right;
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
		return p_left >> p_right;
	case BiaMember::O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_LOGICAL_RIGHT_SHIFT:
		return static_cast<typename std::make_unsigned<_LEFT>::type>(p_left) >> p_right;
	default:
		return ArithmeticOperation<_ALLOW_ASSIGN>(p_left, p_right, p_unOperator);
	}

	throw exception::AccessViolationException("Assign operations are not allowed.");
}

template<bool _BOTH_INTEGRAL>
struct OperationTypeChooser
{
	template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
	inline static typename utility::NativeOperationResult<_LEFT, _RIGHT>::type ReferenceOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
	{
		return IntegralOperation<_ALLOW_ASSIGN>(static_cast<typename utility::NativeTypeAdapter<_LEFT, true, sizeof(_LEFT)>::type>(p_left), p_right, p_unOperator);
	}
};

template<>
struct OperationTypeChooser<false>
{
	template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
	inline static typename utility::NativeOperationResult<_LEFT, _RIGHT>::type ReferenceOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
	{
		return ArithmeticOperation<_ALLOW_ASSIGN>(static_cast<typename utility::NativeTypeAdapter<_LEFT, std::is_integral<_LEFT>::value, sizeof(_LEFT)>::type>(p_left), p_right, p_unOperator);
	}
};

}
}
}