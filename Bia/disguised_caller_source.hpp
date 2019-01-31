#pragma once

#include <cstdint>
#include <type_traits>

#include "disguised_caller.hpp"
#include "exception.hpp"
#include "create_member.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace force
{

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
inline void disguised_caller_count(Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function());
}

template<typename Return, typename _0>
inline void disguised_caller_count(Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0));
}

template<typename Return, typename _0, typename _1>
inline void disguised_caller_count(Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1));
}

template<typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19));
}


inline void disguised_caller_count(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_count(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	_function(_v0);

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_count(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	_function(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_count(Return(Class::*_function)(), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_count(Return(Class::*_function)(_0), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19));
}

template<typename Class>
inline void disguised_caller_count(void(Class::*_function)(), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_count(void(Class::*_function)(_0), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_count(void(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_count(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_count(Return(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19));
}

template<typename Class>
inline void disguised_caller_count(void(Class::*_function)() const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_count(void(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_count(void(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	(_instance->*_function)(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);

	framework::create_member(_destination);
}

template<typename Class>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>();
}

template<typename Class, typename _0>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0);
}

template<typename Class, typename _0, typename _1>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1);
}

template<typename Class, typename _0, typename _1, typename _2>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	typename framework::converter<_0>::type _v0 = _stack->cast<framework::member*>(0 - _arg_count)->cast<_0>();
	typename framework::converter<_1>::type _v1 = _stack->cast<framework::member*>(1 - _arg_count)->cast<_1>();
	typename framework::converter<_2>::type _v2 = _stack->cast<framework::member*>(2 - _arg_count)->cast<_2>();
	typename framework::converter<_3>::type _v3 = _stack->cast<framework::member*>(3 - _arg_count)->cast<_3>();
	typename framework::converter<_4>::type _v4 = _stack->cast<framework::member*>(4 - _arg_count)->cast<_4>();
	typename framework::converter<_5>::type _v5 = _stack->cast<framework::member*>(5 - _arg_count)->cast<_5>();
	typename framework::converter<_6>::type _v6 = _stack->cast<framework::member*>(6 - _arg_count)->cast<_6>();
	typename framework::converter<_7>::type _v7 = _stack->cast<framework::member*>(7 - _arg_count)->cast<_7>();
	typename framework::converter<_8>::type _v8 = _stack->cast<framework::member*>(8 - _arg_count)->cast<_8>();
	typename framework::converter<_9>::type _v9 = _stack->cast<framework::member*>(9 - _arg_count)->cast<_9>();
	typename framework::converter<_10>::type _v10 = _stack->cast<framework::member*>(10 - _arg_count)->cast<_10>();
	typename framework::converter<_11>::type _v11 = _stack->cast<framework::member*>(11 - _arg_count)->cast<_11>();
	typename framework::converter<_12>::type _v12 = _stack->cast<framework::member*>(12 - _arg_count)->cast<_12>();
	typename framework::converter<_13>::type _v13 = _stack->cast<framework::member*>(13 - _arg_count)->cast<_13>();
	typename framework::converter<_14>::type _v14 = _stack->cast<framework::member*>(14 - _arg_count)->cast<_14>();
	typename framework::converter<_15>::type _v15 = _stack->cast<framework::member*>(15 - _arg_count)->cast<_15>();
	typename framework::converter<_16>::type _v16 = _stack->cast<framework::member*>(16 - _arg_count)->cast<_16>();
	typename framework::converter<_17>::type _v17 = _stack->cast<framework::member*>(17 - _arg_count)->cast<_17>();
	typename framework::converter<_18>::type _v18 = _stack->cast<framework::member*>(18 - _arg_count)->cast<_18>();
	typename framework::converter<_19>::type _v19 = _stack->cast<framework::member*>(19 - _arg_count)->cast<_19>();

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8, _v9, _v10, _v11, _v12, _v13, _v14, _v15, _v16, _v17, _v18, _v19);
}

template<typename Return>
inline void disguised_caller_format(Return(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function());
}

template<typename Return, typename _0>
inline void disguised_caller_format(Return(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0)));
}

template<typename Return, typename _0, typename _1>
inline void disguised_caller_format(Return(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18)));
}

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, _function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19)));
}


