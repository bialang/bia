#include <atomic>
#include <bia/bia.hpp>
#include <bia/error/contract_violation.hpp>
#include <bia/error/exception.hpp>
#include <bia/member/function/generator.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <typeinfo>

int main(int argc, char** argv)
try {
	bia::engine engine;
	engine.use_bsl({ argv, argv + argc });

	std::atomic_bool b;
	auto t = std::thread{ [&] {
		while (!b) {
			std::this_thread::sleep_for(std::chrono::seconds{ 1 });
			engine.gc().run_once();
		}

		BIA_LOG(INFO, "exiting gc thread");
	} };
	auto f = bia::util::finallay([&] {
		BIA_LOG(INFO, "waiting for gc to finish");
		b = true;
		t.join();
	});

	std::stringstream code;
	code << u8R"(
	
let x: int = 0
// import io
// import sys

// fun a(x: any): int {
// 	io.print("ha", x, asd or "hey")
// 	return 61
// }

// return a("hi")
)";

	try {
		if (const auto ptr = engine.execute(code).peek()) {
			const auto value = bia::member::cast::cast<int>(*ptr);
			std::cout << "result: " << value << std::endl;
		}
	} catch (const bia::error::Exception& e) {
		std::cerr << "exception (" << e.code() << ") from " << e.source_location() << ": " << e.what()
		          << '\n';
		// std::cout << "exception (" << e.name() << "; " << e.filename() << ":" << e.line() << "): " <<
		// e.what()
		//           << "\n";

		// if (dynamic_cast<const bia::exception::syntax_error*>(&e)) {
		// 	const auto details = static_cast<const bia::exception::syntax_error&>(e).details();

		// 	std::cout << details.message << ":" << details.position.operator std::streamoff() << "\n\n"
		// 	          << code.str() << "\n";

		// 	for (auto i = details.position.operator std::streamoff(); i--;) {
		// 		std::cout.put(' ');
		// 	}

		// 	std::cout << "\e[0;32m^\e[0;30m\n";
		// }

		return 1;
	}
} catch (const bia::error::Contract_violation& e) {
	std::cerr << "contract violated (" << e.source_location() << "): " << e.what() << '\n';
	return -1;
}
