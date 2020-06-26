#ifndef BIA_CREATOR_CREATOR_HPP_
#define BIA_CREATOR_CREATOR_HPP_

#include <bia/gc/gc.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/native/floating_point.hpp>
#include <bia/member/native/integer.hpp>
#include <bia/member/native/list.hpp>
#include <bia/member/native/string.hpp>
#include <bia/util/type_traits/is_gcable.hpp>
#include <cstddef>
#include <cstring>
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
                               gc::gcable<member::native::floating_point>>::type
    create(T&& value)
{
	return gc::gc::active_gc()->construct<member::native::floating_point>(std::forward<T>(value));
}

template<typename Return, typename... Args>
inline gc::gcable<member::function::static_<Return, Args...>> create(Return (*function)(Args...))
{
	return gc::gc::active_gc()->construct<member::function::static_<Return, Args...>>(function);
}

inline gc::gcable<member::native::string> create(const char* value)
{
	const auto gc     = gc::gc::active_gc();
	const auto length = std::char_traits<char>::length(value);
	const auto str    = static_cast<char*>(gc->allocate(length + 1).release());
	auto mem          = gc->construct<member::native::string>(str);

	std::memcpy(str, value, length + 1);

	return mem;
}

template<typename Type>
inline typename std::enable_if<
    util::type_traits::is_gcable<typename std::decay<Type>::type>::value &&
        std::is_base_of<member::member,
                        typename util::type_traits::is_gcable<typename std::decay<Type>::type>::type>::value,
    Type>::type
    create(Type&& value)
{
	return std::forward<Type>(value);
}

inline gc::gcable<member::member> create(member::member* value) noexcept
{
	return { value };
}

inline gc::gcable<member::native::string> create(const std::string& value)
{
	return create(value.c_str());
}

inline gc::gcable<member::member> create(std::nullptr_t) noexcept
{
	return {};
}

inline gc::gcable<member::native::list> create(std::vector<member::member*> value)
{
	return gc::gc::active_gc()->template construct<member::native::list>(std::move(value));
}

} // namespace creator
} // namespace bia

#endif
