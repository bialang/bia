#ifndef BIA_CONNECTOR_DETAIL_STATIC_HPP_
#define BIA_CONNECTOR_DETAIL_STATIC_HPP_

#include "base.hpp"

#include <bia/creator/creator.hpp>
#include <bia/gc/gcable.hpp>

namespace bia {
namespace connector {
namespace detail {

template<typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), parameters_type params,
                                                 parameter_indices<Indices...>)
{
	return creator::create(
	    *gc::gc::active_gc(),
	    function(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...));
}

template<typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(void (*function)(Args...), parameters_type params,
                                                 parameter_indices<Indices...>)
{
	function(std::forward<Args>(member::cast::cast<Args>(not_null(params[Indices])))...);

	return {};
}

template<typename Return>
inline gc::gcable<member::member> connect_static(Return (*function)(parameters_type), parameters_type params,
                                                 parameter_indices<0>)
{
	return creator::create(*gc::gc::active_gc(), function(params));
}

inline gc::gcable<member::member> connect_static(void (*function)(parameters_type), parameters_type params,
                                                 parameter_indices<0>)
{
	function(params);

	return {};
}

} // namespace detail
} // namespace connector
} // namespace bia

#endif
