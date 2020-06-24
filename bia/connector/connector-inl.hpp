#ifndef BIA_CONNECTOR_CONNECTOR_INL_HPP_
#define BIA_CONNECTOR_CONNECTOR_INL_HPP_

#include "parameters.hpp"

#include <bia/creator/creator.hpp>
#include <bia/exception/nullpointer.hpp>
#include <bia/gc/gcable.hpp>
#include <bia/gc/stack_view.hpp>
#include <bia/member/cast/cast.hpp>
#include <bia/member/connector.hpp>
#include <bia/util/type_traits/int_maker.hpp>
#include <bia/util/type_traits/type_maker.hpp>
#include <utility>

namespace bia {
namespace connector {

template<std::size_t... Indices>
using parameter_indices = util::type_traits::int_container<std::size_t, Indices...>;
template<std::size_t Count>
using parameter_index_maker = util::type_traits::int_sequencer<std::size_t, 0, Count>;

inline member::member& not_null(member::member* element)
{
	if (element) {
		return *element;
	}

	BIA_THROW(exception::nullpointer, "nullpointer argument");
}

inline void assert_parameters(parameters_type params, util::type_traits::type_container<parameters_type>)
{}

template<typename... Args>
inline void assert_parameters(parameters_type params, util::type_traits::type_container<Args...>)
{
	if (sizeof...(Args) != params.size()) {
		throw;
	}
}

template<typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), parameters_type params,
                                                 parameter_indices<Indices...>)
{
	return creator::create(
	           function(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...))
	    .template to<member::member>();
}

template<typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(void (*function)(Args...), parameters_type params,
                                                 parameter_indices<Indices...>)
{
	function(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...);

	return {};
}

template<typename Class, typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_method(Class& instance, Return (Class::*function)(Args...),
                                                 parameters_type params, parameter_indices<Indices...>)
{
	return creator::create((instance.*function)(
	                           std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...))
	    .template to<member::member>();
}

template<typename Class, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_method(Class& instance, void (Class::*function)(Args...),
                                                 parameters_type params, parameter_indices<Indices...>)
{
	(instance.*function)(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...);

	return {};
}

template<typename Class, typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_method(const Class& instance,
                                                 Return (Class::*function)(Args...) const,
                                                 parameters_type params, parameter_indices<Indices...>)
{
	return creator::create((instance.*function)(
	                           std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...))
	    .template to<member::member>();
}

template<typename Class, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_method(const Class& instance,
                                                 void (Class::*function)(Args...) const,
                                                 parameters_type params, parameter_indices<Indices...>)
{
	(instance.*function)(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...);

	return {};
}

template<typename Return>
inline gc::gcable<member::member> connect_static(Return (*function)(parameters_type), parameters_type params,
                                                 parameter_indices<0>)
{
	return creator::create(function(params)).template to<member::member>();
}

inline gc::gcable<member::member> connect_static(void (*function)(parameters_type), parameters_type params,
                                                 parameter_indices<0>)
{
	function(params);

	return {};
}

template<typename Return, typename... Args>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), parameters_type params)
{
	assert_parameters(params, util::type_traits::type_container<Args...>{});

	return connect_static(function, params, parameter_index_maker<sizeof...(Args)>::value);
}

template<typename Class, typename Return, typename... Args>
inline gc::gcable<member::member> connect_method(Class& instance, Return (Class::*function)(Args...),
                                                 parameters_type params)
{
	assert_parameters(params, util::type_traits::type_container<Args...>{});

	return connect_method(instance, function, params, parameter_index_maker<sizeof...(Args)>::value);
}

template<typename Class, typename Return, typename... Args>
inline gc::gcable<member::member>
    connect_method(const Class& instance, Return (Class::*function)(Args...) const, parameters_type params)
{
	assert_parameters(params, util::type_traits::type_container<Args...>{});

	return connect_method(instance, function, params, parameter_index_maker<sizeof...(Args)>::value);
}

} // namespace connector
} // namespace bia

#endif
