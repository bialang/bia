#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "biaMember.hpp"
#include "biaException.hpp"
#include "biaMemberCreator.hpp"


namespace bia
{
namespace force
{

template<typename _RETURN>
inline _RETURN FormatCast(va_list & p_args, const char *& p_szFormat)
{
	switch (*p_szFormat++)
	{
	case 'i':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, int32_t>::type>(va_arg(p_args, int32_t));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'I':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, int64_t>::type>(va_arg(p_args, int64_t));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'f':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, float>::type>(va_arg(p_args, float));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'd':
	{
		constexpr auto NUMBER = std::is_integral<_RETURN>::value || std::is_floating_point<_RETURN>::value;

		if (NUMBER)
			return static_cast<std::conditional<NUMBER, _RETURN, double>::type>(va_arg(p_args, double));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 's':
	{
		if (std::is_same<_RETURN, const char*>::value)
			return reinterpret_cast<_RETURN>(va_arg(p_args, const char*));
		else
			throw exception::BadCastException("Invalid cast.");
	}
	case 'M':
	{
		if (auto pValue = va_arg(p_args, framework::BiaMember*)->Cast<_RETURN>())
			return *pValue;
		else
			throw exception::BadCastException("Invalid cast.");
	}
	default:
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
	}
}

inline void DisguisedCaller(void(*p_pFunction)(), framework::BiaMember * p_pDestination)
{
	p_pFunction();

	framework::MemberCreator(p_pDestination);
}

template<typename _RETURN>
inline void DisguisedCaller(_RETURN(*p_pFunction)(), framework::BiaMember * p_pDestination)
{
	framework::MemberCreator(p_pDestination, p_pFunction());
}

template<typename _RETURN, typename... _ARGS>
inline void DisguisedCaller(_RETURN(*)(_ARGS...), framework::BiaMember*)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _CLASS>
inline void DisguisedCaller(void(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS>
inline void DisguisedCaller(void(_CLASS::*p_pFunction)() const, _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCaller(_RETURN(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCaller(_RETURN(_CLASS::*p_pFunction)() const, _CLASS * p_pInstance, framework::BiaMember * p_pDestination)
{
	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS, typename... _ARGS>
inline void DisguisedCaller(_RETURN(_CLASS::*)(_ARGS...), _CLASS*, framework::BiaMember*)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _RETURN, typename _CLASS, typename... _ARGS>
inline void DisguisedCaller(_RETURN(_CLASS::*)(_ARGS...) const, _CLASS*, framework::BiaMember*)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _RETURN>
inline void DisguisedCallerCount(_RETURN(*p_pFunction)(), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	framework::MemberCreator(p_pDestination, p_pFunction());
}

template<typename _RETURN, typename _0>
inline void DisguisedCallerCount(_RETURN(*p_pFunction)(_0), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();

	framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(v0)));
}

template<typename _RETURN, typename _0, typename _1>
inline void DisguisedCallerCount(_RETURN(*p_pFunction)(_0, _1), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();

	framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _RETURN, typename _0, typename _1, typename _2>
inline void DisguisedCallerCount(_RETURN(*p_pFunction)(_0, _1, _2), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();
	_2 v2 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 2))->Cast<_2>();

	framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}


inline void DisguisedCallerCount(void(*p_pFunction)(), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	p_pFunction();

	framework::MemberCreator(p_pDestination);
}

template<typename _0>
inline void DisguisedCallerCount(void(*p_pFunction)(_0), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();

	p_pFunction(std::forward<_0>(v0));

	framework::MemberCreator(p_pDestination);
}

template<typename _0, typename _1>
inline void DisguisedCallerCount(void(*p_pFunction)(_0, _1), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();

	p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::MemberCreator(p_pDestination);
}

template<typename _0, typename _1, typename _2>
inline void DisguisedCallerCount(void(*p_pFunction)(_0, _1, _2), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();
	_2 v2 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 2))->Cast<_2>();

	p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(_0), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(_0, _1), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(_0, _1, _2), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();
	_2 v2 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 2))->Cast<_2>();

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)() const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(_0) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(_0, _1) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerCount(void(_CLASS::*p_pFunction)(_0, _1, _2) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();
	_2 v2 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 2))->Cast<_2>();

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::MemberCreator(p_pDestination);
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS, typename _0>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(_0), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(_0, _1), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(_0, _1, _2), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();
	_2 v2 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 2))->Cast<_2>();

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)() const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS, typename _0>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(_0) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(_0, _1) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerCount(_RETURN(_CLASS::*p_pFunction)(_0, _1, _2) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 0))->Cast<_0>();
	_1 v1 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 1))->Cast<_1>();
	_2 v2 = *(*reinterpret_cast<framework::BiaMember**>(p_args + sizeof(framework::BiaMember*) * 2))->Cast<_2>();

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _RETURN>
inline void DisguisedCallerFormat(_RETURN(*p_pFunction)(), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	framework::MemberCreator(p_pDestination, p_pFunction());
}

