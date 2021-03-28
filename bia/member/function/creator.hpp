#ifndef BIA_MEMBER_FUNCTION_CREATOR_HPP_
#define BIA_MEMBER_FUNCTION_CREATOR_HPP_

#include "base.hpp"
#include "functor.hpp"
#include "static.hpp"

#include <bia/memory/gc/gc.hpp>
#include <bia/util/type_traits/invokable_info.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <type_traits>
#include <utility>

namespace bia {
namespace member {
namespace function {

template<typename Invokeable, typename... Arguments>
inline
  typename std::enable_if<util::type_traits::Invokable_info<typename std::decay<Invokeable>::type>::is_static,
                          memory::gc::GC_able<Base*>>::type
  create(memory::gc::GC& gc, Invokeable&& function, util::type_traits::type_container<Arguments...>)
{
	return {
		gc.create<Static<typename util::type_traits::Invokable_info<typename std::decay<Invokeable>::type>::Return,
		                 Arguments...>>(std::forward<Invokeable>(function))
	};
}

template<typename Invokeable, typename... Arguments>
inline
  typename std::enable_if<util::type_traits::Invokable_info<typename std::decay<Invokeable>::type>::is_functor,
                          memory::gc::GC_able<Base*>>::type
  create(memory::gc::GC& gc, Invokeable&& function, util::type_traits::type_container<Arguments...>)
{
	return { gc.create<Functor<typename std::decay<Invokeable>::type>>(std::forward<Invokeable>(function)) };
}

template<typename Invokeable>
inline memory::gc::GC_able<Base*> create(memory::gc::GC& gc, Invokeable&& function)
{
	static_assert(util::type_traits::Invokable_info<typename std::decay<Invokeable>::type>::is_invokable,
	              "Function must be invokable");
	return create(gc, std::forward<Invokeable>(function),
	              util::type_traits::Invokable_info<typename std::decay<Invokeable>::type>::arguments);
}

} // namespace function
} // namespace member
} // namespace bia

#endif