inline void disguised_caller_format(void(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	_function();

	framework::create_member(_destination);
}

template<typename _0>
inline void disguised_caller_format(void(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename _0, typename _1>
inline void disguised_caller_format(void(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));

	framework::create_member(_destination);
}

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	_function(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_format(Return(Class::*_function)(), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_format(Return(Class::*_function)(_0), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0)));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19)));
}

template<typename Class>
inline void disguised_caller_format(void(Class::*_function)(), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_format(void(Class::*_function)(_0), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_format(void(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));

	framework::create_member(_destination);
}

template<typename Class, typename Return>
inline void disguised_caller_format(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)());
}

template<typename Class, typename Return, typename _0>
inline void disguised_caller_format(Return(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0)));
}

template<typename Class, typename Return, typename _0, typename _1>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18)));
}

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	framework::create_member(_destination, (_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19)));
}

template<typename Class>
inline void disguised_caller_format(void(Class::*_function)() const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	(_instance->*_function)();

	framework::create_member(_destination);
}

template<typename Class, typename _0>
inline void disguised_caller_format(void(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1>
inline void disguised_caller_format(void(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));

	framework::create_member(_destination);
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	(_instance->*_function)(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));

	framework::create_member(_destination);
}

template<typename Class>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 0;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}


	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>();
}

template<typename Class, typename _0>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 1;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0));
}

template<typename Class, typename _0, typename _1>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 2;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1));
}

template<typename Class, typename _0, typename _1, typename _2>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 3;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 4;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 5;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 6;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 7;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 8;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 9;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 10;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 11;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 12;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 13;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 14;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 15;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 16;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 17;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 18;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 19;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18));
}

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
inline machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, machine::stack * _stack)
{
	constexpr auto _arg_count = 20;

	if (_count != _arg_count) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}

	_0 _v0 = _stack->format_cast<_0>(0 - _arg_count, *_format++);
	_1 _v1 = _stack->format_cast<_1>(1 - _arg_count, *_format++);
	_2 _v2 = _stack->format_cast<_2>(2 - _arg_count, *_format++);
	_3 _v3 = _stack->format_cast<_3>(3 - _arg_count, *_format++);
	_4 _v4 = _stack->format_cast<_4>(4 - _arg_count, *_format++);
	_5 _v5 = _stack->format_cast<_5>(5 - _arg_count, *_format++);
	_6 _v6 = _stack->format_cast<_6>(6 - _arg_count, *_format++);
	_7 _v7 = _stack->format_cast<_7>(7 - _arg_count, *_format++);
	_8 _v8 = _stack->format_cast<_8>(8 - _arg_count, *_format++);
	_9 _v9 = _stack->format_cast<_9>(9 - _arg_count, *_format++);
	_10 _v10 = _stack->format_cast<_10>(10 - _arg_count, *_format++);
	_11 _v11 = _stack->format_cast<_11>(11 - _arg_count, *_format++);
	_12 _v12 = _stack->format_cast<_12>(12 - _arg_count, *_format++);
	_13 _v13 = _stack->format_cast<_13>(13 - _arg_count, *_format++);
	_14 _v14 = _stack->format_cast<_14>(14 - _arg_count, *_format++);
	_15 _v15 = _stack->format_cast<_15>(15 - _arg_count, *_format++);
	_16 _v16 = _stack->format_cast<_16>(16 - _arg_count, *_format++);
	_17 _v17 = _stack->format_cast<_17>(17 - _arg_count, *_format++);
	_18 _v18 = _stack->format_cast<_18>(18 - _arg_count, *_format++);
	_19 _v19 = _stack->format_cast<_19>(19 - _arg_count, *_format++);

	_stack->pop_count(_arg_count);

	return machine::machine_context::active_allocator()->construct<Class>(std::forward<_0>(_v0), std::forward<_1>(_v1), std::forward<_2>(_v2), std::forward<_3>(_v3), std::forward<_4>(_v4), std::forward<_5>(_v5), std::forward<_6>(_v6), std::forward<_7>(_v7), std::forward<_8>(_v8), std::forward<_9>(_v9), std::forward<_10>(_v10), std::forward<_11>(_v11), std::forward<_12>(_v12), std::forward<_13>(_v13), std::forward<_14>(_v14), std::forward<_15>(_v15), std::forward<_16>(_v16), std::forward<_17>(_v17), std::forward<_18>(_v18), std::forward<_19>(_v19));
}

}
}