#ifndef BIA_MEMBER_CAST_HPP_
#define BIA_MEMBER_CAST_HPP_

#include "member.hpp"

#include <type_traits>
#include <typeinfo>
#include <bia/util/type_traits/conjunction.hpp>

namespace bia {
namespace member {

template<typename T>
using is_const_value =
    std::is_const<typename std::remove_pointer<typename std::remove_reference<T>::type>::type>;

template<typename T>
inline typename std::enable_if<std::is_integral<T>::value, T>::type cast(member& m)
{
	if (!(m.flags() & member::flag_numeric)) {
		throw;
	}

	return static_cast<T>(m.as_int());
}

template<typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, T>::type cast(member& m)
{
	if (!(m.flags() & member::flag_numeric)) {
		throw;
	}

	return static_cast<T>(m.as_float());
}

template<typename T>
inline typename std::enable_if<!std::is_arithmetic<T>::value && !is_const_value<T>::value, T>::type
    cast(member& m)
{
	T output{};

	if (!m.as_data(typeid(T), &output)) {
		throw;
	}

	return output;
}

template<typename T>
inline typename std::enable_if<!std::is_arithmetic<T>::value && is_const_value<T>::value, T>::type
    cast(const member& m)
{
	T output{};

	if (!m.as_data(typeid(T), &output)) {
		throw;
	}

	return output;
}

} // namespace member
} // namespace bia

#endif
