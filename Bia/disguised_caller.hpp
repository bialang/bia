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

template<typename _Return, typename _List>
_Return format_cast(_List & _args, const char *& _format);

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
void disguised_caller_count(_Return(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Return, typename _0>
void disguised_caller_count(_Return(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Return, typename _0, typename _1>
void disguised_caller_count(_Return(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_count(_Return(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list _args);


void disguised_caller_count(void(*_function)(), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _0>
void disguised_caller_count(void(*_function)(_0), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _0, typename _1>
void disguised_caller_count(void(*_function)(_0, _1), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _0, typename _1, typename _2>
void disguised_caller_count(void(*_function)(_0, _1, _2), framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return>
void disguised_caller_count(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_count(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class>
void disguised_caller_count(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0>
void disguised_caller_count(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_count(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return>
void disguised_caller_count(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_count(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_count(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class>
void disguised_caller_count(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0>
void disguised_caller_count(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_count(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_count(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, framework::member::parameter_count _count, va_list _args);

template<typename _Class>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1, typename _2>
machine::memory::allocation<_Class> disguised_caller_count(framework::member::parameter_count _count, va_list _args);

template<typename _Return>
void disguised_caller_format(_Return(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Return, typename _0>
void disguised_caller_format(_Return(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Return, typename _0, typename _1>
void disguised_caller_format(_Return(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_format(_Return(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);


void disguised_caller_format(void(*_function)(), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _0>
void disguised_caller_format(void(*_function)(_0), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _0, typename _1>
void disguised_caller_format(void(*_function)(_0, _1), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _0, typename _1, typename _2>
void disguised_caller_format(void(*_function)(_0, _1, _2), framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return>
void disguised_caller_format(_Return(_Class::*_function)(), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_format(_Return(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class>
void disguised_caller_format(void(_Class::*_function)(), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0>
void disguised_caller_format(void(_Class::*_function)(_0), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_format(void(_Class::*_function)(_0, _1), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2), _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return>
void disguised_caller_format(_Return(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0>
void disguised_caller_format(_Return(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _Return, typename _0, typename _1, typename _2>
void disguised_caller_format(_Return(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class>
void disguised_caller_format(void(_Class::*_function)() const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0>
void disguised_caller_format(void(_Class::*_function)(_0) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1>
void disguised_caller_format(void(_Class::*_function)(_0, _1) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1, typename _2>
void disguised_caller_format(void(_Class::*_function)(_0, _1, _2) const, const _Class * _instance, framework::member * _destination, const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args);

template<typename _Class, typename _0, typename _1, typename _2>
machine::memory::allocation<_Class> disguised_caller_format(const char * _format, framework::member::parameter_count _count, va_list _args);

}
}