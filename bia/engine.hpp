#ifndef BIA_ENGINE_HPP_
#define BIA_ENGINE_HPP_

#include "internal/context.hpp"
#include "member/function/varargs.hpp"
#include "memory/gc/gc.hpp"
#include "object_builder.hpp"
#include "primitives.hpp"

#include <bia/bsl/modules.hpp>
#include <istream>
#include <memory>
#include <string>
#include <utility>

namespace bia {

/// Provides a simple interface to the Bia programming language.
class Engine : public Object_builder_base
{
public:
	Engine();

	/// Returns the internal context.
	internal::Context& context() noexcept;
	/// Compiles and runs the given Bia code.
	void run(std::istream& code);
	void use_bsl();
	void make_available(std::string name, bsl::Module_definition definition);
	using Object_builder_base::module;

private:
	memory::gc::GC _gc;
	internal::Context _context;
};

template<typename Type>
using Varargs = member::function::Varargs<Type>;

} // namespace bia

#endif
