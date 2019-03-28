#pragma once

#include <cstddef>

#include "member.hpp"
#include "stack.hpp"
#include "allocator.hpp"


namespace bia
{
namespace force
{

template<size_t Opt_count, typename... Arguments, typename Format>
void disguised_caller(void(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<size_t Opt_count, typename... Arguments, typename Return, typename Format>
void disguised_caller(Return(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<size_t Opt_count, typename... Arguments, typename Class, typename Format>
void disguised_caller(Class * _instance, void(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<size_t Opt_count, typename... Arguments, typename Class, typename Return, typename Format>
void disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<size_t Opt_count, typename... Arguments, typename Class, typename Format>
void disguised_caller(const Class * _instance, void(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<size_t Opt_count, typename... Arguments, typename Class, typename Return, typename Format>
void disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

template<size_t Opt_count, typename Class, typename... Arguments, typename Format>
machine::memory::allocation<Class> disguised_caller(Format _format, framework::member::parameter_count_t _count, machine::stack * _stack);

}
}