#pragma once

#include <type_traits>

#include "biaMember.hpp"
#include "biaTypeTraits.hpp"
#include "biaException.hpp"
#include "biaDeclarations.hpp"


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
	typedef typename utility::NativeOperationResult<_LEFT, _RIGHT>::type return_type;

	switch (p_unOperator)
	{
	case BiaMember::O_ASSIGN:
		if (!_ALLOW_ASSIGN)
			break;

		return static_cast<return_type>(p_right);
	case BiaMember::O_ASSIGN_PLUS:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_PLUS:
		return static_cast<return_type>(p_left + p_right);
	case BiaMember::O_ASSIGN_MINUS:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_MINUS:
		return static_cast<return_type>(p_left - p_right);
	case BiaMember::O_ASSIGN_DIVIDE:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_DIVIDE:
		return static_cast<return_type>(p_left / p_right);
	case BiaMember::O_ASSIGN_MULTIPLY:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_MULTIPLY:
		return static_cast<return_type>(p_left * p_right);
	default:
		throw exception::OperatorException("Invalid operation on native type.");
	}

	throw exception::AccessViolationException("Assign operations are not allowed.");
}

template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
inline typename utility::NativeOperationResult<_LEFT, _RIGHT>::type IntegralOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	using namespace framework;
	typedef typename utility::NativeOperationResult<_LEFT, _RIGHT>::type return_type;

	switch (p_unOperator)
	{
	case BiaMember::O_ASSIGN_MODULUS:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_MODULUS:
		return static_cast<return_type>(p_left % p_right);
	case BiaMember::O_BITWISE_ASSIGN_OR:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_OR:
		return static_cast<return_type>(p_left | p_right);
	case BiaMember::O_BITWISE_ASSIGN_AND:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_AND:
		return static_cast<return_type>(p_left & p_right);
	case BiaMember::O_BITWISE_ASSIGN_XOR:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_XOR:
		return static_cast<return_type>(p_left ^ p_right);
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_ARITHMETIC_LEFT_SHIFT:
		return static_cast<return_type>(static_cast<typename utility::NativeOperationResult<_LEFT, _RIGHT>::type>(p_left) << p_right);
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
		return static_cast<return_type>(p_left >> p_right);
	case BiaMember::O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		if (!_ALLOW_ASSIGN)
			break;
	case BiaMember::O_BITWISE_LOGICAL_RIGHT_SHIFT:
		return static_cast<return_type>(static_cast<typename std::make_unsigned<_LEFT>::type>(p_left) >> p_right);
	default:
		return ArithmeticOperation<_ALLOW_ASSIGN>(p_left, p_right, p_unOperator);
	}

	throw exception::AccessViolationException("Assign operations are not allowed.");
}

template<bool _BOTH_INTEGRAL>
struct OperationTypeChooser
{
	template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
	inline static typename utility::NativeOperationResult<_LEFT, _RIGHT>::type Operation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
	{
		return IntegralOperation<_ALLOW_ASSIGN>(static_cast<typename utility::NativeTypeAdapter<_LEFT, true, sizeof(_LEFT)>::type>(p_left), p_right, p_unOperator);
	}
};

template<>
struct OperationTypeChooser<false>
{
	template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
	inline static typename utility::NativeOperationResult<_LEFT, _RIGHT>::type Operation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
	{
		return ArithmeticOperation<_ALLOW_ASSIGN>(static_cast<typename utility::NativeTypeAdapter<_LEFT, std::is_integral<_LEFT>::value, sizeof(_LEFT)>::type>(p_left), p_right, p_unOperator);
	}
};

template<typename _LEFT, typename _RIGHT>
using operation_type_chooser = OperationTypeChooser<std::is_integral<_LEFT>::value && std::is_integral<_RIGHT>::value>;


template<typename T, bool _ALLOW_ASSIGN, bool _INTEGRAL_REFERENCE>
struct OperationChooser
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		framework::MemberCreator(p_pDestination, operation_type_chooser<T, _RIGHT>::Operation<_ALLOW_ASSIGN>(p_left, p_right, p_unOperator));
	}
	template<typename _RIGHT>
	inline static void Operation(T & p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		p_left = static_cast<T>(operation_type_chooser<T, _RIGHT>::Operation<_ALLOW_ASSIGN>(p_left, p_right, p_unOperator));
	}
};

template<typename T>
struct OperationChooser<T, false, true>
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		operation_type_chooser<T, _RIGHT>::Operation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		operation_type_chooser<T, _RIGHT>::Operation<false>(p_left, p_right, p_unOperator);
	}
};

template<typename T, bool _ALLOW_ASSIGN>
struct OperationChooser<T, _ALLOW_ASSIGN, false>
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
};

template<typename T, bool _ALLOW_ASSIGN = utility::Negation<std::is_const<T>::value>::value>
using operation_chooser = OperationChooser<T, _ALLOW_ASSIGN, std::is_arithmetic<T>::value>;

}
}
}