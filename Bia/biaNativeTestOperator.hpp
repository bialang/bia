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

template<typename T>
inline int32_t TestOperation(T p_value)
{
	throw exception::BadCallException("Type cannot be tested.");
}

inline int32_t TestOperation(int32_t p_nValue)
{
	return p_nValue;
}

inline int32_t TestOperation(int64_t p_llValue)
{
	return reinterpret_cast<int32_t*>(&p_llValue)[0] | reinterpret_cast<int32_t*>(&p_llValue)[1];
}

inline int32_t TestOperation(float p_rValue)
{
	return static_cast<int32_t>(p_rValue != 0.0f);
}

inline int32_t TestOperation(double p_rValue)
{
	return static_cast<int32_t>(p_rValue != 0.0);
}

template<typename T>
inline int32_t Test(T p_value)
{
	return TestOperation(static_cast<typename utility::NativeTypeAdapter<T, std::is_integral<T>::value, sizeof(T)>::type>(p_value));
}

template<typename _LEFT, typename _RIGHT>
inline int32_t TestOperation(_LEFT p_left, uint32_t p_unOperator, _RIGHT p_right)
{
	switch (p_unOperator)
	{
	case BiaMember::O_EQUALS:
		return static_cast<int32_t>(p_left == p_right);
	case BiaMember::O_EQUALS_NOT:
		return static_cast<int32_t>(p_left != p_right);
	case BiaMember::O_LESS_THAN:
		return static_cast<int32_t>(p_left < p_right);
	case BiaMember::O_LESS_EQUALS:
		return static_cast<int32_t>(p_left <= p_right);
	case BiaMember::O_GREATER_THAN:
		return static_cast<int32_t>(p_left > p_right);
	case BiaMember::O_GREATER_EQUALS:
		return static_cast<int32_t>(p_left >= p_right);
	default:
		throw exception::OperatorException("Invalid test operator.");
	}
}

template<bool _BOTH_ARITHMETIC>
struct TestOperationChooser
{
	template<typename _LEFT, typename _RIGHT>
	inline static int32_t Operation(_LEFT p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		return TestOperation(p_left, p_unOperator, p_right);
	}
};

template<>
struct TestOperationChooser<false>
{
	template<typename _LEFT, typename _RIGHT>
	inline static int32_t Operation(_LEFT p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
};

template<typename T>
using test_operation_chooser = TestOperationChooser<std::is_arithmetic<T>::value>;

}
}
}