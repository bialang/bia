#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <iostream>
#include <sstream>

int main()
{
	bia::engine engine;

	engine.function("foo", [](bia::connector::parameters_type params) {
		std::cout << "positionals:";

		for (auto i : params.positionals()) {
			std::cout << " " << i;
		}

		std::cout << "\nkwargs:";

		for (auto i : params.kwargs()) {
			std::cout << " " << bia::member::cast::cast<const char*>(*i->key()) << "=" << i->value();
		}

		std::cout << std::endl;
	});
	engine.module<bia::bsl::io>("io", engine.gc());

	std::stringstream code;

	code << u8R"(
		import io

		foo(1, 2, "string", z=0, x=23, "another positional", something=true)

		let l = list(1)
		l.push("hi")
		io.print(l.front(), l.back(), sep="...")

		l.reverse()
		if /hi+/ == l.front() {
			io.print("Hello, there")
		}

		if /fly/ in "iliketofly" {
			io.print("Oh really, me too")
		}
	)";

	engine.execute(code);
}
