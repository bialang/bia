#pragma once

#include <type_traits>

namespace bia {
namespace util {
namespace type_traits {

template<typename T, T Value, T... Other>
struct equals_any : std::false_type
{};

template<typename T, T Value, T Other>
struct equals_any<T, Value, Other>
	: std::conditional<Value == Other, std::true_type, std::false_type>::type
{};

template<typename T, T Value, T Other, T... Others>
struct equals_any<T, Value, Other, Others...>
	: std::conditional<Value == Other, std::true_type, equals_any<T, Value, Others...>>::type
{};

template<typename T, typename... Other>
struct equals_any_type : std::false_type
{};

template<typename T, typename Other>
struct equals_any_type<T, Other>
	: std::conditional<std::is_same<T, Other>::value, std::true_type, std::false_type>::type
{};

template<typename T, typename Other, typename... Others>
struct equals_any_type<T, Other, Others...>
	: std::conditional<std::is_same<T, Other>::value, std::true_type, equals_any_type<T, Others...>>::type
{};

} // namespace type_traits
} // namespace util
} // namespace bia