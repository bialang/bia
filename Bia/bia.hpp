#pragma once

#include <type_traits>
#include <utility>

#include "machine_context.hpp"
#include "static_function.hpp"
#include "member_function.hpp"
#include "lambda_function.hpp"


namespace bia
{

template<typename _Return, typename... _Args>
inline void set_function(machine::machine_context & _context, const char * _name, _Return(*_function)(_Args...))
{
	_context.emplace_member<framework::executable::static_function<_Return, _Args...>>(_name, _function);
}

template<typename _Class, typename _Return, typename... _Args>
inline void set_function(machine::machine_context & _context, const char * _name, _Return(_Class::*_function)(_Args...))
{
	//_context.emplace_member<framework::executable::member_function<_Class, _Return, _Args...>>(_name, _function);
}

template<typename _Lambda>
inline void set_lambda(machine::machine_context & _context, const char * _name, _Lambda && _lambda)
{
	_context.emplace_member<framework::executable::lambda_function<typename std::remove_cv<typename std::remove_reference<_Lambda>::type>::type>>(_name, std::forward<_Lambda>(_lambda));
}

}