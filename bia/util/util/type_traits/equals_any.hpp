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

} // namespace type_traits
} // namespace util
} // namespace bia