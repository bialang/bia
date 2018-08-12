#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "member.hpp"
#include "allocator.hpp"
#include "exception.hpp"
#include "create_member.hpp"
#include "type_traits.hpp"
#include "machine_context.hpp"


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
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'I':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, int64_t>().choose(va_arg(_args, int64_t));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'd':
	{
		constexpr auto is_number = std::is_integral<_Return>::value || std::is_floating_point<_Return>::value;

		if (is_number) {
			return chooser<is_number, _Return, double>().choose(va_arg(_args, double));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'a':
	{
		constexpr auto is_string = std::is_same<_Return, const char*>::value;

		if (is_string) {
			return chooser<is_string, _Return, const char*>().choose(va_arg(_args, const char*));
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
		}
	}
	case 'M':
	{
		if (auto _ptr = va_arg(_args, framework::member*)->cast<_Return>()) {
			return *_ptr;
		} else {
			throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
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
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
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
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename _Return, typename _Class, typename... _Args>
inline void disguised_caller(_Return(_Class::*)(_Args...) const, const _Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename _Class>
inline machine::memory::allocation<_Class> disguised_caller()
{
	return machine::machine_context::active_allocator()->construct<_Class>();
}

template<typename _Class, typename... _Args>
inline typename std::enable_if<(sizeof...(_Args) > 0), machine::memory::allocation<_Class>>::type disguised_caller()
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename _Return>
inline void disguised_caller_count(_Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, _function());
}

template<typename _Return, typename _0>
inline void disguised_caller_count(_Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(*_v0));
}

template<typename _Return, typename _0, typename _1>
inline void disguised_caller_count(_Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(*_v0, *_v1));
}

template<typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(_Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(*_v0, *_v1, *_v2));
}


inline void disguised_caller_count(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_count(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	_function(*_v0);

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_count(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	_function(*_v0, *_v1);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	_function(*_v0, *_v1, *_v2);

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_count(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_count(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(*_v0));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(*_v0, *_v1));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(*_v0, *_v1, *_v2));
}

template<typename _Class>
inline void disguised_caller_count(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_count(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	(_instance->*_function)(*_v0);

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	(_instance->*_function)(*_v0, *_v1);

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	(_instance->*_function)(*_v0, *_v1, *_v2);

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_count(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_count(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(*_v0));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(*_v0, *_v1));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(*_v0, *_v1, *_v2));
}

template<typename _Class>
inline void disguised_caller_count(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_count(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	(_instance->*_function)(*_v0);

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	(_instance->*_function)(*_v0, *_v1);

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	(_instance->*_function)(*_v0, *_v1, *_v2);

	framework::create_member(_destination);
}

template<typename _Class>
inline machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	return machine::machine_context::active_allocator()->construct<_Class>();
}

template<typename _Class, typename _0>
inline machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<_Class>(*_v0);
}

template<typename _Class, typename _0, typename _1>
inline machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<_Class>(*_v0, *_v1);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = va_arg(_args, framework::member*)->cast<_2>();
	auto _v1 = va_arg(_args, framework::member*)->cast<_1>();
	auto _v0 = va_arg(_args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<_Class>(*_v0, *_v1, *_v2);
}

template<typename _Return>
inline void disguised_caller_format(_Return(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, _function());
}

template<typename _Return, typename _0>
inline void disguised_caller_format(_Return(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0)));
}

template<typename _Return, typename _0, typename _1>
inline void disguised_caller_format(_Return(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(_Return(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}


inline void disguised_caller_format(void(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_format(void(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_format(void(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_format(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_format(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0)));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename _Class>
inline void disguised_caller_format(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_format(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename _Class, typename _Return>
inline void disguised_caller_format(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename _Class, typename _Return, typename _0>
inline void disguised_caller_format(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0)));
}

template<typename _Class, typename _Return, typename _0, typename _1>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename _Class>
inline void disguised_caller_format(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename _Class, typename _0>
inline void disguised_caller_format(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename _Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename _Class>
inline machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	return machine::machine_context::active_allocator()->construct<_Class>();
}

template<typename _Class, typename _0>
inline machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<_Class>(std::forward<_0>(_v0));
}

template<typename _Class, typename _0, typename _1>
inline machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<_Class>(std::forward<_0>(_v0), std::forward<_1>(_v1));
}

template<typename _Class, typename _0, typename _1, typename _2>
inline machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	auto _v2 = format_cast<_2>(_args, _format);
	auto _v1 = format_cast<_1>(_args, _format);
	auto _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<_Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));
}

}
}