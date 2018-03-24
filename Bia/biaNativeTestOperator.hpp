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
inline int32_t TestOperation(T)
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
	typedef typename utility::IntegralPromoter<T, std::is_integral<T>::value, sizeof(T)>::type type;

	return TestOperation(static_cast<type>(p_value));
}

template<typename _LEFT, typename _RIGHT>
inline int32_t TestOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
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

}
}
}