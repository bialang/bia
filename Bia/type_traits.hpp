#pragma once

#include <type_traits>
#include <cstdint>
#include <cstddef>

#include "exception.hpp"


namespace bia
{
namespace utility
{

template<bool Value>
struct negation
{
	constexpr static bool value = false;
};

template<>
struct negation<false>
{
	constexpr static bool value = true;
};

template<typename Left, typename Right>
struct native_operation_result
{
	typedef typename std::conditional<std::is_arithmetic<Left>::value && std::is_arithmetic<Right>::value,
		typename std::conditional<std::is_same<Right, double>::value,
		double,
		typename std::conditional<std::is_same<Right, float>::value,
		float,
		typename std::conditional<sizeof(Left) >= sizeof(Right), Left, Right>::type>::type>::type, void*>::type type;
};

template<typename Right>
struct native_operation_result<float, Right>
{
	typedef typename std::conditional<std::is_same<double, Right>::value,
		double,
		typename std::conditional<std::is_arithmetic<Right>::value, float, void*>::type>::type type;
};

template<typename Right>
struct native_operation_result<double, Right>
{
	typedef typename std::conditional<std::is_arithmetic<Right>::value, double, void*>::type type;
};

template<bool _Choose, typename Return, typename Type>
struct chooser
{
};

template<typename Return, typename Type>
struct chooser<true, Return, Type>
{
	static Return choose(Type _value) noexcept
	{
		return checked_cast(_value);
	}

private:
	static Return checked_cast(Return _value) noexcept
	{
		return _value;
	}
	template<typename Ty>
	static Return checked_cast(Ty _value) noexcept
	{
		BIA_IMPLEMENTATION_ERROR;
	}
};

template<typename Return, typename Type>
struct chooser<false, Return, Type>
{
	static Return choose(Type _value)
	{
		BIA_IMPLEMENTATION_ERROR;
	}
};

template<typename Type, bool Is_integral, size_t Size>
struct native_type_adapter
{
	typedef Type type;
};

template<typename Type>
struct native_type_adapter<Type, true, 8>
{
	typedef int64_t type;
};

template<typename Type>
struct native_type_adapter<Type, true, 4>
{
	typedef int32_t type;
};

template<typename Type>
struct native_type_adapter<Type, true, 2>
{
	typedef int32_t type;
};

template<typename Type>
struct native_type_adapter<Type, true, 1>
{
	typedef int32_t type;
};

}
}
