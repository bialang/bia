#define CATCH_CONFIG_MAIN

#include <bvm/bvm.hpp>
#include <bytecode/writer/instruction.hpp>
#include <catch.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <sstream>

using namespace bia::bvm;
using namespace bia::bytecode;

TEST_CASE("simple run", "[bvm]")
{
	context ctx{ std::make_shared<bia::gc::gc>(std::make_shared<bia::gc::memory::simple_allocator>()) };
	std::stringstream output;
	writer::instruction iw{ output };

	iw.write<true, oc_instantiate>(61, member::tos{});
	iw.write<true, oc_instantiate>(11, member::tos{});
	iw.write<true, oc_instantiate>(3, member::tos{});
	iw.write<true, oc_invoke>(2, member::local{ 0 }, member::tos{});
	// iw.write_instruction<false, bytecode::oc_jump_true>(std::int32_t{-6});
	iw.finish();

	const auto code = output.str();

	bia::bvm::bvm::execute(ctx, reinterpret_cast<const bia::util::byte*>(code.data()),
	                       reinterpret_cast<const bia::util::byte*>(code.data() + code.length()));
}
