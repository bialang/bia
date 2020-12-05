#ifndef BIA_CREATOR_CREATOR_HPP_
#define BIA_CREATOR_CREATOR_HPP_

#include <bia/error/exception.hpp>
#include <bia/gc/gc.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/native/floating_point.hpp>
#include <bia/member/native/integer.hpp>
#include <bia/member/native/list.hpp>
#include <bia/member/native/string.hpp>
#include <bia/util/type_traits/is_gcable.hpp>
#include <bia/util/type_traits/is_variant.hpp>
#include <bia/util/variant.hpp>
#include <cstddef>
#include <cstring>
#include <string>
#include <type_traits>

namespace bia {
namespace creator {

inline gc::gcable<member::member> create(gc::gc& gc, bool value)
{
	// TODO implement this
	return {};
}

template<typename Type>
inline typename std::enable_if<std::is_integral<Type>::value && (sizeof(Type) <= 8),
                               gc::gcable<member::native::integer<Type>>>::type
  create(gc::gc& gc, Type value)
{
	return gc.construct<member::native::integer<Type>>(value);
}

template<typename Type>
inline typename std::enable_if<std::is_floating_point<Type>::value && (sizeof(Type) <= 8),
                               gc::gcable<member::native::floating_point<Type>>>::type
  create(gc::gc& gc, Type value)
{
	return gc.construct<member::native::floating_point<Type>>(value);
}

template<typename Return, typename... Args>
inline gc::gcable<member::function::static_<Return, Args...>> create(gc::gc& gc, Return (*function)(Args...))
{
	return gc.construct<member::function::static_<Return, Args...>>(function);
}

template<typename Type, std::size_t Index = 0>
inline typename std::enable_if<Index + 1 == Type::type_count &&
                                 util::type_traits::is_variant<typename std::decay<Type>::type>::value,
                               gc::gcable<member::member>>::type
  create(gc::gc& gc, Type&& value)
{
	if (!Index && value.index() == value.npos) {
		return {};
	} else if (value.index() == Index) {
		return create(gc, value.template get<Index>());
	}

	BIA_THROW(bia::error::code::why_did_this_happen);
}

template<typename Type, std::size_t Index = 0>
inline typename std::enable_if<Index + 1 != Type::type_count &&
                                 util::type_traits::is_variant<typename std::decay<Type>::type>::value,
                               gc::gcable<member::member>>::type
  create(gc::gc& gc, Type&& value)
{
	if (!Index && value.index() == value.npos) {
		return {};
	} else if (value.index() == Index) {
		return create(gc, value.template get<Index>());
	}

	return create<Type, Index + 1>(gc, std::forward<Type>(value));
}

inline gc::gcable<member::native::string> create(gc::gc& gc, const char* value)
{
	const auto length = std::char_traits<char>::length(value);
	const auto str    = static_cast<char*>(gc.allocate(length + 1).release());
	auto mem          = gc.construct<member::native::string>(str);

	std::memcpy(str, value, length + 1);

	return mem;
}

template<typename Type>
inline
  typename std::enable_if<util::type_traits::is_gcable<typename std::decay<Type>::type>::value &&
                            std::is_base_of<member::member, typename util::type_traits::is_gcable<
                                                              typename std::decay<Type>::type>::type>::value,
                          Type>::type
  create(gc::gc& gc, Type&& value)
{
	return std::forward<Type>(value);
}

inline gc::gcable<member::member> create(gc::gc& gc, member::member* value) noexcept
{
	return { value };
}

inline gc::gcable<member::native::string> create(gc::gc& gc, const std::string& value)
{
	return create(gc, value.c_str());
}

inline gc::gcable<member::member> create(gc::gc& gc, std::nullptr_t) noexcept
{
	return {};
}

inline gc::gcable<member::native::list> create(gc::gc& gc, std::vector<member::member*> value)
{
	return gc.construct<member::native::list>(std::move(value));
}

} // namespace creator
} // namespace bia

#endif