template<typename _RETURN, typename _0>
inline void DisguisedCallerFormat(_RETURN(*p_pFunction)(_0), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(v0)));
}

template<typename _RETURN, typename _0, typename _1>
inline void DisguisedCallerFormat(_RETURN(*p_pFunction)(_0, _1), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _RETURN, typename _0, typename _1, typename _2>
inline void DisguisedCallerFormat(_RETURN(*p_pFunction)(_0, _1, _2), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);
	_2 v2 = FormatCast<_2>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}


inline void DisguisedCallerFormat(void(*p_pFunction)(), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	p_pFunction();

	framework::MemberCreator(p_pDestination);
}

template<typename _0>
inline void DisguisedCallerFormat(void(*p_pFunction)(_0), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);

	p_pFunction(std::forward<_0>(v0));

	framework::MemberCreator(p_pDestination);
}

template<typename _0, typename _1>
inline void DisguisedCallerFormat(void(*p_pFunction)(_0, _1), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);

	p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::MemberCreator(p_pDestination);
}

template<typename _0, typename _1, typename _2>
inline void DisguisedCallerFormat(void(*p_pFunction)(_0, _1, _2), framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);
	_2 v2 = FormatCast<_2>(p_args, p_pcFormat);

	p_pFunction(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(_0), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(_0, _1), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(_0, _1, _2), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);
	_2 v2 = FormatCast<_2>(p_args, p_pcFormat);

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)() const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	(p_pInstance->*p_pFunction)();

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(_0) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(_0, _1) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::MemberCreator(p_pDestination);
}

template<typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerFormat(void(_CLASS::*p_pFunction)(_0, _1, _2) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);
	_2 v2 = FormatCast<_2>(p_args, p_pcFormat);

	(p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::MemberCreator(p_pDestination);
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS, typename _0>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(_0), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(_0, _1), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(_0, _1, _2), _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);
	_2 v2 = FormatCast<_2>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _RETURN, typename _CLASS>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)() const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 0)
		throw exception::ArgumentException("Argument count does not match.");


	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)());
}

template<typename _RETURN, typename _CLASS, typename _0>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(_0) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 1)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(_0, _1) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 2)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _RETURN, typename _CLASS, typename _0, typename _1, typename _2>
inline void DisguisedCallerFormat(_RETURN(_CLASS::*p_pFunction)(_0, _1, _2) const, const _CLASS * p_pInstance, framework::BiaMember * p_pDestination, framework::BiaMember::parameter_count p_count, const char * p_pcFormat, va_list p_args)
{
	if (p_count != 3)
		throw exception::ArgumentException("Argument count does not match.");

	_0 v0 = FormatCast<_0>(p_args, p_pcFormat);
	_1 v1 = FormatCast<_1>(p_args, p_pcFormat);
	_2 v2 = FormatCast<_2>(p_args, p_pcFormat);

	framework::MemberCreator(p_pDestination, (p_pInstance->*p_pFunction)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}


}
}