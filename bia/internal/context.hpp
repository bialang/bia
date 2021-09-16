#ifndef BIA_INTERNAL_CONTEXT_HPP_
#define BIA_INTERNAL_CONTEXT_HPP_

#include "namespace.hpp"
#include "string_key.hpp"
#include "type/function.hpp"
#include "type/string.hpp"
#include "type/system.hpp"
#include "type/void.hpp"
#include "typed_object.hpp"

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
	Context(memory::gc::GC& gc)
	    : _type_system_runtime{ gc.allocator() }, _type_system_compilation{ gc.allocator() }, _namespace{
		      _type_system_compilation, gc
	      }
	{}
	Namespace& global_namespace() noexcept
	{
		return _namespace;
	}

private:
	/// The type system required by the runtime. This contains usually types that were passed around as
	/// indeterminates.
	type::System _type_system_runtime;
	/// The type system required for compilation. This is usually more elaborate than the runtime type system.
	type::System _type_system_compilation;
	/// The global namespace. These variables and modules are always available.
	Namespace _namespace;
};

} // namespace internal
} // namespace bia

#endif
