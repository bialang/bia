#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include "context.hpp"

#include <bia/gc/gcable.hpp>
#include <bia/gc/root.hpp>
#include <bia/gc/stack_view.hpp>
#include <bia/gc/token.hpp>
#include <bia/member/member.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bvm {

class bvm
{
public:
	static gc::gcable<member::member> execute(context& context, util::span<const util::byte*> instructions,
	                                          gc::root& resources);
	static gc::gcable<member::member> execute(context& context, util::span<const util::byte*> instructions,
	                                          gc::root& resources, gc::stack_view& stack, gc::token& token);
};

} // namespace bvm
} // namespace bia

#endif
