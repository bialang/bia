#ifndef BIA_MEMBER_INVOKE_CONTEXT_HPP_
#define BIA_MEMBER_INVOKE_CONTEXT_HPP_

#include <bia/bvm/context.hpp>
#include <bia/gc/root.hpp>
#include <bia/gc/token.hpp>

namespace bia {
namespace member {

struct invoke_context
{
	bvm::context& context;
	gc::root& resources;
	gc::token& token;
};

} // namespace member
} // namespace bia

#endif
