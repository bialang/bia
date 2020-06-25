#ifndef BIA_CONNECTOR_DETAIL_METHOD_HPP_
#define BIA_CONNECTOR_DETAIL_METHOD_HPP_

#include "base.hpp"

#include <bia/creator/creator.hpp>
#include <bia/gc/gcable.hpp>

namespace bia {
namespace connector {
namespace detail {

template<typename Class, typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_method(Class& instance, Return (Class::*function)(Args...),
                                                 parameters_type params, parameter_indices<Indices...>)
{
	return creator::create(
	    (instance.*function)(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...));
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
	return creator::create(
	    (instance.*function)(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...));
}

template<typename Class, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_method(const Class& instance,
                                                 void (Class::*function)(Args...) const,
                                                 parameters_type params, parameter_indices<Indices...>)
{
	(instance.*function)(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...);

	return {};
}

template<typename Class, typename Return>
inline gc::gcable<member::member> connect_method(const Class& instance,
                                                 Return (Class::*function)(parameters_type) const,
                                                 parameters_type params, parameter_indices<0>)
{
	return creator::create((instance.*function)(params));
}

template<typename Class>
inline gc::gcable<member::member> connect_method(const Class& instance,
                                                 void (Class::*function)(parameters_type) const,
                                                 parameters_type params, parameter_indices<0>)
{
	(instance.*function)(params);

	return {};
}

} // namespace detail
} // namespace connector
} // namespace bia

#endif
