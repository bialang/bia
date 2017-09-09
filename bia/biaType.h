#pragma once


namespace bia
{
namespace utility
{

template<typename T, T _VALUE>
struct BiaIntegralConstant
{
	constexpr static T VALUE = _VALUE;
};

template<typename T>
struct BiaHalf
{
};

template<>
struct BiaHalf<unsigned int>
{
	typedef unsigned short _HALF;
};

template<>
struct BiaHalf<unsigned long long>
{
	typedef unsigned int _HALF;
};

template<typename T>
struct BiaUpgrade
{
	typedef typename std::conditional<std::is_integral<T>::value, long long, T>::type upgrade;
};

template<>
struct BiaUpgrade<double>
{
	typedef double upgrade;
};

template<>
struct BiaUpgrade<float>
{
	typedef float upgrade;
};

template<typename T>
struct BiaPointerRank : BiaIntegralConstant<unsigned int, 0>
{
	typedef T _TYPE;
};

template<typename T>
struct BiaPointerRank<T*> : BiaIntegralConstant<unsigned int, BiaPointerRank<T>::VALUE + 1>
{
	using _TYPE = typename BiaPointerRank<T>::_TYPE;
};

template<typename T>
struct BiaPointerRank<T[]> : BiaIntegralConstant<unsigned int, BiaPointerRank<T>::VALUE>
{
	using _TYPE = typename BiaPointerRank<T>::_TYPE;
};

template<typename T, size_t _SIZE>
struct BiaPointerRank<T[_SIZE]> : BiaIntegralConstant<unsigned int, BiaPointerRank<T>::VALUE>
{
	using _TYPE = typename BiaPointerRank<T>::_TYPE;
};

template<typename T>
struct BiaFunctionTraits
{
	typedef void class_type;
	typedef void return_type;
	typedef void(*function_signature)();

	constexpr static bool IS_MEMBER_FUNCTION = false;
	constexpr static bool IS_FUNCTION = false;
	constexpr static size_t ARG_COUNT = 0;
};

template<typename _CLASS, typename _RETURN, typename... _ARGS>
struct BiaFunctionTraits<_RETURN(_CLASS::*)(_ARGS...) const>
{
	typedef _CLASS class_type;
	typedef _RETURN return_type;
	typedef _RETURN(_CLASS::*function_signature)(_ARGS...) const;

	constexpr static bool IS_MEMBER_FUNCTION = true;
	constexpr static bool IS_FUNCTION = true;
	constexpr static size_t ARG_COUNT = sizeof...(_ARGS);
};

template<typename _CLASS, typename _RETURN, typename... _ARGS>
struct BiaFunctionTraits<_RETURN(_CLASS::*)(_ARGS...)>
{
	typedef _CLASS class_type;
	typedef _RETURN return_type;
	typedef _RETURN(_CLASS::*function_signature)(_ARGS...);

	constexpr static bool IS_MEMBER_FUNCTION = true;
	constexpr static bool IS_FUNCTION = true;
	constexpr static size_t ARG_COUNT = sizeof...(_ARGS);
};

template<typename _RETURN, typename... _ARGS>
struct BiaFunctionTraits<_RETURN(*)(_ARGS...)>
{
	typedef void class_type;
	typedef _RETURN return_type;
	typedef _RETURN(*function_signature)(_ARGS...);

	constexpr static bool IS_MEMBER_FUNCTION = false;
	constexpr static bool IS_FUNCTION = true;
	constexpr static size_t ARG_COUNT = sizeof...(_ARGS);
};

template<typename T>
struct BiaLambdaTraits : BiaFunctionTraits<decltype(&T::operator())>
{
};

template<typename T>
struct BiaRefConverter
{
	typedef double* type;

	constexpr static bool CONVERTIBLE = false;
};

template<typename T>
struct BiaRefConverter<T*>
{
	typedef typename std::conditional<std::is_floating_point<T>::value || std::is_integral<T>::value || std::is_same<typename std::remove_cv<T>::type, std::string>::value, T*, double*>::type type;

	constexpr static bool CONVERTIBLE = std::is_floating_point<T>::value || std::is_integral<T>::value || std::is_same<typename std::remove_cv<T>::type, std::string>::value;
};

template<typename T>
struct BiaRefConverter<T&>
{
	typedef typename std::conditional<std::is_floating_point<T>::value || std::is_integral<T>::value || std::is_same<typename std::remove_cv<T>::type, std::string>::value, T*, double*>::type type;

	constexpr static bool CONVERTIBLE = std::is_floating_point<T>::value || std::is_integral<T>::value || std::is_same<typename std::remove_cv<T>::type, std::string>::value;
};

}
}