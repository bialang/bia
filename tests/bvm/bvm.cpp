#define CATCH_CONFIG_MAIN

#include <bia/bvm/bvm.hpp>
#include <bia/bytecode/instructor.hpp>
#include <bia/gc/memory/simple_allocator.hpp>
#include <catch.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace bia::bvm;
using namespace bia::bytecode;

TEST_CASE("simple run", "[bvm]")
{
	std::stringstream output;
	Instructor instrcutor{ output };

	instrcutor.write<Op_code::load>(0, std::int32_t{ 1 });
	instrcutor.write<Op_code::copy>(4, 0);
	instrcutor.write<Op_code::load>(8, std::int32_t{ 9 });
	instrcutor.write<Op_code::unsigned_integral_operation>(Infix_operation::addition, 4, 8);

	const auto code = output.str();

	bia::gc::Stack stack{ std::make_shared<bia::gc::memory::simple_allocator>(), 1024 };
	execute({ reinterpret_cast<const bia::util::Byte*>(code.data()), code.length() }, stack);
	// print stack
	for (int i = 0; i < 10; ++i) {
		std::cout << "%" << std::setw(3) << i * 4 << ": " << std::setw(16) << stack.load<std::uint32_t>(i * 4)
		          << std::endl;
	}
}
