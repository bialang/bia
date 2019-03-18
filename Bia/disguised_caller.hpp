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

template<size_t Count>
using make_sequence = std::make_integer_sequence<machine::stack::index_t, Count>;

template<size_t Count, typename... Types>
using type_splitter = utility::type_container_splitter<Count, utility::type_container<>, Types...>;

template<typename... Arguments>
inline void assert_argument_count(framework::member::parameter_count_t _count)
{
	if (_count != sizeof...(Arguments)) {
		throw exception::argument_error(BIA_EM_INVALID_ARGUMENT);
	}
}

template<typename Return, typename... Function_args, typename... Arguments, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<>, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	assert_argument_count<Arguments...>(_count);

	return _function(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename Return, typename... Function_args, typename... Arguments, typename... Optionals, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<Optionals...>, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	if (_count == arg_count) {
		return _function(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()..., Optionals()...);
	}

	using splitter = type_splitter<arg_count + 1, Arguments..., Optionals...>;

	return disguised_caller(_function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count + 1>());
}

template<typename Return, typename... Function_args, typename... Arguments, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<>, const char * _format, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	assert_argument_count<Arguments...>(_count);

	return _function(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}

template<typename Return, typename... Function_args, typename... Arguments, typename... Optionals, machine::stack::index_t... Indices>
inline Return disguised_caller(Return(*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<Optionals...>, const char * _format, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	if (_count == arg_count) {
		return _function(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])..., Optionals()...);
	}

	using splitter = type_splitter<arg_count + 1, Arguments..., Optionals...>;

	return disguised_caller(_function, splitter::first(), splitter::second(), _format, _count, _stack, make_sequence<arg_count + 1>());
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<>, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	assert_argument_count<Arguments...>(_count);

	return (_instance->*_function)(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, typename... Optionals, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<Optionals...>, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	if (_count == arg_count) {
		return (_instance->*_function)(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()..., Optionals()...);
	}

	using splitter = type_splitter<arg_count + 1, Arguments..., Optionals...>;

	return disguised_caller(_instance, _function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count + 1>());
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<>, const char * _format, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	assert_argument_count<Arguments...>(_count);

	return (_instance->*_function)(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, typename... Optionals, machine::stack::index_t... Indices>
inline Return disguised_caller(Class * _instance, Return(Class::*_function)(Function_args...), utility::type_container<Arguments...>, utility::type_container<Optionals...>, const char * _format, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	if (_count == arg_count) {
		return (_instance->*_function)(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])..., Optionals()...);
	}

	using splitter = type_splitter<arg_count + 1, Arguments..., Optionals...>;

	return disguised_caller(_instance, _function, splitter::first(), splitter::second(), _format, _count, _stack, make_sequence<arg_count + 1>());
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Function_args...) const, utility::type_container<Arguments...>, utility::type_container<>, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	assert_argument_count<Arguments...>(_count);

	return (_instance->*_function)(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()...);
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, typename... Optionals, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Function_args...) const, utility::type_container<Arguments...>, utility::type_container<Optionals...>, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	if (_count == arg_count) {
		return (_instance->*_function)(_stack->cast<framework::member*>(Indices - arg_count)->cast<Arguments>()..., Optionals()...);
	}

	using splitter = type_splitter<arg_count + 1, Arguments..., Optionals...>;

	return disguised_caller(_instance, _function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count + 1>());
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Function_args...) const, utility::type_container<Arguments...>, utility::type_container<>, const char * _format, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	assert_argument_count<Arguments...>(_count);

	return (_instance->*_function)(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])...);
}

