#include "sys.hpp"

#include "helper.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <bia/gc/temporary_token.hpp>
#include <cstdlib>

using namespace bia::bsl;

sys::sys(gc::gc& gc, int argc, char** argv) : _symbols{ _init(gc, argc, argv) }
{}

sys::version_type sys::version() const noexcept
{
	return 0;
}

bia::util::not_null<bia::member::member*> sys::create(gc::gc& gc)
{
	return _symbols.get();
}

void sys::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_symbols.get(), mark);
}

void sys::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_symbols.get());

	for (const auto& i : _symbols->map()) {
		gc.register_gcable(i.first.get());
		gc.register_gcable(i.second.get());
	}
}

bia::member::native::dict* sys::_init(gc::gc& gc, int argc, char** argv)
{
	const auto dict     = gc.construct<member::native::dict>().release();
	const auto token    = gc.activate_temporarily();
	const int byteorder = 1;

	put_function(gc, *dict, "exit", &std::exit);
	put_function(gc, *dict, "quick_exit", &std::quick_exit);
	put_function(gc, *dict, "abort", &std::abort);
	put_gcable(gc, *dict, "version", creator::create("v4.0-alpha"));
	put_gcable(gc, *dict, "byteorder",
	           creator::create(*reinterpret_cast<const char*>(&byteorder) == 1 ? "little" : "big"));

	std::vector<member::member*> args;

	for (auto i = 0; i < argc; ++i) {
		args.push_back(creator::create(argv[i]).release());
	}

	put_gcable(gc, *dict, "args", creator::create(std::move(args)));

	return dict;
}
