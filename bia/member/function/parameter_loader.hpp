#ifndef BIA_MEMBER_FUNCTION_PARAMETER_LOADER_HPP_
#define BIA_MEMBER_FUNCTION_PARAMETER_LOADER_HPP_

#include <bia/memory/frame.hpp>
#include <bia/util/algorithm.hpp>
#include <bia/util/type_traits/is_frameable.hpp>
#include <bia/util/type_traits/is_varargs_invokable.hpp>
#include <bia/util/type_traits/type_at.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <cstddef>
#include <type_traits>

namespace bia {
namespace member {
namespace function {

template<typename... Parameters>
inline std::size_t aligned_offset(util::type_traits::Type_container<Parameters...> = {})
{
	static_assert(util::sum(static_cast<int>(util::type_traits::Is_frameable<Parameters>::value)...) ==
	                sizeof...(Parameters),
	              "All parameters must be frameable");
	return util::sum(util::aligned(internal::type::Framer<Parameters>::size(), alignof(std::max_align_t))...);
}

template<typename Parameter, typename... PreviousParameters>
inline Parameter load_parameter(memory::Frame<false>& frame,
                                util::type_traits::Type_container<PreviousParameters...>)
{
	return frame.load<Parameter>(aligned_offset<PreviousParameters...>());
	// return frame.load<Parameter>(util::sum(
	//   util::aligned(internal::type::Framer<PreviousParameters>::size(), alignof(std::max_align_t))...));
}

template<std::size_t Index, typename... Parameters>
inline typename std::enable_if<!(util::type_traits::Is_varargs_compatible_container<
                                   util::type_traits::Type_container<Parameters...>>::value &&
                                 Index == sizeof...(Parameters) - 1),
                               typename util::type_traits::type_at<Index, Parameters...>::type>::type
  load_parameter(memory::Frame<false>& frame)
{
	// static_assert(util::sum(static_cast<int>(util::type_traits::Is_frameable<Parameters>::value)...) ==
	//                 sizeof...(Parameters),
	//               "All parameters must be frameable");
	// TODO
	return load_parameter<typename util::type_traits::type_at<Index, Parameters...>::type>(
	  frame, util::type_traits::Type_select<0, Index + 1, memory::gc::GC_able<void*>, Parameters...>::selected);
}

template<std::size_t Index, typename... Parameters>
inline typename std::enable_if<(util::type_traits::Is_varargs_compatible_container<
                                  util::type_traits::Type_container<Parameters...>>::value &&
                                Index == sizeof...(Parameters) - 1),
                               typename util::type_traits::type_at<Index, Parameters...>::type>::type
  load_parameter(memory::Frame<false>& frame)
{
	const std::size_t offset = aligned_offset(
	  util::type_traits::Type_select<0, Index + 1, memory::gc::GC_able<void*>, Parameters...>::selected);
	return { memory::Frame<false>{ frame,
		                             offset + util::aligned(sizeof(std::ptrdiff_t), alignof(std::max_align_t)) },
		       frame.load<std::ptrdiff_t>(offset) };
	// static_assert(util::sum(static_cast<int>(util::type_traits::Is_frameable<Parameters>::value)...) ==
	//                 sizeof...(Parameters),
	//               "All parameters must be frameable");
	// // TODO
	// return load_parameter<typename util::type_traits::type_at<Index, Parameters...>::type>(
	//   frame, util::type_traits::type_select<0, Index + 1, memory::gc::GC_able<void*>, Parameters...>::value);
}

} // namespace function
} // namespace member
} // namespace bia

#endif
