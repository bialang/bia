#pragma once

#include <cstdint>
#include <type_traits>

#include "biaMember.hpp"
#include "biaTypeTraits.hpp"
#include "biaException.hpp"


namespace bia
{
namespace compiler
{

template<typename _LEFT, typename _RIGHT>
inline typename utility::NativeOperationResult<_LEFT, _RIGHT>::type ConstantOperationBasic(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	using namespace framework;

	switch (p_unOperator)
	{
	case BiaMember::O_PLUS:
	case BiaMember::O_ASSIGN_PLUS:
		return p_left + p_right;
	case BiaMember::O_MINUS:
	case BiaMember::O_ASSIGN_MINUS:
		return p_left - p_right;
	case BiaMember::O_DIVIDE:
	case BiaMember::O_ASSIGN_DIVIDE:
		return p_left / p_right;
	case BiaMember::O_MULTIPLY:
	case BiaMember::O_ASSIGN_MULTIPLY:
		return p_left * p_right;
	default:
		throw exception::OperatorException("Invalid operation on native type.");
	}
}

template<typename _LEFT, typename _RIGHT>
inline typename utility::NativeOperationResult<_LEFT, _RIGHT>::type ConstantOperationIntegral(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	using namespace framework;

	switch (p_unOperator)
	{
	case BiaMember::O_MODULUS:
	case BiaMember::O_ASSIGN_MODULUS:
		return p_left % p_right;
	case BiaMember::O_BITWISE_OR:
	case BiaMember::O_BITWISE_ASSIGN_OR:
		return p_left | p_right;
	case BiaMember::O_BITWISE_AND:
	case BiaMember::O_BITWISE_ASSIGN_AND:
		return p_left & p_right;
	case BiaMember::O_BITWISE_XOR:
	case BiaMember::O_BITWISE_ASSIGN_XOR:
		return p_left ^ p_right;
	case BiaMember::O_BITWISE_ARITHMETIC_LEFT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		return static_cast<typename utility::NativeOperationResult<_LEFT, _RIGHT>::type>(p_left) << p_right;
	case BiaMember::O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		return p_left >> p_right;
	case BiaMember::O_BITWISE_LOGICAL_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		return static_cast<typename std::make_unsigned<_LEFT>::type>(p_left) >> p_right;
	default:
		return ConstantOperationBasic(p_left, p_right, p_unOperator);
	}
}

}
}