#pragma once

#include <type_traits>
#include <cstdint>

#include "operator.hpp"
#include "type_traits.hpp"
#include "exception.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename Type>
inline int32_t test_operation(Type _value)
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
}

inline int32_t test_operation(int32_t _value)
{
	return _value;
}

inline int32_t test_operation(int64_t _value)
{
	return reinterpret_cast<int32_t*>(&_value)[0] | reinterpret_cast<int32_t*>(&_value)[1];
}

inline int32_t test_operation(float _value)
{
	return static_cast<int32_t>(_value != 0.f);
}

inline int32_t test_operation(double _value)
{
	return static_cast<int32_t>(_value != 0.);
}

template<typename Type>
inline int32_t test(Type _value)
{
	return test_operation(static_cast<typename utility::native_type_adapter<Type, std::is_integral<Type>::value, sizeof(Type)>::type>(_value));
}

template<typename Left, typename Right>
inline int32_t test_operation(Left _left, uint32_t _operator, Right _right)
{
	switch (_operator)
	{
	case O_EQUALS:
		return static_cast<int32_t>(_left == _right);
	case O_EQUALS_NOT:
		return static_cast<int32_t>(_left != _right);
	/*case O_SAME:
		return static_cast<int32_t>(std::is_same<Left, Right>::value && _left == _right);
	case O_NOT_SAME:
		return static_cast<int32_t>(!std::is_same<Left, Right>::value || _left != _right);*/
	case O_LESS_THAN:
		return static_cast<int32_t>(_left < _right);
	case O_LESS_EQUALS:
		return static_cast<int32_t>(_left <= _right);
	case O_GREATER_THAN:
		return static_cast<int32_t>(_left > _right);
	case O_GREATER_EQUALS:
		return static_cast<int32_t>(_left >= _right);
	default:
		throw exception::operator_error(BIA_EM_UNSUPPORTED_OPERATOR);
	}
}

}
}
}
