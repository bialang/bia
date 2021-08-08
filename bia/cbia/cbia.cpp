#include <bia/bvm/bvm.hpp>
#include <bia/cbia.h>
#include <bia/compiler/compiler.hpp>
#include <bia/internal/context.hpp>
#include <bia/memory/frame.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/simple_allocator.hpp>
#include <bia/memory/stack.hpp>
#include <bia/string/encoding/encoder.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/memory_streambuf.hpp>
#include <istream>
#include <sstream>

using namespace bia;

struct Bytecode
{
	std::string instructions;
	std::string resources;
};

bia_context_t bia_context_new()
try {
	return new internal::Context{ *new memory::gc::GC{ std::make_shared<memory::Simple_allocator>() } };
} catch (...) {
	return nullptr;
}

void bia_context_free(bia_context_t context)
try {
	const auto ctx = static_cast<internal::Context*>(context);
	const auto gc  = &ctx->global_namespace().gc();
	delete ctx;
	delete gc;
} catch (...) {
}

bia_err_t bia_compile(bia_context_t context, bia_bytecode_t* out, const char* code, size_t size)
try {
	const auto ctx = static_cast<internal::Context*>(context);
	std::stringstream instructions;
	std::stringstream resources;
	tokenizer::Bia_lexer lexer{ ctx->global_namespace().gc().allocator() };
	compiler::Compiler compiler{ ctx->global_namespace().gc().allocator(), instructions, resources, *ctx };
	util::Memory_streambuf code_buffer{ { reinterpret_cast<const util::Byte*>(code), size } };
	std::istream input{ &code_buffer };
	auto encoder      = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto free_encoder = util::finallay([&] { string::encoding::free_encoder(encoder); });
	tokenizer::Reader reader{ input, *encoder };

	lexer.lex(reader, compiler);

	if (compiler.errors().size()) {
		return BIA_ERR_UNKNOWN;
	}

	*out = new Bytecode{ instructions.str(), resources.str() };

	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}

void bia_bytecode_free(bia_bytecode_t bytecode)
try {
	delete static_cast<Bytecode*>(bytecode);
} catch (...) {
}

bia_err_t bia_run(bia_context_t context, bia_bytecode_t bytecode)
try {
	const auto ctx   = static_cast<internal::Context*>(context);
	const auto bcode = static_cast<Bytecode*>(bytecode);

	memory::Stack stack{ ctx->global_namespace().gc().allocator(), 1024 };
	memory::Frame<true> frame{ stack._memory, ctx->global_namespace().gc(), 0 };
	auto resources = resource::deserialize(
	  { reinterpret_cast<const util::Byte*>(bcode->resources.data()), bcode->resources.size() },
	  ctx->global_namespace().gc());

	// ctx->global_namespace().gc().register_stack(stack);

	bvm::execute(
	  { reinterpret_cast<const util::Byte*>(bcode->instructions.data()), bcode->instructions.size() }, frame,
	  resources, *ctx);

	// ctx->global_namespace().gc().unregister_stack(stack);
	ctx->global_namespace().gc().run();

	return BIA_OK;
} catch (...) {
	return BIA_ERR_UNKNOWN;
}
