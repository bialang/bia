#ifndef BIA_BVM_CONTEXT_HPP_
#define BIA_BVM_CONTEXT_HPP_

#include <bia/error/exception.hpp>
#include <bia/member/function/static.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <map>
#include <string>

namespace bia {
namespace bvm {

class Context
{
public:
	Context(memory::gc::GC& gc)
	{
		_global_modules["hello_world"] = {
			gc.create<member::function::Static<void>>([] { puts("hello world!"); }).pointer
		};
	}
	memory::gc::GC_able<memory::gc::Base*> import(const char* name)
	{
		auto it = _global_modules.find(name);
		if (it == _global_modules.end()) {
			BIA_THROW(error::Code::module_not_found);
		}
		return it->second;
	}

private:
	std::map<std::string, memory::gc::GC_able<memory::gc::Base*>> _global_modules;
};

} // namespace bvm
} // namespace bia

#endif
