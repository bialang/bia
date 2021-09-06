#ifndef BIA_ENGINE_HPP_
#define BIA_ENGINE_HPP_

#include "internal/context.hpp"
#include "memory/gc/gc.hpp"

#include <istream>
#include <string>
#include <utility>

namespace bia {

class Engine
{
public:
	Engine();

	/**
	 * Sets the globally available symbol to the given function.
	 * 
	 * @tparam Invokable The function type.
	 * @param name The global name.
	 * @param invokable The invokable function.
	 * @param immutable If `true`, the Bia code is not allowed to overwrite the symbol value.
	*/
	template<typename Invokable>
	void function(const std::string& name, Invokable&& invokable, bool immutable = true)
	{
		_context.global_namespace().put_invokable(name, std::forward<Invokable>(invokable), immutable);
	}
	template<typename Type>
	void variable(const std::string& name, Type&& value, bool immutable = true)
	{
		_context.global_namespace().put_value(name, std::forward<Type>(value), immutable);
	}
	/// Returns the internal context.
	internal::Context& context() noexcept;
	/// Compiles and runs the given Bia code.
	void run(std::istream& code);

private:
	memory::gc::GC _gc;
	internal::Context _context;
};

} // namespace bia

#endif
