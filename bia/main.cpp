#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <bia/bsl/math.hpp>
#include <bia/exception/syntax_error.hpp>
#include <bia/member/function/generator.hpp>
#include <iostream>
#include <sstream>
#include <typeinfo>

int main()
{
	bia::engine engine;

	engine.module<bia::bsl::io>("io", engine.gc());
	engine.module<bia::bsl::math>("math", engine.gc());

	std::stringstream code;

	code << u8R"(

import io
import math

io.print(math.min(9,8,77))

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
