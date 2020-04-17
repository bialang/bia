#ifndef BIA_CONNECTOR_CONNECTOR_INL_HPP_
#define BIA_CONNECTOR_CONNECTOR_INL_HPP_

#include <connector/connector.hpp>
#include <creator/creator.hpp>
#include <util/type_traits/int_maker.hpp>
#include <gc/gcable.hpp>
#include <gc/stack_view.hpp>

namespace bia {
namespace connector {

template<std::size_t... Indices>
using parameter_indices = util::type_traits::int_container<std::size_t, Indices...>;
template<std::size_t Count>
using parameter_index_maker = util::type_traits::int_sequencer<std::size_t, 0, Count>;

template<typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), gc::stack_view& stack,
                                                 parameter_indices<Indices...>)
{
	return creator::create(function(stack.arg_at(Indices)...)).template to<member::member>();
}

template<typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(void (*function)(Args...), gc::stack_view& stack,
                                                 parameter_indices<Indices...>)
{
	function(stack.arg_at(Indices)...);

	return {};
}

template<typename Return, typename... Args>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), gc::stack_view& stack,
                                                 std::size_t parameter_count)
{
	if (parameter_count != sizeof...(Args)) {
		throw;
	}

	return connect_static(function, stack, parameter_index_maker<sizeof...(Args)>::value);
}

} // namespace connector
} // namespace bia

#endif