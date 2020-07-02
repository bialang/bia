#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <bia/exception/syntax_error.hpp>
#include <bia/member/function/generator.hpp>
#include <iostream>
#include <sstream>
#include <typeinfo>

int main()
{
	bia::engine engine{};

	engine.module<bia::bsl::io>("io", engine.gc());
	engine.function("range", [](int start, int end, int step) {
		auto foo = [start, end, step]() mutable -> bia::gc::gcable<bia::member::member> {
			const auto current = start;

			if ((start += step) >= end) {
				return bia::member::function::stop_iteration;
			}

			return bia::creator::create(current);
		};

		return bia::gc::gc::active_gc()
		    ->construct<bia::member::function::generator<
		        bia::member::function::method<false, decltype(&decltype(foo)::operator())>>>(
		        foo, &decltype(foo)::operator());
	});

	std::stringstream code;

	code << u8R"(

import io

for i in range(0, 10, 2) {
	io.print(i)
}

/*
let x = range(0, 10, 1)

io.print("outside the loop", x())

for i in x {
	io.print("inside the loop", i)
}

// should it be still valid?
io.print(i)*/

)";

	try {
		engine.execute(code);
	} catch (const bia::exception::bia_error& e) {
		std::cout << "exception (" << e.name() << "; " << e.filename() << ":" << e.line() << "): " << e.what()
		          << "\n";

		if (dynamic_cast<const bia::exception::syntax_error*>(&e)) {
			const auto details = static_cast<const bia::exception::syntax_error&>(e).details();

			std::cout << details.message << ":" << details.position.operator std::streamoff() << "\n\n"
			          << code.str() << "\n";

			for (auto i = details.position.operator std::streamoff(); i--;) {
				std::cout.put(' ');
			}

			std::cout << "\e[0;32m^\e[0;30m\n";
		}

		return 1;
	}
}
