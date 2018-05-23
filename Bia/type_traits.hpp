#pragma once

#include <type_traits>
#include <cstdint>
#include <cstddef>


namespace bia
{
namespace utility
{

template<bool _Value>
struct negation
{
	constexpr static bool value = false;
};

template<>
struct negation<false>
{
	constexpr static bool value = true;
};

template<typename _Left, typename _Right>
struct native_operation_result
{
	typedef typename std::conditional<std::is_arithmetic<_Left>::value && std::is_arithmetic<_Right>::value,
		typename std::conditional<std::is_same<_Right, double>::value,
		double,
		typename std::conditional<std::is_same<_Right, float>::value,
		float,
		typename std::conditional<sizeof(_Left) >= sizeof(_Right), _Left, _Right>::type>::type>::type, void*>::type type;
};

template<typename _Right>
struct native_operation_result<float, _Right>
{
	typedef typename std::conditional<std::is_same<double, _Right>::value, 
		double, 
		typename std::conditional<std::is_arithmetic<_Right>::value, float, void*>::type>::type type;
};

template<typename _Right>
struct native_operation_result<double, _Right>
{
	typedef typename std::conditional<std::is_arithmetic<_Right>::value, double, void*>::type type;
};

template<bool _Choose, typename _Return, typename _Ty>
struct chooser
{
};

template<typename _Return, typename _Ty>
struct chooser<true, _Return, _Ty>
{
	static _Return choose(_Ty _value) noexcept
	{
		return static_cast<_Return>(_value);
	}
};

template<typename _Return, typename _Ty>
struct chooser<false, _Return, _Ty>
{
	static _Return choose(_Ty _value) noexcept
	{
		return _Return();
	}
};

template<typename _Ty, bool _Integral, size_t _Size>
struct native_type_adapter
{
	typedef _Ty type;
};

template<typename _Ty>
struct native_type_adapter<_Ty, true, 8>
{
	typedef int64_t type;
};

template<typename _Ty>
struct native_type_adapter<_Ty, true, 4>
{
	typedef int32_t type;
};

template<typename _Ty>
struct native_type_adapter<_Ty, true, 2>
{
	typedef int32_t type;
};

template<typename _Ty>
struct native_type_adapter<_Ty, true, 1>
{
	typedef int32_t type;
};

}
}