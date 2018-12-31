#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "disguised_caller.hpp"
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

template<typename Return>
inline Return format_cast(va_list_wrapper & _args, const char *& _format)
{
	using namespace utility;
	using Real_return = typename std::remove_reference<Return>::type;

gt_redo:;

	switch (*_format++)
	{
	case 'i':
	{
		constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

		if (is_number) {
			return chooser<is_number, Return, int32_t>::choose(va_arg(_args.args, int32_t));
		} else {
			break;
		}
	}
	case 'I':
	{
		constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

		if (is_number) {
			return chooser<is_number, Return, int64_t>().choose(va_arg(_args.args, int64_t));
		} else {
			break;
		}
	}
	case 'd':
	{
		constexpr auto is_number = std::is_integral<Real_return>::value || std::is_floating_point<Real_return>::value;

		if (is_number) {
			auto _value = va_arg(_args.args, int64_t);

			return chooser<is_number, Return, double>().choose(*reinterpret_cast<double*>(&_value));
		} else {
			break;
		}
	}
	case 'a':
	{
		constexpr auto is_string = std::is_same<Real_return, const char*>::value;

		if (is_string) {
			return chooser<is_string, Return, const char*>().choose(va_arg(_args.args, const char*));
		} else {
			break;
		}
	}
	case 'M':
		return va_arg(_args.args, framework::member*)->cast<Return>();
	case 'r':
		va_arg(_args.args, void*);

		goto gt_redo;
	default:
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid format type.");
	}

	throw exception::type_error(BIA_EM_UNEXPECTED_TYPE);
}

inline void disguised_caller(void(*_function)(), framework::member * _destination)
{
	_function();

	framework::create_member(_destination);
}

template<typename Return>
inline void disguised_caller(Return(*_function)(), framework::member * _destination)
{
	framework::create_member(_destination, _function());
}

template<typename Return, typename... Arguments>
inline void disguised_caller(Return(*)(Arguments...), framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Class>
inline void disguised_caller(void(Class::*_function)(), Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class>
inline void disguised_caller(void(Class::*_function)() const, const Class * _instance, framework::member * _destination)
{
	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Return, typename Class>
inline void disguised_caller(Return(Class::*_function)(), Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Return, typename Class>
inline void disguised_caller(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination)
{
	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Return, typename Class, typename... Arguments>
inline void disguised_caller(Return(Class::*)(Arguments...), Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Return, typename Class, typename... Arguments>
inline void disguised_caller(Return(Class::*)(Arguments...) const, const Class * _instance, framework::member * _destination)
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Class>
inline machine::memory::allocation<Class> disguised_caller()
{
	return machine::machine_context::active_allocator()->construct<Class>();
}

template<typename Class, typename... Arguments>
inline typename std::enable_if<(sizeof...(Arguments) > 0), machine::memory::allocation<Class>>::type disguised_caller()
{
	throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
}

template<typename Return>
inline void disguised_caller_count(Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, _function());
}

template<typename Return, typename _0>
inline void disguised_caller_count(Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0));
}

template<typename Return, typename _0, typename _1>
inline void disguised_caller_count(Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1));
}

template<typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19));
}


