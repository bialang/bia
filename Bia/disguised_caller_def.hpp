#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

#include "member.hpp"
#include "stack.hpp"
#include "allocator.hpp"
#include "type_traits.hpp"


namespace bia
{
namespace force
{

template<machine::stack::index_t... Indices>
using sequence = std::integer_sequence<machine::stack::index_t, Indices...>;

template<typename... Arguments>
using make_sequence = std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>;

template<typename... Arguments>
void assert_argument_count(framework::member::parameter_count_t _count);

template<typename... Arguments, typename Return, machine::stack::index_t... Indices>
Return disguised_caller(Return(*_function)(Arguments...), machine::stack * _stack, sequence<Indices...>);

template<typename... Arguments, typename Return, machine::stack::index_t... Indices>
Return disguised_caller(Return(*_function)(Arguments...), const char * _format, machine::stack * _stack, sequence<Indices...>);

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
Return disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), machine::stack * _stack, sequence<Indices...>);

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
Return disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), const char * _format, machine::stack * _stack, sequence<Indices...>);

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
Return disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, machine::stack * _stack, sequence<Indices...>);

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
Return disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, const char * _format, machine::stack * _stack, sequence<Indices...>);


template<typename... Arguments, typename Format>
void disguised_caller(void(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<typename... Arguments, typename Return, typename Format>
void disguised_caller(Return(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<typename... Arguments, typename Class, typename Format>
void disguised_caller(Class * _instance, void(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<typename... Arguments, typename Class, typename Return, typename Format>
void disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<typename... Arguments, typename Class, typename Format>
void disguised_caller(const Class * _instance, void(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<typename... Arguments, typename Class, typename Return, typename Format>
void disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<typename Class, typename... Arguments, typename Format>
machine::memory::allocation<Class> disguised_caller(Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

}
}