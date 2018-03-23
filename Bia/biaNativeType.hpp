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
	INT_8,
	CONST_INT_8,
	INT_16,
	CONST_INT_16,
	INT_32,
	CONST_INT_32,
	INT_64,
	CONST_INT_64,
	FLOAT,
	CONST_FLOAT,
	DOUBLE,
	CONST_DOUBLE,
	CONST_STRING,
	CUSTOM
};

template<typename T, bool _INTEGRAL, bool _CONST, size_t _SIZE>
struct NativeType
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_STRING;
	}
};

template<typename T>
struct NativeType<T, true, true, 1>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_INT_8;
	}
};

template<typename T>
struct NativeType<T, true, false, 1>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::INT_8;
	}
};

template<typename T>
struct NativeType<T, true, true, 2>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_INT_16;
	}
};

template<typename T>
struct NativeType<T, true, false, 2>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::INT_16;
	}
};

template<typename T>
struct NativeType<T, true, true, 4>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_INT_32;
	}
};

template<typename T>
struct NativeType<T, true, false, 4>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::INT_32;
	}
};

template<typename T>
struct NativeType<T, true, true, 8>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_INT_64;
	}
};

template<typename T>
struct NativeType<T, true, false, 8>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::INT_64;
	}
};

template<size_t _SIZE>
struct NativeType<float, false, true, _SIZE>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_FLOAT;
	}
};

template<size_t _SIZE>
struct NativeType<float, false, false, _SIZE>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::FLOAT;
	}
};

template<size_t _SIZE>
struct NativeType<double, false, true, _SIZE>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_DOUBLE;
	}
};

template<size_t _SIZE>
struct NativeType<double, false, false, _SIZE>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::DOUBLE;
	}
};

template<bool _INTEGRAL, bool _CONST, size_t _SIZE>
struct NativeType<const char*, _INTEGRAL, _CONST, _SIZE>
{
	inline constexpr static NATIVE_TYPE Type()
	{
		return NATIVE_TYPE::CONST_STRING;
	}
};

template<typename T>
inline constexpr NATIVE_TYPE DetermineNativeType()
{
	return NativeType<T, std::is_integral<T>::value, std::is_const<T>::value, sizeof(T)>::Type();
}

}
}
}