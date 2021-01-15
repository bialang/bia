#include "loader.hpp"

#include <bia/error/exception.hpp>

using namespace bia::bvm::module;

loader::loader(util::Not_null<gc::gc*> gc) noexcept
{
	_gc = gc;
}

bia::util::Not_null<bia::util::gcable<bia::member::member*>>
    loader::load(util::Not_null<util::gcable<member::native::string*>> name)
{
	const auto it = _modules.find(name.get());

	if (it != _modules.end()) {
		return it->second->create(*_gc);
	}

	BIA_THROW(error::Code::module_not_found);
}

void loader::add_module(util::Not_null<util::gcable<member::native::string*>> name,
                        util::Not_null<util::gcable<module*>> module)
{
	_modules.emplace(name.get(), module.get());
}

void loader::gc_mark_children(bool mark) const noexcept
{
	for (const auto& i : _modules) {
		gc::object::gc_mark(i.first.get(), mark);
		gc::object::gc_mark(i.second.get(), mark);
	}
}
