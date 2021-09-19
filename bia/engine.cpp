#include "engine.hpp"

#include "bvm/bvm.hpp"
#include "compiler/compiler.hpp"
#include "config.hpp"
#include "memory/simple_allocator.hpp"
#include "resource/deserialize.hpp"
#include "string/encoding/encoder.hpp"
#include "tokenizer/bia_lexer.hpp"
#include "util/finally.hpp"

#include <sstream>

using namespace bia;

#if BIA_DEVELOPER_DISASSEMBLY
#	include "bytecode/disassembler.hpp"
#	include "string/encoding/unicode.hpp"

#	include <iostream>

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
	std::cerr << error.code.default_error_condition().message()
	          << " in line "
	             "IN_FILE"
	             ":"
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
#endif

Engine::Engine()
    : Object_builder_base{ this, nullptr }, _gc{ std::make_shared<memory::Simple_allocator>() }, _context{
	      _gc
      }
{
	_typed_object = Pointer{ &_context.global_namespace(), [](internal::Typed_object*) {} };
}

internal::Context& Engine::context() noexcept
{
	return _context;
}

void Engine::run(std::istream& code)
{
	std::stringstream instructions;
	std::stringstream resource_output;
	tokenizer::Bia_lexer lexer{ _gc.allocator() };
	compiler::Compiler compiler{ _gc.allocator(), instructions, resource_output, _context };
	auto encoder      = string::encoding::get_encoder(string::encoding::Standard::utf_8);
	auto free_encoder = util::finallay([&] { string::encoding::free_encoder(encoder); });
	tokenizer::Reader reader{ code, *encoder };

	lexer.lex(reader, compiler);

	if (compiler.errors().size()) {
#if BIA_DEVELOPER && BIA_DEVELOPER_DISASSEMBLY
		std::stringstream ss;
		code.seekg(0, std::ios::beg);
		ss << code.rdbuf();
		auto str = ss.str();
		for (auto err : compiler.errors()) {
			print_error(split_lines(str), err);
		}
#endif
		BIA_LOG(ERROR, "Compiler error");
		return;
	}

	const auto ins = instructions.str();
	const auto res = resource_output.str();
	memory::Stack stack{ _gc.allocator(), 1024 };
	memory::Frame<true> frame{ stack._memory, _gc };
	auto resources =
	  resource::deserialize({ reinterpret_cast<const util::Byte*>(res.data()), res.size() }, _gc);

	// _gc.register_stack(stack);

#if BIA_DEVELOPER && BIA_DEVELOPER_DISASSEMBLY
	// print disassembly
	instructions.seekg(0, std::ios::beg);
	bytecode::disassemble(instructions, std::cout);
#endif

	bvm::execute({ reinterpret_cast<const util::Byte*>(ins.data()), ins.size() }, frame, resources, _context);

	// _gc.unregister_stack(stack);
	_gc.run();
}

void Engine::use_bsl()
{
	make_available("io", bsl::io);
	make_available("sys", bsl::sys);
	make_available("os", bsl::os);
	make_available("math", bsl::math);
}

void Engine::make_available(std::string name, bsl::Module_definition definition)
{
	BIA_EXPECTS(static_cast<bool>(definition));
	auto builder = module(std::move(name));
	definition(*builder._typed_object);
	builder.finish();
}
