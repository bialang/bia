#include "os.hpp"

#include "helper.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <cstdlib>

using namespace bia::bsl;

inline bia::gc::gcable<bia::member::member> get_env(const char* name)
{
	if (const auto value = getenv(name)) {
		return bia::creator::create(value);
	}

	return {};
}

os::os(gc::gc& gc) : _symbols{ _init(gc) }
{}

os::version_type os::version() const noexcept
{
	return 0;
}

bia::util::not_null<bia::member::member*> os::create(gc::gc& gc)
{
	return _symbols.get();
}

void os::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_symbols.get(), mark);
}

void os::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_symbols.get());

	for (const auto& i : _symbols->map()) {
		gc.register_gcable(i.first.get());
		gc.register_gcable(i.second.get());
	}
}

bia::member::native::dict* os::_init(gc::gc& gc)
{
	const auto dict = gc.construct<member::native::dict>().release();

	put_function(gc, *dict, "get_env", &get_env);
	put_function(gc, *dict, "system", &std::system);

	return dict;
}
