#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <iostream>
#include <sstream>

int main()
{
	bia::engine engine;

	engine.function("hello_world", +[] { std::cout << "Hello, World! - C++\n"; });
	engine.module<bia::bsl::io>("io", engine.gc());

	std::stringstream code;

	code << u8R"(
		import io

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
