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

	template<typename Invokable>
	void function(const std::string& name, Invokable&& invokeable, bool immutable = true)
	{
		_context.global_namespace().put_invokable(name, std::forward<Invokable>(invokeable), immutable);
	}
	template<typename Type>
	void variable(const std::string& name, Type&& value, bool immutable = true)
	{
		_context.global_namespace().put_value(name, std::forward<Type>(value), immutable);
	}
	internal::Context& context() noexcept;
	void run(std::istream& code);

private:
	memory::gc::GC _gc;
	internal::Context _context;
};

} // namespace bia

#endif
