#ifndef BIA_BYTECODE_WRITER_MEMBER_HPP_
#define BIA_BYTECODE_WRITER_MEMBER_HPP_

#include "../op_code.hpp"
#include "common.hpp"

#include <bia/util/type_traits/equals_any.hpp>
#include <bia/util/type_traits/type_index.hpp>
#include <ostream>
#include <type_traits>

namespace bia {
namespace bytecode {
namespace writer {

template<typename T>
using is_member_source =
    util::type_traits::equals_any_type<typename std::decay<T>::type, member::args, member::global,
                                       member::local, member::resource, member::builtin>;
template<typename T>
using is_member_destination = util::type_traits::equals_any_type<typename std::decay<T>::type, member::args,
                                                                 member::global, member::local>;

template<bool Optimize, typename Type>
inline void optimized_member(std::ostream& output, Type member)
{
	optimized_write<Optimize>(output, member.index);
}

template<bool Optimize>
inline void optimized_member(std::ostream& output, member::builtin builtin) noexcept
{
	optimized_write<false>(output,
	                       static_cast<typename std::underlying_type<member::builtin>::type>(builtin));
}

template<bool Optimize>
inline member_source_option member_source_index(member::builtin) noexcept
{
	return member_source_option::mso_builtin;
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_member_source<T>::value, member_source_option>::type
    member_source_index(T member) noexcept
{
	constexpr auto index =
	    util::type_traits::type_index<typename std::decay<T>::type, member::args, member::global,
	                                  member::local, member::resource>::value;

	return static_cast<member_source_option>(
	    index + (Optimize && util::limit_checker<std::uint8_t>::in_bounds(member.index) ? 4 : 0));
}

template<bool Optimize, typename T>
inline typename std::enable_if<is_member_destination<T>::value, member_destination_option>::type
    member_destination_index(T member) noexcept
{
	constexpr auto index = util::type_traits::type_index<typename std::decay<T>::type, member::args,
	                                                     member::global, member::local>::value;

	return static_cast<member_destination_option>(
	    index + (Optimize && util::limit_checker<std::uint8_t>::in_bounds(member.index) ? 3 : 0));
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
