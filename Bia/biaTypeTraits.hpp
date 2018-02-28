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

template<typename _LEFT, typename _RIGHT, typename _S = void>
struct OperationResult
{
	typedef typename std::conditional<sizeof(_LEFT) >= sizeof(_RIGHT), _LEFT, _RIGHT>::type type;
};

template<typename _RIGHT>
struct OperationResult<size_t, _RIGHT>
{
	typedef size_t type;
};

template<typename _LEFT>
struct OperationResult<_LEFT, size_t>
{
	typedef size_t type;
};

template<typename _RIGHT>
struct OperationResult<double, _RIGHT, typename std::enable_if<Negation<std::is_same<_RIGHT, size_t>::value>::value>::type>
{
	typedef double type;
};

template<typename _LEFT>
struct OperationResult<_LEFT, double, typename std::enable_if<Negation<std::is_same<_LEFT, size_t>::value || std::is_same<_LEFT, double>::value>::value>::type>
{
	typedef double type;
};

template<typename _RIGHT>
struct OperationResult<float, _RIGHT, typename std::enable_if<Negation<std::is_same<_RIGHT, size_t>::value || std::is_same<_RIGHT, double>::value>::value>::type>
{
	typedef float type;
};

template<typename _LEFT>
struct OperationResult<_LEFT, float, typename std::enable_if<Negation<std::is_same<_LEFT, size_t>::value || std::is_same<_LEFT, double>::value || std::is_same<_LEFT, float>::value>::value>::type>
{
	typedef float type;
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

}
}