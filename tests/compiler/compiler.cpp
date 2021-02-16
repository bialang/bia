//#define CATCH_CONFIG_MAIN

#include <bia/bvm/bvm.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace bia;

// TEST_CASE("simple compiling", "[compiler]")
int main()
try {
	std::stringstream code;
	std::stringstream output;
	std::stringstream resource_output;

	code << u8R"(
		
		let x: int = "hello, world"

)";

	gc::gc g{ std::make_shared<gc::memory::simple_allocator>() };
	compiler::Compiler compiler{ g.allocator(), output, resource_output };
	auto encoder = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto finally = util::finallay([encoder] { string::encoding::free_encoder(encoder); });
	tokenizer::Bia_lexer lexer{ g.allocator() };

	lexer.lex(code, *encoder, compiler);

	// run
	const auto ins = output.str();
	const auto res = resource_output.str();
	gc::Stack stack{ g.allocator(), 1024 };
	const auto resources =
	  resource::deserialize({ reinterpret_cast<const util::Byte*>(res.data()), res.size() });
	bvm::execute({ reinterpret_cast<const util::Byte*>(ins.data()), ins.size() }, stack, resources);

	// print stack
	for (int i = 0; i < 5; ++i) {
		std::cout << "%" << std::setw(3) << i * 4 << ": " << std::setw(16) << stack.load<std::uint32_t>(i * 4)
		          << std::endl;
	}
} catch (const bia::error::Exception& e) {
	std::cerr << "exception from main: " << e.code() << "\n\twhat: " << e.what()
	          << "\n\tfrom: " << e.source_location() << std::endl;
} catch (const bia::error::Contract_violation& e) {
	std::cerr << "contract violation from main\n\twhat: " << e.what() << "\n\tfrom: " << e.source_location()
	          << std::endl;
}