inline void disguised_caller_count(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_count(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0);

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_count(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_count(Return(Class::*_function)(), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_count(Return(Class::*_function)(_0), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19));
}

template<typename Class>
inline void disguised_caller_count(void(Class::*_function)(), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_count(void(Class::*_function)(_0), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_count(void(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_count(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_count(Return(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19));
}

template<typename Class>
inline void disguised_caller_count(void(Class::*_function)() const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_count(void(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_count(void(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);

	framework::create_member(_destination);
}

template<typename Class>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	return machine::machine_context::active_allocator()->construct<Class>();
}

template<typename Class, typename _0>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0);
}

template<typename Class, typename _0, typename _1>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1);
}

template<typename Class, typename _0, typename _1, typename _2>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	framework::converter<_19>::type _v19 = va_arg(_args.args, framework::member*)->cast<_19>();
	framework::converter<_18>::type _v18 = va_arg(_args.args, framework::member*)->cast<_18>();
	framework::converter<_17>::type _v17 = va_arg(_args.args, framework::member*)->cast<_17>();
	framework::converter<_16>::type _v16 = va_arg(_args.args, framework::member*)->cast<_16>();
	framework::converter<_15>::type _v15 = va_arg(_args.args, framework::member*)->cast<_15>();
	framework::converter<_14>::type _v14 = va_arg(_args.args, framework::member*)->cast<_14>();
	framework::converter<_13>::type _v13 = va_arg(_args.args, framework::member*)->cast<_13>();
	framework::converter<_12>::type _v12 = va_arg(_args.args, framework::member*)->cast<_12>();
	framework::converter<_11>::type _v11 = va_arg(_args.args, framework::member*)->cast<_11>();
	framework::converter<_10>::type _v10 = va_arg(_args.args, framework::member*)->cast<_10>();
	framework::converter<_9>::type _v9 = va_arg(_args.args, framework::member*)->cast<_9>();
	framework::converter<_8>::type _v8 = va_arg(_args.args, framework::member*)->cast<_8>();
	framework::converter<_7>::type _v7 = va_arg(_args.args, framework::member*)->cast<_7>();
	framework::converter<_6>::type _v6 = va_arg(_args.args, framework::member*)->cast<_6>();
	framework::converter<_5>::type _v5 = va_arg(_args.args, framework::member*)->cast<_5>();
	framework::converter<_4>::type _v4 = va_arg(_args.args, framework::member*)->cast<_4>();
	framework::converter<_3>::type _v3 = va_arg(_args.args, framework::member*)->cast<_3>();
	framework::converter<_2>::type _v2 = va_arg(_args.args, framework::member*)->cast<_2>();
	framework::converter<_1>::type _v1 = va_arg(_args.args, framework::member*)->cast<_1>();
	framework::converter<_0>::type _v0 = va_arg(_args.args, framework::member*)->cast<_0>();

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);
}

template<typename Return>
inline void disguised_caller_format(Return(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, _function());
}

template<typename Return, typename _0>
inline void disguised_caller_format(Return(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0)));
}

template<typename Return, typename _0, typename _1>
inline void disguised_caller_format(Return(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19)));
}


inline void disguised_caller_format(void(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_format(void(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_format(void(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_format(Return(Class::*_function)(), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_format(Return(Class::*_function)(_0), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0)));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19)));
}

template<typename Class>
inline void disguised_caller_format(void(Class::*_function)(), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_format(void(Class::*_function)(_0), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_format(void(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_format(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_format(Return(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0)));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19)));
}

template<typename Class>
inline void disguised_caller_format(void(Class::*_function)() const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_format(void(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_format(void(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));

	framework::create_member(_destination);
}

template<typename Class>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 0) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	return machine::machine_context::active_allocator()->construct<Class>();
}

template<typename Class, typename _0>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 1) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0));
}

template<typename Class, typename _0, typename _1>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 2) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1));
}

template<typename Class, typename _0, typename _1, typename _2>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 3) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 4) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 5) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 6) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 7) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 8) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 9) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 10) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 11) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 12) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 13) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 14) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 15) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 16) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 17) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 18) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 19) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args)
{
	if (_count != 20) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
	_19 _v19 = format_cast<_19>(_args, _format);
	_18 _v18 = format_cast<_18>(_args, _format);
	_17 _v17 = format_cast<_17>(_args, _format);
	_16 _v16 = format_cast<_16>(_args, _format);
	_15 _v15 = format_cast<_15>(_args, _format);
	_14 _v14 = format_cast<_14>(_args, _format);
	_13 _v13 = format_cast<_13>(_args, _format);
	_12 _v12 = format_cast<_12>(_args, _format);
	_11 _v11 = format_cast<_11>(_args, _format);
	_10 _v10 = format_cast<_10>(_args, _format);
	_9 _v9 = format_cast<_9>(_args, _format);
	_8 _v8 = format_cast<_8>(_args, _format);
	_7 _v7 = format_cast<_7>(_args, _format);
	_6 _v6 = format_cast<_6>(_args, _format);
	_5 _v5 = format_cast<_5>(_args, _format);
	_4 _v4 = format_cast<_4>(_args, _format);
	_3 _v3 = format_cast<_3>(_args, _format);
	_2 _v2 = format_cast<_2>(_args, _format);
	_1 _v1 = format_cast<_1>(_args, _format);
	_0 _v0 = format_cast<_0>(_args, _format);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));
}

}
}