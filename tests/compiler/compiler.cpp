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

inline void print_error(const std::string& code, const compiler::Error& error)
{
	BIA_EXPECTS(error.range.start.line == error.range.end.line && error.range.start < error.range.end);
	std::vector<util::Span<const char*>> lines;
	// split
	{
		std::size_t line_start = 0;
		for (std::size_t i = 0; i < code.length(); ++i) {
			if (code[i] == '\n') {
				lines.push_back({ code.data() + line_start, code.data() + i });
				line_start = i + 1;
			}
		}
		if (line_start < code.length()) {
			lines.push_back({ code.data() + line_start, code.data() + code.length() });
		}
	}
	std::cerr << error.code.default_error_condition().message() << ": " << error.code.message() << '\n';
	auto line = lines.at(error.range.start.line - 1);
	std::cerr.write(line.data(), line.size());
	std::cerr << '\n';
	for (std::size_t i = 0; i < error.range.start.character - 1; ++i) {
		std::cerr << (line.at(i) == '\t' ? '\t' : ' ');
	}
	std::cerr << '^';
	for (std::size_t i = error.range.start.character + 1; i < error.range.end.character; ++i) {
		std::cerr << '~';
	}
	std::cerr << std::endl;
}

// TEST_CASE("simple compiling", "[compiler]")
int main()
try {
	std::stringstream code;
	std::stringstream output;
	std::stringstream resource_output;

	code << u8R"(
  
	let x: int = "hello, world"
	let o = x
	let p: int = 1 == 0

)";

	gc::gc g{ std::make_shared<gc::memory::simple_allocator>() };
	compiler::Compiler compiler{ g.allocator(), output, resource_output };
	auto encoder = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto finally = util::finallay([encoder] { string::encoding::free_encoder(encoder); });
	tokenizer::Bia_lexer lexer{ g.allocator() };
	tokenizer::Reader reader{ code, *encoder };

	lexer.lex(reader, compiler);

	if (compiler.errors().size() > 0) {
		const auto str = code.str();
		for (auto err : compiler.errors()) {
			print_error(str, err);
		}
		std::cerr << "compilation failed\n";
		return -1;
	}

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
	          << "\n\tcondition: " << e.code().default_error_condition().message()
	          << "\n\tfrom: " << e.source_location() << std::endl;
} catch (const bia::error::Contract_violation& e) {
	std::cerr << "contract violation from main\n\twhat: " << e.what() << "\n\tfrom: " << e.source_location()
	          << std::endl;
}
