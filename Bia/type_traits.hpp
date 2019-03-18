#pragma once

#include <type_traits>
#include <cstdint>
#include <cstddef>

#include "config.hpp"
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

template<typename T>
struct pointer_rank
{
	constexpr static size_t value = 0;
	constexpr static bool odd = false;
};

template<typename T>
struct pointer_rank<T*>
{
	constexpr static size_t value = pointer_rank<T>::value + 1;
	constexpr static bool odd = value % 2 != 0;
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

template<bool Value, bool... Rest>
struct all_true
{
private:
	template<bool V>
	constexpr static bool check() noexcept
	{
		return V;
	}
	template<bool V, bool... Rest>
	constexpr static typename std::enable_if<sizeof...(Rest), bool>::type check() noexcept
	{
		return V && check<Rest...>();
	}


public:
	constexpr static bool value = check<Value, Rest...>();
};

template<typename Type>
struct is_variant
{
	constexpr static bool value = false;
};

template<typename... Types>
struct is_variant<utility::variant<Types...>>
{
	constexpr static bool value = true;
};

template<typename Type>
struct type_transporter
{
	typedef Type type;
};

template<size_t Index, typename Type, typename... Types>
struct type_at : type_at<Index - 1, Types...>
{
};

template<typename Type, typename... Types>
struct type_at<0, Type, Types...>
{
	typedef Type type;
};

template<typename From, typename To>
struct is_promotable
{
	constexpr static bool value = (std::is_floating_point<From>::value && std::is_floating_point<To>::value || std::is_integral<From>::value && std::is_integral<To>::value) && sizeof(From) <= sizeof(To);
};

template<typename... Types>
struct type_container
{
};

}
}
