//#define CATCH_CONFIG_MAIN

#include <bia/bsl/modules.hpp>
#include <bia/bvm/bvm.hpp>
#include <bia/bytecode/disassembler.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/error/contract_violation.hpp>
#include <bia/member/function/context.hpp>
#include <bia/member/function/varargs.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/simple_allocator.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/string/encoding/unicode.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <catch2/catch.hpp>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

extern char** environ;

using namespace bia;

#define IN_FILE "../../tests/compiler/test.bia"

inline std::vector<util::Span<const char*>> split_lines(const std::string& code)
{
	std::vector<util::Span<const char*>> lines;
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
	return lines;
}

inline void print_error(const std::vector<util::Span<const char*>>& lines, const error::Bia& error)
{
	BIA_EXPECTS(error.range.start.line == error.range.end.line && error.range.start <= error.range.end);
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
	std::cout << std::boolalpha;
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
	context.global_namespace().put_invokable(util::from_cstring("to_string"),
	                                         [](std::ptrdiff_t value) { return std::to_string(value); });
	context.global_namespace().put_invokable(util::from_cstring("fto_string"),
	                                         [](double value) { return std::to_string(value); });
	context.global_namespace().put_invokable(
	  util::from_cstring("compare"), [](const std::string& a, const std::string& b) { return a.compare(b); });

	context.global_namespace().put_invokable(
	  util::from_cstring("test"), +[](bool value) { std::cout << (value ? "true" : "false") << "\n"; });
	context.global_namespace().put_value(util::from_cstring("file"), std::string{ __FILE__ }, false);
	context.global_namespace().put_invokable(util::from_cstring("varargs"),
	                                         [](std::int64_t, member::function::Varargs<std::string> strings) {
		                                         printf("got %zu arguments: ", strings.size());
		                                         for (std::size_t i = 0; i < strings.size(); ++i) {
			                                         printf("%s ", strings.at(i).c_str());
		                                         }
		                                         puts("");
	                                         });
	context.global_namespace().put_invokable(util::from_cstring("variant"),
	                                         [](util::Variant<std::int64_t, std::string> arg) {
		                                         if (arg.is_type<std::int64_t>()) {
			                                         std::cout << "<int> " << arg.get<std::int64_t>() << "\n";
		                                         } else {
			                                         std::cout << "<str> " << arg.get<std::string>() << "\n";
		                                         }
	                                         });

	internal::Typed_object obj{ context.global_namespace().type_system(), gc };
	for (char** s = environ; *s; ++s) {
		char* p = std::strchr(*s, '=');
		if (p) {
			obj.put_value(std::string{ *s, p - *s }, std::string{ p + 1 });
		}
	}
	context.global_namespace().put_object(util::from_cstring("env"), std::move(obj));

	member::function::Signature signature{ context.global_namespace().type_system().definition_of<int>() };
	signature.positionals.push_back({ context.global_namespace().type_system().definition_of<std::string>() });
	signature.positionals.push_back({ context.global_namespace().type_system().definition_of<std::string>() });
	signature.named_arguments.insert({ util::from_cstring("a"), 0 });
	signature.named_arguments.insert({ util::from_cstring("b"), 1 });
	context.global_namespace().put_invokable(
	  util::from_cstring("dynamic"),
	  [](member::function::Context& context) {
		  std::cout << "A=" << context.get_argument<std::string>(0)
		            << " B=" << context.get_argument<std::string>(1) << "\n";
		  context.set_return(61);
	  },
	  signature);

	{
		internal::Typed_object io{ context.global_namespace().type_system(), gc };
		bsl::io(io);
		context.global_namespace().put_import(util::from_cstring("io"), std::move(io));
	}

	{
		internal::Typed_object sys{ context.global_namespace().type_system(), gc };
		bsl::sys(sys);
		context.global_namespace().put_import(util::from_cstring("sys"), std::move(sys));
	}

	{
		internal::Typed_object os{ context.global_namespace().type_system(), gc };
		bsl::os(os);
		context.global_namespace().put_import(util::from_cstring("os"), std::move(os));
	}

	compiler::Compiler compiler{ allocator, output, resource_output, context };
	auto encoder = string::encoding::get_encoder(string::encoding::Standard::utf_8);
	auto finally = util::finallay([encoder] { string::encoding::free_encoder(encoder); });
	tokenizer::Bia_lexer lexer{ allocator };
	tokenizer::Reader reader{ code, *encoder };

	bool failed = false;

#if BIA_LOG_IS(INFO)
	const auto start = std::chrono::high_resolution_clock::now();
#endif

	if (const auto err = lexer.lex(reader, compiler)) {
		code.clear();
		code.seekg(0, std::ios::end);
		std::string str;
		str.resize(code.tellg());
		code.seekg(0, std::ios::beg);
		code.read(&str[0], str.size());
		print_error(split_lines(str), err);
		BIA_LOG(ERROR, "Lexing failed");
	}

	compiler.finish();
	BIA_LOG(INFO, "Compilation took {}", std::chrono::high_resolution_clock::now() - start);

	if (compiler.errors().size() > 0) {
		code.clear();
		code.seekg(0, std::ios::end);
		std::string str;
		str.resize(code.tellg());
		code.seekg(0, std::ios::beg);
		code.read(&str[0], str.size());
		const auto lines = split_lines(str);
		for (auto err : compiler.errors()) {
			print_error(lines, err);
		}
		BIA_LOG(ERROR, "Compilation failed with {} error{}", compiler.errors().size(),
		        compiler.errors().size() > 1 ? "s" : "");
		failed = true;
	}

	if (compiler.warnings().size() > 0) {
		code.clear();
		code.seekg(0, std::ios::end);
		std::string str;
		str.resize(code.tellg());
		code.seekg(0, std::ios::beg);
		code.read(&str[0], str.size());
		const auto lines = split_lines(str);
		for (auto warn : compiler.warnings()) {
			print_error(lines, warn);
		}
		BIA_LOG(WARN, "Compilation finished with {} warning{}", compiler.warnings().size(),
		        compiler.warnings().size() > 1 ? "s" : "");
	}

	if (failed) {
		return -1;
	}

	// run
	const auto ins = output.str();
	const auto res = resource_output.str();

	output.seekg(std::ios::beg);
	bytecode::disassemble(output, std::cout);

	memory::Stack stack{ allocator, 1024 };
	memory::Frame<true> base_frame{ stack._memory, &gc };
	const auto resources =
	  resource::deserialize({ reinterpret_cast<const util::Byte*>(res.data()), res.size() }, gc);
	gc.register_stack(stack);
	{
#if BIA_LOG_IS(INFO)
		const auto start = std::chrono::high_resolution_clock::now();
#endif
		bvm::execute({ reinterpret_cast<const util::Byte*>(ins.data()), ins.size() }, base_frame, resources,
		             context);
		BIA_LOG(INFO, "Execution took {}", std::chrono::high_resolution_clock::now() - start);
	}
	gc.run();

	// print stack
	std::cout << "\n==========STACK==========\n";
	for (int i = 0; i < 5; ++i) {
		std::cout << "%" << std::setw(4) << std::setfill(' ') << std::hex << i * 2 * sizeof(std::size_t) << ": 0x"
		          << std::setw(16) << std::setfill('0') << std::hex
		          << base_frame.load<std::size_t>(i * 2 * sizeof(std::size_t)) << "\n";
	}
	std::cout << "==========STACK==========\n";
} catch (const bia::error::Exception& e) {
	std::cerr << "Exception from main: " << e.code() << "\n\twhat: " << e.what()
	          << "\n\tcondition: " << e.code().default_error_condition().message()
	          << "\n\tfrom: " << e.source_location() << std::endl;
} /* catch (const bia::error::Contract_violation& e) {
  std::cerr << "Contract violation from main\n\twhat: " << e.what() << "\n\tfrom: " << e.source_location()
            << std::endl;
}
 */
