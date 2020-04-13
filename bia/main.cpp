#include <bvm/bvm.hpp>
#include <compiler/compiler.hpp>
#include <exception/syntax_error.hpp>
#include <gc/gc.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <iostream>
#include <sstream>
#include <tokenizer/bia_lexer.hpp>
#include <util/finally.hpp>

int main()
{
	auto allocator = std::make_shared<bia::gc::memory::simple_allocator>();
	bia::tokenizer::bia_lexer lexer{ allocator };
	std::stringstream output;
	std::stringstream code;
	bia::compiler::compiler compiler{ output };
	auto encoder = bia::string::encoding::encoder::get_instance(
	    bia::string::encoding::encoder::standard_encoding::utf_8);
	const auto finally =
	    bia::util::make_finally([encoder] { bia::string::encoding::encoder::free_instance(encoder); });

	code << u8R"(
		
let print = 65

print(99, 5)

)";

	try {
		lexer.lex(code, *encoder, compiler);
	} catch (const bia::exception::bia_error& e) {
		std::cout << "exception (" << e.name() << "; " << e.filename() << ":" << e.line() << "): " << e.what()
		          << "\n";

		if (dynamic_cast<const bia::exception::syntax_error*>(&e)) {
			auto details = static_cast<const bia::exception::syntax_error&>(e).details();

			std::cout << details.message << ":" << details.position.operator std::streamoff() << "\n\n";

			std::cout << code.str() << "\n";

			for (auto i = details.position.operator std::streamoff(); i--;) {
				std::cout.put(' ');
			}
			std::cout << "\e[0;32m^\e[0;30m\n";
		}

		return 1;
	}

	compiler.finish();

	auto gc = std::make_shared<bia::gc::gc>(allocator);
	bia::bvm::context context{ gc };
	const auto bytecode = output.str();

	bia::bvm::bvm::execute(context, reinterpret_cast<const bia::util::byte*>(&bytecode[0]),
	                       reinterpret_cast<const bia::util::byte*>(&bytecode[0] + bytecode.size()));
}