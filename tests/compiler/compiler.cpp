//#define CATCH_CONFIG_MAIN

#include <bia/bvm/bvm.hpp>
#include <bia/bytecode/disassembler.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/member/function/dynamic.hpp>
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

struct Vector : bia::memory::gc::Base
{
	std::vector<std::string> value;

	Vector(std::vector<std::string>&& value) noexcept : value{ std::move(value) }
	{}
};

namespace bia {
namespace internal {
namespace type {

template<typename Type>
struct Framer<Type, typename std::enable_if<
                      std::is_same<typename std::decay<Type>::type, std::vector<std::string>>::value>::type>
{
	constexpr static std::size_t size() noexcept
	{
		return sizeof(memory::gc::GC_able<Vector*>);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return alignof(memory::gc::GC_able<Vector*>);
	}
	static void frame(memory::gc::GC& gc, util::Span<util::Byte*> buffer, std::vector<std::string> value)
	{
		*reinterpret_cast<memory::gc::GC_able<Vector*>*>(buffer.data()) = gc.create<Vector>(std::move(value));
	}
	static const std::vector<std::string>& unframe(util::Span<const util::Byte*> buffer)
	{
		return (*reinterpret_cast<const memory::gc::GC_able<Vector*>*>(buffer.data()))->value;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

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

	// define user defined types
	context.global_namespace().put_invokable(util::from_cstring("hello_world"),
	                                         static_cast<void (*)()>([] { puts("Hello, world!"); }));
	context.global_namespace().put_invokable(util::from_cstring("print"),
	                                         [](const std::string& v) { return puts(v.c_str()); });
	context.global_namespace().put_invokable(
	  util::from_cstring("compare"), [](const std::string& a, const std::string& b) { return a.compare(b); });
	context.global_namespace().put_invokable(
	  util::from_cstring("print_vector"), +[](const std::vector<std::string>& ss) {
		  for (const auto& s : ss) {
			  std::cout << s << " ";
		  }
		  std::cout << "\n";
	  });
	context.global_namespace().put_invokable(
	  util::from_cstring("read_three"), +[] {
		  std::string s;
		  std::vector<std::string> ss;
		  for (int i = 0; i < 3; ++i) {
			  std::getline(std::cin, s);
			  ss.push_back(s);
		  }
		  return ss;
	  });
	context.global_namespace().put_value(util::from_cstring("file"), std::string{ __FILE__ }, false);
	context.global_namespace().put_invokable(util::from_cstring("to_string"),
	                                         [](std::int64_t i) { return std::to_string(i); });

	compiler::Compiler compiler{ allocator, output, resource_output, context };
	auto encoder = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto finally = util::finallay([encoder] { string::encoding::free_encoder(encoder); });
	tokenizer::Bia_lexer lexer{ allocator };
	tokenizer::Reader reader{ code, *encoder };

	lexer.lex(reader, compiler);

	if (compiler.errors().size() > 0) {
		code.clear();
		code.seekg(0, std::ios::end);
		std::string str;
		str.resize(code.tellg());
		code.seekg(0, std::ios::beg);
		code.read(&str[0], str.size());
		for (auto err : compiler.errors()) {
			print_error(str, err);
		}
		BIA_LOG(ERROR, "Compilation failed with {} errors", compiler.errors().size());
		return -1;
	}

	// run
	const auto ins = output.str();
	const auto res = resource_output.str();

	output.seekg(std::ios::beg);
	bytecode::disassemble(output, std::cout);

	memory::Stack stack{ allocator, 1024 };
	memory::Frame<true> base_frame{ stack._memory, gc, 0 };
	const auto resources =
	  resource::deserialize({ reinterpret_cast<const util::Byte*>(res.data()), res.size() }, gc);
	gc.register_stack(stack);
	{
		const auto start = std::chrono::high_resolution_clock::now();
		bvm::execute({ reinterpret_cast<const util::Byte*>(ins.data()), ins.size() }, base_frame, resources,
		             context);
		BIA_LOG(INFO, "Execution took {}", std::chrono::high_resolution_clock::now() - start);
	}
	gc.run();

	// print stack
	std::cout << "\n==========STACK==========\n";
	for (int i = 0; i < 5; ++i) {
		std::cout << "%" << std::setw(3) << std::setfill(' ') << std::hex << i * 2 * sizeof(std::size_t) << ": 0x"
		          << std::setw(16) << std::setfill('0') << std::hex
		          << base_frame.load<std::size_t>(i * 2 * sizeof(std::size_t)) << std::endl;
	}
	std::cout << "==========STACK==========\n";
} catch (const bia::error::Exception& e) {
	std::cerr << "Exception from main: " << e.code() << "\n\twhat: " << e.what()
	          << "\n\tcondition: " << e.code().default_error_condition().message()
	          << "\n\tfrom: " << e.source_location() << std::endl;
} catch (const bia::error::Contract_violation& e) {
  std::cerr << "Contract violation from main\n\twhat: " << e.what() << "\n\tfrom: " << e.source_location()
            << std::endl;
}
