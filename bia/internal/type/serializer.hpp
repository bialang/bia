#ifndef BIA_INTERNAL_TYPE_SERIALIZER_HPP_
#define BIA_INTERNAL_TYPE_SERIALIZER_HPP_

#include <bia/util/gsl.hpp>
#include <type_traits>

namespace bia {
namespace internal {
namespace type {

template<typename Type, typename = void>
struct Serializer;

template<typename Type>
struct Serializer<Type, typename std::enable_if<std::is_integral<Type>::value>::type>
{
};

template<typename Type>
struct Serializer<Type*, void>
{
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
