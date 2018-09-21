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

template<typename Return>
Return format_cast(va_list_wrapper & _args, const char *& _format);

void disguised_caller(void(*_function)(), framework::member * _destination);

template<typename Return>
void disguised_caller(Return(*_function)(), framework::member * _destination);

template<typename Return, typename... Arguments>
void disguised_caller(Return(*)(Arguments...), framework::member * _destination);

template<typename Class>
void disguised_caller(void(Class::*_function)(), Class * _instance, framework::member * _destination);

template<typename Class>
void disguised_caller(void(Class::*_function)() const, const Class * _instance, framework::member * _destination);

template<typename Return, typename Class>
void disguised_caller(Return(Class::*_function)(), Class * _instance, framework::member * _destination);

template<typename Return, typename Class>
void disguised_caller(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination);

template<typename Return, typename Class, typename... Arguments>
void disguised_caller(Return(Class::*)(Arguments...), Class * _instance, framework::member * _destination);

template<typename Return, typename Class, typename... Arguments>
void disguised_caller(Return(Class::*)(Arguments...) const, const Class * _instance, framework::member * _destination);

template<typename Class>
machine::memory::allocation<Class> disguised_caller();

template<typename Class, typename... Arguments>
typename std::enable_if<(sizeof...(Arguments) > 0), machine::memory::allocation<Class>>::type disguised_caller();

template<typename Return>
void disguised_caller_count(Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0>
void disguised_caller_count(Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1>
void disguised_caller_count(Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2>
void disguised_caller_count(Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);


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

template<typename Class, typename Return>
void disguised_caller_count(Return(Class::*_function)(), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0>
void disguised_caller_count(Return(Class::*_function)(_0), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1>
void disguised_caller_count(Return(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class>
void disguised_caller_count(void(Class::*_function)(), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0>
void disguised_caller_count(void(Class::*_function)(_0), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1>
void disguised_caller_count(void(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return>
void disguised_caller_count(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0>
void disguised_caller_count(Return(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1>
void disguised_caller_count(Return(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class>
void disguised_caller_count(void(Class::*_function)() const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0>
void disguised_caller_count(void(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1>
void disguised_caller_count(void(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_count(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
machine::memory::allocation<Class> disguised_caller_count(framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return>
void disguised_caller_format(Return(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0>
void disguised_caller_format(Return(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1>
void disguised_caller_format(Return(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2>
void disguised_caller_format(Return(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(Return(*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);


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

template<typename Class, typename Return>
void disguised_caller_format(Return(Class::*_function)(), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0>
void disguised_caller_format(Return(Class::*_function)(_0), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1>
void disguised_caller_format(Return(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class>
void disguised_caller_format(void(Class::*_function)(), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0>
void disguised_caller_format(void(Class::*_function)(_0), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1>
void disguised_caller_format(void(Class::*_function)(_0, _1), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19), Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return>
void disguised_caller_format(Return(Class::*_function)() const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0>
void disguised_caller_format(Return(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1>
void disguised_caller_format(Return(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename Return, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(Return(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class>
void disguised_caller_format(void(Class::*_function)() const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0>
void disguised_caller_format(void(Class::*_function)(_0) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1>
void disguised_caller_format(void(Class::*_function)(_0, _1) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
void disguised_caller_format(void(Class::*_function)(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) const, const Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

template<typename Class, typename _0, typename _1, typename _2, typename _3, typename _4, typename _5, typename _6, typename _7, typename _8, typename _9, typename _10, typename _11, typename _12, typename _13, typename _14, typename _15, typename _16, typename _17, typename _18, typename _19>
machine::memory::allocation<Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list_wrapper & _args);

}
}