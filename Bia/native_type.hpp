#pragma once

#include <type_traits>


namespace bia
{
namespace framework
{
namespace native
{

enum class NATIVE_TYPE
{
	BOOL,
	INT_8,
	INT_16,
	INT_32,
	INT_64,
	FLOAT,
	DOUBLE,
	CONST_STRING,
	CUSTOM
};

template<typename _Ty, bool _Integral, size_t _Size>
struct native_type
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::CUSTOM;
};

template<>
struct native_type<bool, true, 1>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::BOOL;
};

template<typename _Ty>
struct native_type<_Ty, true, 1>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::INT_8;
};

template<typename _Ty>
struct native_type<_Ty, true, 2>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::INT_16;
};

template<typename _Ty>
struct native_type<_Ty, true, 4>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::INT_32;
};

template<typename _Ty>
struct native_type<_Ty, true, 8>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::INT_64;
};

template<>
struct native_type<float, false, sizeof(float)>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::FLOAT;
};

template<>
struct native_type<double, false, sizeof(double)>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::DOUBLE;
};

template<>
struct native_type<const char*, false, sizeof(const char*)>
{
	constexpr static NATIVE_TYPE type = NATIVE_TYPE::CONST_STRING;
};

template<typename _Ty>
constexpr NATIVE_TYPE determine_native_type() noexcept
{
	return native_type<_Ty, std::is_integral<_Ty>::value, sizeof(_Ty)>::type;
}

}
}
}