#include <bia/bia.hpp>
#include <bia/exception/syntax_error.hpp>
#include <iostream>
#include <sstream>

int main()
{
	bia::engine engine{};

	engine.function("print",
	                static_cast<void (*)(bia::connector::parameters)>([](bia::connector::parameters params) {
						for(std::size_t i = 0; i < params.size(); ++i) {
							std::cout << bia::member::cast<int>(*params[i]) << " ";
						}

						std::cout << "\n";
	                }));

	std::stringstream code;

	code << u8R"(
		
		print(12, 12 ,3, 65)

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
