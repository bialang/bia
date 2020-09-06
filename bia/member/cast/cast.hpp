#ifndef BIA_MEMBER_CAST_CAST_HPP_
#define BIA_MEMBER_CAST_CAST_HPP_

#include "../member.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/type_traits/conjunction.hpp>
#include <type_traits>
#include <typeinfo>

namespace bia {
namespace member {
namespace cast {

template<typename Type>
using is_const_value =
    std::is_const<typename std::remove_pointer<typename std::remove_reference<Type>::type>::type>;

template<typename Type>
inline typename std::enable_if<std::is_integral<Type>::value, Type>::type cast(member& m)
{
	if (!(m.flags() & member::flag_numeric)) {
		BIA_THROW(error::code::bad_cast);
	}

	return static_cast<Type>(m.as_int());
}

template<typename Type>
inline typename std::enable_if<std::is_floating_point<Type>::value, Type>::type cast(member& m)
{
	if (!(m.flags() & member::flag_numeric)) {
		BIA_THROW(error::code::bad_cast);
	}

	return static_cast<Type>(m.as_float());
}

template<typename Type>
inline typename std::enable_if<!std::is_arithmetic<Type>::value && !is_const_value<Type>::value, Type>::type
    cast(member& m)
{
	Type output{};

	if (!m.as_data(typeid(Type), &output)) {
		BIA_THROW(error::code::bad_cast);
	}

	return output;
}

template<typename Type>
inline typename std::enable_if<!std::is_arithmetic<Type>::value && is_const_value<Type>::value, Type>::type
    cast(const member& m)
{
	Type output{};

	if (!m.as_data(typeid(Type), &output)) {
		BIA_THROW(error::code::bad_cast);
	}

	return output;
}

} // namespace cast
} // namespace member
} // namespace bia

#endif
