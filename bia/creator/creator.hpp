#ifndef BIA_CREATOR_CREATOR_HPP_
#define BIA_CREATOR_CREATOR_HPP_

#include <cstring>
#include <bia/gc/gc.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/native/integer.hpp>
#include <bia/member/native/string.hpp>
#include <string>
#include <type_traits>

namespace bia {
namespace creator {

template<typename T>
inline typename std::enable_if<std::is_integral<typename std::decay<T>::type>::value &&
                                   (sizeof(typename std::decay<T>::type) <= 8),
                               gc::gcable<member::native::integer>>::type
    create(T&& value)
{
	return gc::gc::active_gc()->construct<member::native::integer>(std::forward<T>(value));
}

template<typename T>
inline typename std::enable_if<std::is_floating_point<typename std::decay<T>::type>::value &&
                                   (sizeof(typename std::decay<T>::type) <= 8),
                               gc::gcable<member::native::integer>>::type
    create(T&& value)
{
	return {};
	// return gc::gc::active_gc()->construct<member::native::int_member>(std::forward<T>(value));
}

template<typename Return, typename... Args>
inline gc::gcable<member::function::static_<Return, Args...>> create(Return (*function)(Args...))
{
	return gc::gc::active_gc()->construct<member::function::static_<Return, Args...>>(function);
}

inline gc::gcable<member::native::string> create(const std::string& value)
{
	const auto gc  = gc::gc::active_gc();
	const auto str = static_cast<char*>(gc->allocate(value.size() + 1).release());
	auto mem       = gc->construct<member::native::string>(str);

	std::memcpy(str, value.c_str(), value.size() + 1);

	return mem;
}

} // namespace creator
} // namespace bia

#endif
