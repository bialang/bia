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

template<typename _Ty>
inline int32_t test_operation(_Ty _value)
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

template<typename _Ty>
inline int32_t test(_Ty _value)
{
	return test_operation(static_cast<typename utility::native_type_adapter<_Ty, std::is_integral<_Ty>::value, sizeof(_Ty)>::type>(_value));
}

template<typename _Left, typename _Right>
inline int32_t test_operation(_Left _left, uint32_t _operator, _Right _right)
{
	switch (_operator)
	{
	case O_EQUALS:
		return static_cast<int32_t>(_left == _right);
	case O_EQUALS_NOT:
		return static_cast<int32_t>(_left != _right);
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

template<bool _ARITHMETIC>
struct TestOperationChooser
{
	template<typename _Left, typename _Right>
	inline static int32_t Operation(_Left _left, uint32_t _operator, _Right _right)
	{
		return TestOperation(_left, _operator, _right);
	}
};

template<>
struct TestOperationChooser<false>
{
	template<typename _Left, typename _Right>
	inline static int32_t Operation(_Left _left, uint32_t _operator, _Right _right)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
};

template<typename _Ty>
using test_operation_chooser = TestOperationChooser<std::is_arithmetic<_Ty>::value>;

}
}
}