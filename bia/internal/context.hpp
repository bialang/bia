#ifndef BIA_INTERNAL_CONTEXT_HPP_
#define BIA_INTERNAL_CONTEXT_HPP_

#include "namespace.hpp"
#include "type/function.hpp"
#include "type/string.hpp"
#include "type/system.hpp"
#include "type/void.hpp"

#include <bia/error/exception.hpp>
#include <bia/member/function/static.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/optional.hpp>
#include <map>
#include <string>

namespace bia {
namespace internal {

class Context
{
public:
	Context(memory::gc::GC& gc) : _type_system{ gc.allocator() }, _namespace{ _type_system, gc }
	{}
	Namespace& global_namespace() noexcept
	{
		return _namespace;
	}

private:
	type::System _type_system;
	/// The global namespace. These variables and modules are always available.
	Namespace _namespace;
};

} // namespace internal
} // namespace bia

#endif
