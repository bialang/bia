#ifndef BIA_INTERNAL_CONTEXT_HPP_
#define BIA_INTERNAL_CONTEXT_HPP_

#include "type/function.hpp"
#include "type/integer.hpp"
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
	struct Module
	{
		memory::gc::GC_able<memory::gc::Base*> pointer;
		const type::Definition* definition;
	};

	Context(memory::gc::GC& gc)
	{
		static type::Void v;
		static type::Integer i{ type::Integer::Size::i32, true };
		static type::Function foo{ &i, { { &i }, { &i } } };
		_global_modules["hello_world"] = { gc.create<member::function::Static<int, int, int>>([](int i, int j) {
			                                     printf("hello world - %d | %d!\n", i, j);
			                                     return i * j;
			                                   })
			                                   .pointer,
			                                 &foo };
	}
	template<typename Return, typename... Arguments>
	void put_function(const std::string& name, Return (*function)(Arguments...))
	{
		// TODO add type
		// _global_modules[name] = { gc.create<member::function::Static<Return, Arguments...>>(function).pointer
		// };
	}
	Module import(const char* name)
	{
		auto it = _global_modules.find(name);
		if (it == _global_modules.end()) {
			BIA_THROW(error::Code::module_not_found);
		}
		return it->second;
	}
	util::Optional<Module> import(const resource::View&)
	{
		return import("hello_world");
	}

private:
	// type::System _type_system;
	std::map<std::string, Module> _global_modules;
};

} // namespace internal
} // namespace bia

#endif
