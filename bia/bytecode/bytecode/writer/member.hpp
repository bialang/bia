#ifndef BIA_BYTECODE_WRITER_MEMBER_HPP_
#define BIA_BYTECODE_WRITER_MEMBER_HPP_

#include "../op_code.hpp"
#include "common.hpp"

#include <ostream>
#include <type_traits>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/type_index.hpp>

namespace bia {
namespace bytecode {
namespace writer {

template<typename T>
using is_member = util::type_traits::equals_any_type<typename std::decay<T>::type, member::tos, member::args,
                                                     member::global, member::local, member::resource>;
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
inline typename std::enable_if<is_not_optimizeable_member<T>::value, member_option>::type
    member_index(T) noexcept
{
	return static_cast<member_option>(
	    util::type_traits::type_index<typename std::decay<T>::type, member::tos, member::args>::value);
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_optimizeable_member<T>::value, member_option>::type
    member_index(T member) noexcept
{
	constexpr auto index = util::type_traits::type_index<typename std::decay<T>::type, member::global,
	                                                     member::local, member::resource>::value +
	                       mo_global_16;

	return static_cast<member_option>(
	    index + (Optimize && util::limit_checker<std::uint8_t>::in_bounds(member.index) ? 3 : 0));
}

} // namespace writer
} // namespace bytecode
} // namespace bia

#endif