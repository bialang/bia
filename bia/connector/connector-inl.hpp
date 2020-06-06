#ifndef BIA_CONNECTOR_CONNECTOR_INL_HPP_
#define BIA_CONNECTOR_CONNECTOR_INL_HPP_

#include <bia/creator/creator.hpp>
#include <bia/exception/nullpointer.hpp>
#include <bia/gc/gcable.hpp>
#include <bia/gc/stack_view.hpp>
#include <bia/member/cast.hpp>
#include <bia/member/connector.hpp>
#include <bia/util/type_traits/int_maker.hpp>
#include <utility>

namespace bia {
namespace connector {

template<std::size_t... Indices>
using parameter_indices = util::type_traits::int_container<std::size_t, Indices...>;
template<std::size_t Count>
using parameter_index_maker = util::type_traits::int_sequencer<std::size_t, 0, Count>;

inline member::member& not_null(gc::stack_view::element_type& element)
{
	if (const auto ptr = element.get()) {
		return *ptr;
	}

	BIA_THROW(exception::nullpointer, "nullpointer argument");
}

template<typename Return, typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(Return (*function)(Args...), gc::stack_view& stack,
                                                 parameter_indices<Indices...>)
{
	return creator::create(
	           function(std::forward<Args>(member::cast<Args>(not_null(stack.arg_at(Indices))))...))
	    .template to<member::member>();
}

template<typename... Args, std::size_t... Indices>
inline gc::gcable<member::member> connect_static(void (*function)(Args...), gc::stack_view& stack,
                                                 parameter_indices<Indices...>)
{
	function(std::forward<Args>(member::cast<Args>(not_null(stack.arg_at(Indices))))...);

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
