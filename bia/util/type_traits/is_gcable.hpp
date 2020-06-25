#ifndef BIA_UTIL_TYPE_TRAITS_IS_GCABLE_HPP_
#define BIA_UTIL_TYPE_TRAITS_IS_GCABLE_HPP_

#include <type_traits>

namespace bia {
namespace gc {

template<typename Type>
class gcable;

}

namespace util {
namespace type_traits {

template<typename Type>
struct is_gcable : std::false_type
{
	typedef Type type;
};

template<typename Type>
struct is_gcable<gc::gcable<Type>> : std::true_type
{
	typedef Type type;
};

} // namespace type_traits
} // namespace util
} // namespace bia

#endif
