#include "io.hpp"

#include "helper.hpp"

#include <bia/connector/connector-inl.hpp>
#include <iostream>
#include <string>

using namespace bia::bsl;

inline void print(bia::connector::parameters_type params)
{
	const char* sep = " ";
	const char* end = "\n";

	{
		auto tmp = params["sep"];

		if (tmp.second) {
			sep = bia::member::cast::cast<const char*>(*tmp.first);
		}

		tmp = params["end"];

		if (tmp.second) {
			end = bia::member::cast::cast<const char*>(*tmp.first);
		}
	}

	for (auto i = params.positionals().begin(); i != params.positionals().end(); ++i) {
		if (*i) {
			if (dynamic_cast<const bia::member::native::string*>(*i)) {
				std::cout << bia::member::cast::cast<const char*>(**i);
			} else if (dynamic_cast<const bia::member::native::floating_point*>(*i)) {
				std::cout << bia::member::cast::cast<bia::member::member::float_type>(**i);
			} else {
				std::cout << bia::member::cast::cast<bia::member::member::int_type>(**i);
			}
		} else {
			std::cout << "<null>";
		}

		if (i + 1 != params.positionals().end()) {
			std::cout << sep;
		}
	}

	std::cout << end;
}

inline std::string read_input(bia::connector::parameters_type params)
{
	std::string input;

	std::getline(std::cin, input);

	return input;
}

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

	put_function(gc, *dict, "print", &print);
	put_function(gc, *dict, "read", &read_input);

	return dict;
}
