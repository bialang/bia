#pragma once

#include <cstdint>
#include <type_traits>

#include "biaMember.hpp"
#include "biaException.hpp"


namespace bia
{
namespace compiler
{

template<bool _VALUE>
struct Negation
{
	constexpr static bool value = false;
};

template<>
struct Negation<false>
{
	constexpr static bool value = true;
};

template<typename _LEFT, typename _RIGHT, typename _S= void>
struct OperationResult
{
	typedef typename std::conditional<sizeof(_LEFT) >= sizeof(_RIGHT), _LEFT, _RIGHT>::type type;
};

template<typename _RIGHT>
struct OperationResult<size_t, _RIGHT>
{
	typedef size_t type;
};

template<typename _LEFT>
struct OperationResult<_LEFT, size_t>
{
	typedef size_t type;
};

template<typename _RIGHT>
struct OperationResult<double, _RIGHT, typename std::enable_if<Negation<std::is_same<_RIGHT, size_t>::value>::value>::type>
{
	typedef double type;
};

template<typename _LEFT>
struct OperationResult<_LEFT, double, typename std::enable_if<Negation<std::is_same<_LEFT, size_t>::value || std::is_same<_LEFT, double>::value>::value>::type>
{
	typedef double type;
};

template<typename _RIGHT>
struct OperationResult<float, _RIGHT, typename std::enable_if<Negation<std::is_same<_RIGHT, size_t>::value || std::is_same<_RIGHT, double>::value>::value>::type>
{
	typedef float type;
};

template<typename _LEFT>
struct OperationResult<_LEFT, float, typename std::enable_if<Negation<std::is_same<_LEFT, size_t>::value || std::is_same<_LEFT, double>::value || std::is_same<_LEFT, float>::value>::value>::type>
{
	typedef float type;
};

template<typename _LEFT, typename _RIGHT>
inline typename OperationResult<_LEFT, _RIGHT>::type ConstantOperationBasic(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
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
inline typename OperationResult<_LEFT, _RIGHT>::type ConstantOperationIntegral(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
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
		return static_cast<OperationResult<_LEFT, _RIGHT>::type>(p_left) << p_right;
	case BiaMember::O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		return p_left >> p_right;
	case BiaMember::O_BITWISE_LOGICAL_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		return static_cast<std::make_unsigned<_LEFT>::type>(p_left) >> p_right;
	default:
		return ConstantOperationBasic(p_left, p_right, p_unOperator);
	}
}

}
}