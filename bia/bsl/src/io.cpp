#include "bsl/io.hpp"

#include <connector/connector-inl.hpp>
#include <member/function/static_.hpp>
#include <member/native/dict.hpp>
#include <member/native/string.hpp>

using namespace bia::bsl;

io::io(gc::gc& gc) : _symbols{ _init(gc) }
{}

io::version_type io::version() const noexcept
{
	return 0;
}

bia::util::not_null<bia::member::member*> io::create(gc::gc& gc)
{
	return _symbols.get();
}

void io::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_symbols.get(), mark);
}

void io::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_symbols.get());

	for (const auto& i : _symbols->map()) {
		gc.register_gcable(i.first.get());
		gc.register_gcable(i.second.get());
	}
}

bia::member::native::dict* io::_init(gc::gc& gc)
{
	const auto dict = gc.construct<member::native::dict>().release();
	const auto str  = static_cast<char*>(gc.allocate(6).release());
	const auto name = gc.construct<member::native::string>(str).release();
	const auto fun  = gc.construct<member::function::static_<void, const char*>>([](const char* str) {
                           puts(str);
                       }).release();

	std::memcpy(str, "print", 6);

	dict->put(name, fun);

	return dict;
}