#include "engine.hpp"

#include "bvm/bvm.hpp"
#include "compiler/compiler.hpp"
#include "config.hpp"
#include "memory/simple_allocator.hpp"
#include "resource/deserialize.hpp"
#include "string/encoding/encoder.hpp"
#include "tokenizer/bia_lexer.hpp"
#include "util/finally.hpp"

#if BIA_DEVELOPER_DISASSEMBLY
#	include "bytecode/disassembler.hpp"

#	include <iostream>
#endif

#include <sstream>

using namespace bia;

Engine::Engine() : _gc{ std::make_shared<memory::Simple_allocator>() }, _context{ _gc }
{}

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
		return;
	}

	const auto ins = instructions.str();
	const auto res = resource_output.str();
	memory::Stack stack{ _gc.allocator(), 1024 };
	memory::Frame<true> frame{ stack._memory, _gc };
	auto resources =
	  resource::deserialize({ reinterpret_cast<const util::Byte*>(res.data()), res.size() }, _gc);

	// _gc.register_stack(stack);

#if BIA_DEVELOPER_DISASSEMBLY
	// print disassembly
	instructions.seekg(0, std::ios::beg);
	bytecode::disassemble(instructions, std::cout);
#endif

	bvm::execute({ reinterpret_cast<const util::Byte*>(ins.data()), ins.size() }, frame, resources, _context);

	// _gc.unregister_stack(stack);
	_gc.run();
}
