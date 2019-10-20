#pragma once

#include <cstddef>

namespace bia {
namespace util {
namespace type_traits {

template<std::size_t Index, typename... T>
struct type_at;

template<std::size_t Index, typename T, typename... Ts>
struct type_at<Index, T, Ts...> : type_at<Index - 1, Ts...>
{};

template<typename T, typename... Ts>
struct type_at<0, T, Ts...>
{
	typedef T type;
};

} // namespace type_traits
} // namespace util
} // namespace bia