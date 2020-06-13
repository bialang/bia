#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <bia/exception/syntax_error.hpp>
#include <bia/member/function/generator.hpp>
#include <iostream>
#include <sstream>
#include <typeinfo>

int main()
{
	bia::engine engine;

	engine.module<bia::bsl::io>("io", engine.gc());

	std::stringstream code;

	code << u8R"(

import io

let x = "ich bin 21 jahre alt und wir schreiben den 18.07.2020"

for i in /\d+/.match_all(x) {
	io.print(i.group(0))
}

/*
import io

io.print("hi", "bye")
io.print("hey")

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
