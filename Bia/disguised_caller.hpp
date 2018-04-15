#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "member.hpp"
#include "exception.hpp"
#include "create_member.hpp"
#include "type_traits.hpp"


namespace bia
{
namespace force
{

template<typename _Return>
inline _Return format_cast(va_list & _args, const char *& _format)
{
	using namespace utility;

	switch (*_format++)
	{
	case 'i':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, int32_t>::choose(va_arg(_args, int32_t));
		} else {
			throw exception::BadCastException("Invalid cast.");
		}
	}
	case 'I':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, int64_t>().choose(va_arg(_args, int64_t));
		} else {
			throw exception::BadCastException("Invalid cast.");
		}
	}
	case 'f':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, float>().choose(va_arg(_args, float));
		} else {
			throw exception::BadCastException("Invalid cast.");
		}
	}
	case 'd':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, double>().choose(va_arg(_args, double));
		} else {
			throw exception::BadCastException("Invalid cast.");
		}
	}
	case 's':
	{
		constexpr auto is_string = std::is_same<_Return, const char*>::value;

		if (is_string) {
			return chooser<is_string, _Return, const char*>().choose(va_arg(_args, const char*));
		} else {
			throw exception::BadCastException("Invalid cast.");
		}
	}
	case 'M':
	{
		if (auto _ptr = va_arg(_args, framework::member*)->cast<_Return>()) {
			return *_ptr;
		} else {
			throw exception::BadCastException("Invalid cast.");
		}
	}
	default:
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
	}
}

inline void disguised_caller(void(*_function)(), framework::member * _destination)
{
	_function();

	framework::create_member(_destination);
}

template<typename _Return>
inline void disguised_caller(_Return(*_function)(), framework::member * _destination)
{
	framework::create_member(_destination, _function());
}

template<typename _Return, typename... _Args>
inline void disguised_caller(_Return(*)(_Args...), framework::member * _destination)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _Class>
inline void disguised_caller(void(_Class::*_function)(), _Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class>
inline void disguised_caller(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Return, typename _Class>
inline void disguised_caller(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Return, typename _Class>
inline void disguised_caller(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Return, typename _Class, typename... _Args>
inline void disguised_caller(_Return(_Class::*)(_Args...), _Class * _instance, framework::member * _destination)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _Return, typename _Class, typename... _Args>
inline void disguised_caller(_Return(_Class::*)(_Args...) const, const _Class * _instance, framework::member * _destination)
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _Class>
inline _Class * disguised_caller()
{
	return new _Class();
}

template<typename _Class, typename... _Args>
inline _Class * disguised_caller()
{
	throw exception::ArgumentException("Arguments expected.");
}

template<typename _Return>
inline void disguised_caller_count(_Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	framework::create_member(_destination, _function());
}

template<typename _Return, typename _0>
inline void disguised_caller_count(_Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	framework::create_member(_destination, _function(std::forward<_0>(v0)));
}

template<typename _Return, typename _0, typename _1>
inline void disguised_caller_count(_Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	framework::create_member(_destination, _function(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(_Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	framework::create_member(_destination, _function(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}


inline void disguised_caller_count(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_count(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	_function(std::forward<_0>(v0));

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_count(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	_function(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	_function(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_count(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_count(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0)));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _Class>
inline void disguised_caller_count(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_count(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	(_instance->*_function)(std::forward<_0>(v0));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_count(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_count(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0)));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _Class>
inline void disguised_caller_count(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_count(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	(_instance->*_function)(std::forward<_0>(v0));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::create_member(_destination);
}

template<typename _Class>
inline _Class * disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	return new _Class();
}

template<typename _Class, typename _0>
inline _Class * disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_0>();

	return new _Class(std::forward<_0>(v0));
}

template<typename _Class, typename _0, typename _1>
inline _Class * disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_0>();

	return new _Class(std::forward<_0>(v0), std::forward<_1>(v1));
}

template<typename _Class, typename _0, typename _1, typename _2>
inline _Class * disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 0))->cast<_2>();
	auto v1 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 1))->cast<_1>();
	auto v0 = *(*reinterpret_cast<framework::member**>(_args + sizeof(framework::member*) * 2))->cast<_0>();

	return new _Class(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));
}

template<typename _Return>
inline void disguised_caller_format(_Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	framework::create_member(_destination, _function());
}

template<typename _Return, typename _0>
inline void disguised_caller_format(_Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, _function(std::forward<_0>(v0)));
}

template<typename _Return, typename _0, typename _1>
inline void disguised_caller_format(_Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, _function(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(_Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, _function(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}


inline void disguised_caller_format(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_format(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	_function(std::forward<_0>(v0));

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_format(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	_function(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	_function(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_format(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_format(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0)));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _Class>
inline void disguised_caller_format(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_format(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	(_instance->*_function)(std::forward<_0>(v0));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_format(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_format(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0)));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1)));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2)));
}

template<typename _Class>
inline void disguised_caller_format(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_format(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	(_instance->*_function)(std::forward<_0>(v0));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	(_instance->*_function)(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));

	framework::create_member(_destination);
}

template<typename _Class>
inline _Class * disguised_caller_format(framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 0) {
		throw exception::ArgumentException("Argument count does not match.");
	}

	return new _Class();
}

template<typename _Class, typename _0>
inline _Class * disguised_caller_format(framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 1) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	return new _Class(std::forward<_0>(v0));
}

template<typename _Class, typename _0, typename _1>
inline _Class * disguised_caller_format(framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 2) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	return new _Class(std::forward<_0>(v0), std::forward<_1>(v1));
}

template<typename _Class, typename _0, typename _1, typename _2>
inline _Class * disguised_caller_format(framework::member::parameter_count _count, const char * _format, va_list _args)
{
	if (_count != 3) {
		throw exception::ArgumentException("Argument count does not match.");
	}
	auto v2 = format_cast<_2>(_args, p_pcFormat);
	auto v1 = format_cast<_1>(_args, p_pcFormat);
	auto v0 = format_cast<_0>(_args, p_pcFormat);

	return new _Class(std::forward<_0>(v0), std::forward<_1>(v1), std::forward<_2>(v2));
}

}
}