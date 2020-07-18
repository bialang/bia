#ifndef BIA_CONNECTOR_DETAIL_BASE_HPP_
#define BIA_CONNECTOR_DETAIL_BASE_HPP_

#include "../parameters.hpp"

#include <bia/exception/nullpointer.hpp>
#include <bia/member/cast/cast.hpp>
#include <bia/member/member.hpp>
#include <bia/util/type_traits/int_maker.hpp>
#include <bia/util/type_traits/type_select.hpp>

namespace bia {
namespace connector {
namespace detail {

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

} // namespace detail
} // namespace connector
} // namespace bia

#endif
