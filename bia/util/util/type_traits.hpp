#pragma once

#include <type_traits>

namespace bia {
namespace util {

template<bool...>
struct conjunction : std::true_type
{};

template<bool B>
struct conjunction<B> : std::conditional<B, std::true_type, std::false_type>::type
{};

template<bool B0, bool... B>
struct conjunction<B0, B...> : std::conditional<B0 && conjunction<B...>::value, std::true_type, std::false_type>::type
{};



}
}