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
inline void assert_argument_count(framework::member::parameter_count_t _count)
{
    if (_count != sizeof...(Arguments)) {
        throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
    }
}

template<typename... Arguments, typename Return, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Arguments...), machine::stack * _stack, sequence<Indices...>)
{
    return _function(_stack->cast<framework::member>(Indices)->cast<Arguments>()...);
}

template<typename... Arguments, typename Return, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Arguments...), machine::stack * _stack, const char * _format, sequence<Indices...>)
{
    return _function(_stack->format_cast<Arguments>(_format[Indices])...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), machine::stack * _stack, sequence<Indices...>)
{
    return (_instance->*_function)(_stack->cast<framework::member>(Indices)->cast<Arguments>()...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), machine::stack * _stack, const char * _format, sequence<Indices...>)
{
    return (_instance->*_function)(_stack->format_cast<Arguments>(_format[Indices])...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, machine::stack * _stack, sequence<Indices...>)
{
    return (_instance->*_function)(_stack->cast<framework::member>(Indices)->cast<Arguments>()...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, machine::stack * _stack, const char * _format, sequence<Indices...>)
{
    return (_instance->*_function)(_stack->format_cast<Arguments>(_format[Indices])...);
}

template<typename... Arguments>
inline void disguised_caller(void(*_function)(Arguments...), framework::member * _destination)
{
    assert_argument_count<Arguments...>(0);

    disguised_caller<Arguments...>(_function, nullptr, std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>());
    framework::create_member(_destination);
}

template<typename... Arguments, typename Return>
inline void disguised_caller(Return(*_function)(Arguments...), framework::member * _destination)
{
    assert_argument_count<Arguments...>(0);

    framework::create_member(disguised_caller<Arguments...>(_function, nullptr, std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>()), _destination);
}

template<typename... Arguments, typename Class>
inline void disguised_caller(Class * _instance, void(Class::*_function)(Arguments...), framework::member * _destination)
{
    assert_argument_count<Arguments...>(0);

    disguised_caller<Arguments...>(_instance, _function, nullptr, std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>());
    framework::create_member(_destination);
}

template<typename... Arguments, typename Class, typename Return>
inline void disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), framework::member * _destination)
{
    assert_argument_count<Arguments...>(0);

    framework::create_member(disguised_caller<Arguments...>(_instance, _function, nullptr, std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>()), _destination);
}

template<typename... Arguments, typename Class>
inline void disguised_caller(const Class * _instance, void(Class::*_function)(Arguments...) const, framework::member * _destination)
{
    assert_argument_count<Arguments...>(0);

    disguised_caller<Arguments...>(_instance, _function, nullptr, std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>());
    framework::create_member(_destination);
}

template<typename... Arguments, typename Class, typename Return>
inline void disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, framework::member * _destination)
{
    assert_argument_count<Arguments...>(0);

    framework::create_member(disguised_caller<Arguments...>(_instance, _function, nullptr, std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>()), _destination);
}

}
}