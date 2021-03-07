//#define CATCH_CONFIG_MAIN

#include <bia/bvm/bvm.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/simple_allocator.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/string/encoding/unicode.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace bia;

#define IN_FILE "../../tests/compiler/test.bia"

inline void print_error(const std::string& code, const compiler::Error& error)
{
	BIA_EXPECTS(error.range.start.line == error.range.end.line && error.range.start <= error.range.end);
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
	std::cerr << error.code.default_error_condition().message() << " in line " IN_FILE ":"
	          << error.range.start.line << ":" << error.range.start.character << " => " << error.code.message()
	          << '\n';
	auto line = lines.at(error.range.start.line - 1);
	std::cerr.write(line.data(), line.size());
	std::cerr << '\n';
	for (std::size_t i = 0; i < error.range.start.character - 1; ++i) {
		const auto category = string::encoding::category_of(line.at(i));
		std::cerr << (category == string::encoding::Category::Zs || category == string::encoding::Category::Cc
		                ? line[i]
		                : ' ');
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
	// std::stringstream code;
	std::fstream code{ IN_FILE, std::ios::binary | std::ios::in };
	std::stringstream output;
	std::stringstream resource_output;

	auto allocator = std::make_shared<memory::Simple_allocator>();
	memory::gc::GC gc{ allocator };
	internal::Context context{ gc };
	compiler::Compiler compiler{ allocator, output, resource_output, context };
	auto encoder = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto finally = util::finallay([encoder] { string::encoding::free_encoder(encoder); });
	tokenizer::Bia_lexer lexer{ allocator };
	tokenizer::Reader reader{ code, *encoder };

	lexer.lex(reader, compiler);

	if (compiler.errors().size() > 0) {
		code.seekg(0, std::ios::end);
		std::string str;
		str.resize(code.tellg());
		code.seekg(0, std::ios::beg);
		code.read(&str[0], str.size());
		for (auto err : compiler.errors()) {
			print_error(str, err);
		}
		BIA_LOG(ERROR, "compilation failed");
		return -1;
	}

	// run
	const auto ins = output.str();
	const auto res = resource_output.str();
	memory::Stack stack{ allocator, 1024 };
	memory::Frame base_frame{ stack, gc, 0 };
	const auto resources =
	  resource::deserialize({ reinterpret_cast<const util::Byte*>(res.data()), res.size() }, gc);
	gc.register_stack(stack);
	{
		const auto start = std::chrono::high_resolution_clock::now();
		bvm::execute({ reinterpret_cast<const util::Byte*>(ins.data()), ins.size() }, base_frame, resources,
		             context);
		BIA_LOG(INFO, "execution took {}", std::chrono::high_resolution_clock::now() - start);
	}
	gc.run();

	// print stack
	std::cout << "\n==========STACK==========\n";
	for (int i = 0; i < 5; ++i) {
		std::cout << "%" << std::setw(3) << std::setfill(' ') << std::dec << i * sizeof(std::size_t) << ": 0x"
		          << std::setw(16) << std::setfill('0') << std::hex
		          << base_frame.load<std::size_t>(i * sizeof(std::size_t)) << std::endl;
	}
	std::cout << "==========STACK==========\n";
} catch (const bia::error::Exception& e) {
	std::cerr << "exception from main: " << e.code() << "\n\twhat: " << e.what()
	          << "\n\tcondition: " << e.code().default_error_condition().message()
	          << "\n\tfrom: " << e.source_location() << std::endl;
} catch (const bia::error::Contract_violation& e) {
	std::cerr << "contract violation from main\n\twhat: " << e.what() << "\n\tfrom: " << e.source_location()
	          << std::endl;
}
