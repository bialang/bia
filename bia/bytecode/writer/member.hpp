#ifndef BIA_BYTECODE_WRITER_MEMBER_HPP_
#define BIA_BYTECODE_WRITER_MEMBER_HPP_

#include "../op_code.hpp"
#include "common.hpp"

#include <ostream>
#include <type_traits>
#include <bia/util/type_traits/equals_any.hpp>
#include <bia/util/type_traits/type_index.hpp>

namespace bia {
namespace bytecode {
namespace writer {

template<typename T>
using is_member_source =
    util::type_traits::equals_any_type<typename std::decay<T>::type, member::tos, member::args,
                                       member::global, member::local, member::resource>;
template<typename T>
using is_member_destination = util::type_traits::equals_any_type<typename std::decay<T>::type, member::tos,
                                                                 member::global, member::local>;
template<typename T>
using is_indexed_member = util::type_traits::equals_any_type<typename std::decay<T>::type, member::args,
                                                             member::global, member::local, member::resource>;
template<typename T>
using is_indexless_member = util::type_traits::equals_any_type<typename std::decay<T>::type, member::tos>;
template<typename T>
using is_optimizeable_member =
    util::type_traits::equals_any_type<typename std::decay<T>::type, member::global, member::local,
                                       member::resource>;
template<typename T>
using is_not_optimizeable_member =
    util::type_traits::equals_any_type<typename std::decay<T>::type, member::tos, member::args>;

template<bool Optimize, typename T>
inline typename std::enable_if<is_indexed_member<T>::value>::type optimized_member(std::ostream& output,
                                                                                   T member)
{
	optimized_write<Optimize>(output, member.index);
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_indexless_member<T>::value>::type optimized_member(std::ostream&,
                                                                                     T) noexcept
{}

template<bool Optimize, typename T>
inline typename std::enable_if<is_member_source<T>::value && is_not_optimizeable_member<T>::value,
                               member_source_option>::type member_source_index(T) noexcept
{
	return static_cast<member_source_option>(
	    util::type_traits::type_index<typename std::decay<T>::type, member::tos, member::args>::value);
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_member_source<T>::value && is_optimizeable_member<T>::value,
                               member_source_option>::type
    member_source_index(T member) noexcept
{
	constexpr auto index = util::type_traits::type_index<typename std::decay<T>::type, member::global,
	                                                     member::local, member::resource>::value +
	                       mso_global_16;

	return static_cast<member_source_option>(
	    index + (Optimize && util::limit_checker<std::uint8_t>::in_bounds(member.index) ? 3 : 0));
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_member_destination<T>::value && is_not_optimizeable_member<T>::value,
                               member_destination_option>::type member_destination_index(T) noexcept
{
	return mdo_tos;
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_member_destination<T>::value && is_optimizeable_member<T>::value,
                               member_destination_option>::type
    member_destination_index(T member) noexcept
{
	constexpr auto index =
	    util::type_traits::type_index<typename std::decay<T>::type, member::global, member::local>::value +
	    mdo_global_16;

	return static_cast<member_destination_option>(
	    index + (Optimize && util::limit_checker<std::uint8_t>::in_bounds(member.index) ? 2 : 0));
}

template<bool Optimize>
inline resource_option resource_index(member::resource resource) noexcept
{
    if (util::limit_checker<std::uint8_t>::in_bounds(resource.index)) {
        return ro_8;
    }

    return ro_16;
}

} // namespace writer
} // namespace bytecode
} // namespace bia

#endif
