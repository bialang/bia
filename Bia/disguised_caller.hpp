#pragma once

#include <type_traits>
#include <utility>

#include "disguised_caller_def.hpp"
#include "exception.hpp"
#include "create_member.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace force
{

template<machine::stack::index_t... Indices>
using sequence = std::integer_sequence<machine::stack::index_t, Indices...>;

template<typename... Arguments>
using make_sequence = std::make_integer_sequence<machine::stack::index_t, sizeof...(Arguments)>;

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
	constexpr auto arg_count = sizeof...(Arguments);

	return _function(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename... Arguments, typename Return, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Arguments...), const char * _format, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	return _function(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	return (_instance->*_function)(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), const char * _format, machine::stack * _stack, sequence<Indices...>)
{
	return (_instance->*_function)(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	return (_instance->*_function)(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename... Arguments, typename Return, typename Class, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, const char * _format, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	return (_instance->*_function)(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}

template<typename Class, typename... Arguments, machine::stack::index_t... Indices>
inline machine::memory::allocation<Class> disguised_caller(machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	return machine::machine_context::active_allocator()->construct<Class>(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename Class, typename... Arguments, machine::stack::index_t... Indices>
inline machine::memory::allocation<Class> disguised_caller(const char * _format, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	return machine::machine_context::active_allocator()->construct<Class>(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}


template<typename... Arguments, typename Format>
inline void disguised_caller(void(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		disguised_caller<Arguments...>(_function, _stack, make_sequence<Arguments...>());
	} else {
		disguised_caller<Arguments...>(_function, static_cast<const char*>(_format), _stack, make_sequence<Arguments...>());
	}

	framework::create_member(_destination);
}

template<typename... Arguments, typename Return, typename Format>
inline void disguised_caller(Return(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		framework::create_member(_destination, disguised_caller<Arguments...>(_function, _stack, make_sequence<Arguments...>()));
	} else {
		framework::create_member(_destination, disguised_caller<Arguments...>(_function, static_cast<const char*>(_format), _stack, make_sequence<Arguments...>()));
	}
}

template<typename... Arguments, typename Class, typename Format>
inline void disguised_caller(Class * _instance, void(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		disguised_caller<Arguments...>(_instance, _function, _stack, make_sequence<Arguments...>());
	} else {
		disguised_caller<Arguments...>(_instance, _function, static_cast<const char*>(_format), _stack, make_sequence<Arguments...>());
	}

	framework::create_member(_destination);
}

template<typename... Arguments, typename Class, typename Return, typename Format>
inline void disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		framework::create_member(_destination, disguised_caller<Arguments...>(_instance, _function, _stack, make_sequence<Arguments...>()));
	} else {
		framework::create_member(_destination, disguised_caller<Arguments...>(_instance, _function, static_cast<const char*>(_format), _stack, make_sequence<Arguments...>()));
	}
}

template<typename... Arguments, typename Class, typename Format>
inline void disguised_caller(const Class * _instance, void(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		disguised_caller<Arguments...>(_instance, _function, _stack, make_sequence<Arguments...>());
	} else {
		disguised_caller<Arguments...>(_instance, _function, static_cast<const char*>(_format), _stack, make_sequence<Arguments...>());
	}

	framework::create_member(_destination);
}

template<typename... Arguments, typename Class, typename Return, typename Format>
inline void disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		framework::create_member(_destination, disguised_caller<Arguments...>(_instance, _function, _stack, make_sequence<Arguments...>()));
	} else {
		framework::create_member(_destination, disguised_caller<Arguments...>(_instance, _function, static_cast<const char*>(_format), _stack, make_sequence<Arguments...>()));
	}
}

template<typename Class, typename... Arguments, typename Format>
inline machine::memory::allocation<Class> disguised_caller(Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);
	
	if (std::is_null_pointer<Format>::value) {
		return disguised_caller<Class, Arguments...>(_stack, make_sequence<Arguments...>());
	} else {
		return disguised_caller<Class, Arguments...>(static_cast<const char*>(_format), _stack, make_sequence<Arguments...>());
	}
}


}
}