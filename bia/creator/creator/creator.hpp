#ifndef BIA_CREATOR_CREATOR_HPP_
#define BIA_CREATOR_CREATOR_HPP_

#include <gc/gc.hpp>
#include <member/native/int_member.hpp>
#include <type_traits>

namespace bia {
namespace creator {

template<typename T>
inline typename std::enable_if<std::is_integral<typename std::decay<T>::type>::value &&
                                   (sizeof(typename std::decay<T>::type) <= 8),
                               gc::gcable<member::native::int_member>>::type
    create(T&& value)
{
	return gc::gc::active_gc()->construct<member::native::int_member>(std::forward<T>(value));
}

template<typename T>
inline typename std::enable_if<std::is_floating_point<typename std::decay<T>::type>::value &&
                                   (sizeof(typename std::decay<T>::type) <= 8),
                               gc::gcable<member::native::int_member>>::type
    create(T&& value)
{
	return {};
	//return gc::gc::active_gc()->construct<member::native::int_member>(std::forward<T>(value));
}

} // namespace creator
} // namespace bia

#endif