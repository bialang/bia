#pragma once

#include <connector/connector.hpp>
#include <creator/creator.hpp>
#include <exception/argument_exception.hpp>
#include <util/type_traits/int_maker.hpp>
#include <util/type_traits/type_maker.hpp>

namespace bia {
namespace connector {

template<typename... Args, int... Indices>
inline member::member* static_caller(void (*function)(Args...), stack::stack* stack,
                                     util::type_traits::int_container<int, Indices...>)
{
	function(stack->get(util::type_traits::type_select<Indices + 1, Args...>::values)...);

	// nothing to return
	return nullptr;
}

template<typename Return, typename... Args, int... Indices>
inline member::member* static_caller(Return (*function)(Args...), stack::stack* stack,
                                     util::type_traits::int_container<int, Indices...>)
{
	// call and wrap return value
	return creator::creator(gc::gc::active_gc())
	    .create_member(function(stack->get(util::type_traits::type_select<Indices + 1, Args...>::values)...));
}

template<typename Class, typename... Args, int... Indices>
inline member::member* member_caller(void (Class::*function)(Args...), Class* instance, stack::stack* stack,
                                     util::type_traits::int_container<int, Indices...>)
{
	(instance->*function)(stack->get(util::type_traits::type_select<Indices + 1, Args...>::values)...);

	// nothing to return
	return nullptr;
}

template<typename Return, typename Class, typename... Args, int... Indices>
inline member::member* member_caller(Return (Class::*function)(Args...), Class* instance, stack::stack* stack,
                                     util::type_traits::int_container<int, Indices...>)
{
	// call and wrap return value
	return creator::creator(gc::gc::active_gc())
	    .create_member(
	        (instance->*function)(stack->get(util::type_traits::type_select<Indices + 1, Args...>::values)...));
}

template<typename Return, typename... Args>
inline member::member* static_connector(Return (*function)(Args...), stack::stack* stack, param_count_type param_count)
{
	// invalid amount of parameters
	if (sizeof...(Args) != param_count) {
		BIA_THROW(exception::argument_exception, u"invalid argument count");
	}

	// perform call
	return static_caller(function, stack, util::type_traits::int_sequencer<int, 0, sizeof...(Args)>::values);
}

template<typename Return, typename Class, typename... Args>
inline member::member* member_connector(Return (Class::*function)(Args...), Class* instance, stack::stack* stack,
                                        param_count_type param_count)
{
	// invalid amount of parameters
	if (sizeof...(Args) != param_count) {
		BIA_THROW(exception::argument_exception, u"invalid argument count");
	}

	// perform call
	return member_caller(function, instance, stack, util::type_traits::int_sequencer<int, 0, sizeof...(Args)>::values);
}

} // namespace connector
} // namespace bia