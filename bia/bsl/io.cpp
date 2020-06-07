#include "io.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/native/dict.hpp>
#include <bia/member/native/string.hpp>
#include <iostream>

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
	const auto fun  = gc.construct<member::function::static_<void, connector::parameters>>(
                           [](connector::parameters params) {
                               for (std::size_t i = 0; i < params.size(); ++i) {
                                   if (const auto ptr = params[i]) {
                                       if (dynamic_cast<const bia::member::native::string*>(ptr)) {
                                           std::cout << bia::member::cast::cast<const char*>(*ptr) << " ";
                                       } else {
                                           std::cout << bia::member::cast::cast<int>(*ptr) << " ";
                                       }
                                   } else {
                                       std::cout << "<null> ";
                                   }
                               }

                               std::cout << "\n";
                           })
	                     .release();

	std::memcpy(str, "print", 6);

	dict->put(name, fun);

	return dict;
}
