#pragma once

#include <type_traits>
#include <utility>

#include "machine_context.hpp"
#include "string_manager.hpp"
#include "static_function.hpp"
#include "member_function.hpp"
#include "lambda_function.hpp"
#include "class_template.hpp"
#include "namespace_member.hpp"
#include "template_wrapper.hpp"
#include "disguised_caller_source.hpp"


namespace bia
{

template<typename Return, typename... Arguments>
inline void set_function(machine::machine_context & _context, machine::string_manager::name_type _name, Return(*_function)(Arguments...))
{
	// Set the active allocator
	_context.activate_context();

	_context.emplace_member<framework::executable::static_function<Return, Arguments...>>(_name, _function);
}

template<typename Class, typename Return, typename... Arguments>
inline void set_function(machine::machine_context & _context, machine::string_manager::name_type _name, Return(Class::*_function)(Arguments...))
{
	//_context.emplace_member<framework::executable::member_function<Class, Return, Arguments...>>(_name, _function);
}

template<typename _Lambda>
inline void set_lambda(machine::machine_context & _context, machine::string_manager::name_type _name, _Lambda && _lambda)
{
	// Set the active allocator
	_context.activate_context();

	_context.emplace_member<framework::executable::lambda_function<typename std::remove_cv<typename std::remove_reference<_Lambda>::type>::type>>(_name, std::forward<_Lambda>(_lambda));
}

template<typename Class>
inline framework::object::template_wrapper<framework::object::class_template<Class>, Class> set_class(machine::machine_context & _context, machine::string_manager::name_type _name)
{
	// Set the active allocator
	_context.activate_context();

	auto _template = _context.emplace_member<framework::object::class_template<Class>>(_name);

	return framework::object::template_wrapper<framework::object::class_template<Class>, Class>(_context, _template);
}

template<typename Class>
inline framework::object::template_wrapper<framework::object::class_template<Class>, Class> set_class(machine::machine_context & _context, framework::member & _member)
{
	// Set the active allocator
	_context.activate_context();

	auto _template = _member.replace_this<framework::object::class_template<Class>>();

	return framework::object::template_wrapper<framework::object::class_template<Class>, Class>(_context, _template);
}

inline framework::object::template_wrapper<framework::object::namespace_member, void> set_namespace(machine::machine_context & _context, machine::string_manager::name_type _name)
{
	// Set the active allocator
	_context.activate_context();

	auto _template = _context.emplace_member<framework::object::namespace_member>(_name, framework::object::member_map());

	return framework::object::template_wrapper<framework::object::namespace_member, void>(_context, _template);
}

inline framework::object::template_wrapper<framework::object::namespace_member, void> set_namespace(machine::machine_context & _context, framework::member & _member)
{
	// Set the active allocator
	_context.activate_context();

	auto _template = _member.replace_this<framework::object::namespace_member>(framework::object::member_map());

	return framework::object::template_wrapper<framework::object::namespace_member, void>(_context, _template);
}

}
