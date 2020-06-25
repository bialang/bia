#ifndef BIA_CONNECTOR_CONNECTOR_INL_HPP_
#define BIA_CONNECTOR_CONNECTOR_INL_HPP_

#include "connector.hpp"
#include "detail/method.hpp"
#include "detail/static.hpp"
#include "parameters.hpp"

#include <bia/util/type_traits/method_info.hpp>
#include <type_traits>
#include <utility>

namespace bia {
namespace connector {

template<typename Return, typename... Args>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), parameters_type params)
{
	detail::assert_parameters(params, util::type_traits::type_container<Args...>{});

	return detail::connect_static(function, params, detail::parameter_index_maker<sizeof...(Args)>::value);
}

template<typename Class, typename Return, typename... Args>
inline gc::gcable<member::member> connect_method(Class& instance, Return (Class::*function)(Args...),
                                                 parameters_type params)
{
	detail::assert_parameters(params, util::type_traits::type_container<Args...>{});

	return detail::connect_method(instance, function, params,
	                              detail::parameter_index_maker<sizeof...(Args)>::value);
}

template<typename Class, typename Return, typename... Args>
inline gc::gcable<member::member>
    connect_method(const Class& instance, Return (Class::*function)(Args...) const, parameters_type params)
{
	detail::assert_parameters(params, util::type_traits::type_container<Args...>{});

	return detail::connect_method(instance, function, params,
	                              detail::parameter_index_maker<sizeof...(Args)>::value);
}

} // namespace connector
} // namespace bia

#endif
