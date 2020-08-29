#include "sys.hpp"

#include "helper.hpp"

#include <bia/config.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <bia/gc/temporary_token.hpp>
#include <cstdlib>

using namespace bia::bsl;

sys::sys(gc::gc& gc, util::span<const char* const*> arguments) : _symbols{ _init(gc, arguments) }
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

bia::member::native::dict* sys::_init(gc::gc& gc, util::span<const char* const*> arguments)
{
	const auto dict     = gc.construct<member::native::dict>().release();
	const int byteorder = 1;

	put_function(gc, *dict, "exit", &std::exit);
	put_function(gc, *dict, "quick_exit", &std::quick_exit);
	put_function(gc, *dict, "abort", &std::abort);
	put_gcable(gc, *dict, "version", creator::create(gc, BIA_VERSION));
	put_gcable(gc, *dict, "byteorder",
	           creator::create(gc, *reinterpret_cast<const char*>(&byteorder) == 1 ? "little" : "big"));

	member::native::list::list_type args;

	args.reserve(arguments.size());

	for (auto i : arguments) {
		args.push_back(creator::create(gc, i).release());
	}

	put_gcable(gc, *dict, "args", creator::create(gc, std::move(args)));

	return dict;
}
