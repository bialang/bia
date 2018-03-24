#pragma once

#include <type_traits>


namespace bia
{
namespace utility
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

template<typename _LEFT, typename _RIGHT>
struct NativeOperationResult
{
	typedef typename std::conditional<std::is_arithmetic<_LEFT>::value && std::is_arithmetic<_RIGHT>::value,
		typename std::conditional<std::is_same<_RIGHT, double>::value,
		double,
		typename std::conditional<std::is_same<_RIGHT, float>::value,
		float,
		typename std::conditional<sizeof(_LEFT) >= sizeof(_RIGHT), _LEFT, _RIGHT>::type>::type>::type, void>::type type;
};

template<typename _RIGHT>
struct NativeOperationResult<float, _RIGHT>
{
	typedef typename std::conditional<std::is_same<double, _RIGHT>::value, 
		double, 
		typename std::conditional<std::is_arithmetic<_RIGHT>::value, float, void>::type>::type type;
};

template<typename _RIGHT>
struct NativeOperationResult<double, _RIGHT>
{
	typedef typename std::conditional<std::is_arithmetic<_RIGHT>::value, double, void>::type type;
};

template<bool _CHOOSE, typename, typename>
struct Chooser;

template<typename _RETURN, typename T>
struct Chooser<true, _RETURN, T>
{
	inline _RETURN Choose(T p_value)
	{
		return static_cast<_RETURN>(p_value);
	}
};

template<typename _RETURN, typename T>
struct Chooser<false, _RETURN, T>
{
	inline _RETURN Choose(T p_value)
	{
		return _RETURN();
	}
};

template<typename T, bool _INTEGRAL, size_t _SIZE>
struct IntegralPromoter
{
	typedef T type;
};

template<typename T>
struct IntegralPromoter<T, true, 8>
{
	typedef int64_t type;
};

template<typename T>
struct IntegralPromoter<T, true, 4>
{
	typedef int32_t type;
};

template<typename T>
struct IntegralPromoter<T, true, 2>
{
	typedef int32_t type;
};

template<typename T>
struct IntegralPromoter<T, true, 1>
{
	typedef int32_t type;
};

}
}