#pragma once

#include <cstdarg>
#include <cstdint>
#include <type_traits>

#include "member.hpp"
#include "allocator.hpp"
#include "type_traits.hpp"


namespace bia
{
namespace force
{

struct va_list_wrapper
{
	std::va_list args;
};

template<typename _Return>
_Return format_cast(va_list_wrapper & _args, const char *& _format);

void disguised_caller(void(*_function)(), framework::member * _destination);

template<typename _Return>
void disguised_caller(_Return(*_function)(), framework::member * _destination);

template<typename _Return, typename... _Args>
void disguised_caller(_Return(*)(_Args...), framework::member * _destination);

template<typename _Class>
void disguised_caller(void(_Class::*_function)(), _Class * _instance, framework::member * _destination);

template<typename _Class>
void disguised_caller(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination);

template<typename _Return, typename _Class>
void disguised_caller(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination);

template<typename _Return, typename _Class>
void disguised_caller(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination);

template<typename _Return, typename _Class, typename... _Args>
void disguised_caller(_Return(_Class::*)(_Args...), _Class * _instance, framework::member * _destination);

template<typename _Return, typename _Class, typename... _Args>
void disguised_caller(_Return(_Class::*)(_Args...) const, const _Class * _instance, framework::member * _destination);

template<typename _Class>
machine::memory::allocation<_Class> disguised_caller();

template<typename _Class, typename... _Args>
typename std::enable_if<(sizeof...(_Args) > 0), machine::memory::allocation<_Class>>::type disguised_caller();

template<typename _Return>
void disguised_caller_count(_Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0>
void disguised_caller_count(_Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1>
void disguised_caller_count(_Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_count(_Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);


void disguised_caller_count(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0>
void disguised_caller_count(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1>
void disguised_caller_count(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2>
void disguised_caller_count(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return>
void disguised_caller_count(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_count(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class>
void disguised_caller_count(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0>
void disguised_caller_count(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_count(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return>
void disguised_caller_count(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_count(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class>
void disguised_caller_count(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0>
void disguised_caller_count(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_count(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return>
void disguised_caller_format(_Return(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0>
void disguised_caller_format(_Return(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1>
void disguised_caller_format(_Return(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_format(_Return(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(_Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);


void disguised_caller_format(void(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0>
void disguised_caller_format(void(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1>
void disguised_caller_format(void(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2>
void disguised_caller_format(void(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(void(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return>
void disguised_caller_format(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_format(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class>
void disguised_caller_format(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0>
void disguised_caller_format(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_format(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return>
void disguised_caller_format(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_format(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class>
void disguised_caller_format(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0>
void disguised_caller_format(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_format(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename _Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

}
}