template<typename Class, typename Return, typename... Function_args, typename... Arguments, typename... Optionals, machine::stack::index_t... Indices>
inline Return disguised_caller(const Class * _instance, Return(Class::*_function)(Function_args...) const, utility::type_container<Arguments...>, utility::type_container<Optionals...>, const char * _format, framework::member::parameter_count_t _count, machine::stack * _stack, sequence<Indices...>)
{
	constexpr auto arg_count = sizeof...(Arguments);

	if (_count == arg_count) {
		return (_instance->*_function)(_stack->format_cast<Arguments>(Indices - arg_count, _format[Indices])..., Optionals()...);
	}

	using splitter = type_splitter<arg_count + 1, Arguments..., Optionals...>;

	return disguised_caller(_instance, _function, splitter::first(), splitter::second(), _format, _count, _stack, make_sequence<arg_count + 1>());
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
/////////////////////////////////////////////////////////////////////////////

template<size_t Opt_count, typename... Arguments, typename Format>
inline void disguised_caller(void(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	static_assert(Opt_count <= sizeof...(Arguments), "Cannot declare more optional parameters than actual parameters.");

	constexpr auto arg_count = sizeof...(Arguments) - Opt_count;

	using splitter = utility::type_container_splitter<arg_count, utility::type_container<>, Arguments...>;

	if (std::is_null_pointer<Format>::value) {
		disguised_caller(_function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count>());
	} else {
		disguised_caller(_function, splitter::first(), splitter::second(), static_cast<const char*>(_format), _count, _stack, make_sequence<arg_count>());
	}

	framework::create_member(_destination);
}

template<size_t Opt_count, typename... Arguments, typename Return, typename Format>
inline void disguised_caller(Return(*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	static_assert(Opt_count <= sizeof...(Arguments), "Cannot declare more optional parameters than actual parameters.");

	constexpr auto arg_count = sizeof...(Arguments) - Opt_count;

	using splitter = utility::type_container_splitter<arg_count, utility::type_container<>, Arguments...>;

	if (std::is_null_pointer<Format>::value) {
		framework::create_member(_destination, disguised_caller(_function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count>()));
	} else {
		framework::create_member(_destination, disguised_caller(_function, splitter::first(), splitter::second(), static_cast<const char*>(_format), _count, _stack, make_sequence<arg_count>()));
	}
}

template<size_t Opt_count, typename... Arguments, typename Class, typename Format>
inline void disguised_caller(Class * _instance, void(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	static_assert(Opt_count <= sizeof...(Arguments), "Cannot declare more optional parameters than actual parameters.");

	constexpr auto arg_count = sizeof...(Arguments) - Opt_count;

	using splitter = utility::type_container_splitter<arg_count, utility::type_container<>, Arguments...>;

	if (std::is_null_pointer<Format>::value) {
		disguised_caller(_instance, _function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count>());
	} else {
		disguised_caller(_instance, _function, splitter::first(), splitter::second(), static_cast<const char*>(_format), _count, _stack, make_sequence<arg_count>());
	}

	framework::create_member(_destination);
}

template<size_t Opt_count, typename... Arguments, typename Class, typename Return, typename Format>
inline void disguised_caller(Class * _instance, Return(Class::*_function)(Arguments...), framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	static_assert(Opt_count <= sizeof...(Arguments), "Cannot declare more optional parameters than actual parameters.");

	constexpr auto arg_count = sizeof...(Arguments) - Opt_count;

	using splitter = utility::type_container_splitter<arg_count, utility::type_container<>, Arguments...>;

	if (std::is_null_pointer<Format>::value) {
		framework::create_member(_destination, disguised_caller(_instance, _function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count>()));
	} else {
		framework::create_member(_destination, disguised_caller(_instance, _function, splitter::first(), splitter::second(), static_cast<const char*>(_format), _count, _stack, make_sequence<arg_count>()));
	}
}

template<size_t Opt_count, typename... Arguments, typename Class, typename Format>
inline void disguised_caller(const Class * _instance, void(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	static_assert(Opt_count <= sizeof...(Arguments), "Cannot declare more optional parameters than actual parameters.");

	constexpr auto arg_count = sizeof...(Arguments) - Opt_count;

	using splitter = utility::type_container_splitter<arg_count, utility::type_container<>, Arguments...>;

	if (std::is_null_pointer<Format>::value) {
		disguised_caller(_instance, _function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count>());
	} else {
		disguised_caller(_instance, _function, splitter::first(), splitter::second(), static_cast<const char*>(_format), _count, _stack, make_sequence<arg_count>());
	}

	framework::create_member(_destination);
}

template<size_t Opt_count, typename... Arguments, typename Class, typename Return, typename Format>
inline void disguised_caller(const Class * _instance, Return(Class::*_function)(Arguments...) const, framework::member * _destination, Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	static_assert(Opt_count <= sizeof...(Arguments), "Cannot declare more optional parameters than actual parameters.");

	constexpr auto arg_count = sizeof...(Arguments) - Opt_count;

	using splitter = utility::type_container_splitter<arg_count, utility::type_container<>, Arguments...>;

	if (std::is_null_pointer<Format>::value) {
		framework::create_member(_destination, disguised_caller(_instance, _function, splitter::first(), splitter::second(), _count, _stack, make_sequence<arg_count>()));
	} else {
		framework::create_member(_destination, disguised_caller(_instance, _function, splitter::first(), splitter::second(), static_cast<const char*>(_format), _count, _stack, make_sequence<arg_count>()));
	}
}

template<typename Class, typename... Arguments, typename Format>
inline machine::memory::allocation<Class> disguised_caller(Format _format, framework::member::parameter_count_t _count, machine::stack * _stack)
{
	assert_argument_count<Arguments...>(_count);

	if (std::is_null_pointer<Format>::value) {
		return disguised_caller<Class, Arguments...>(_stack, make_sequence<sizeof...(Arguments)>());
	} else {
		return disguised_caller<Class, Arguments...>(static_cast<const char*>(_format), _stack, make_sequence<sizeof...(Arguments)>());
	}
}


}
}