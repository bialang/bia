#include "bvm/bvm.hpp"

#include "bvm/instruction_pointer.hpp"

#include <bytecode/op_code.hpp>
#include <gc/gcable.hpp>
#include <gc/stack.hpp>
#include <gc/token.hpp>
#include <member/member.hpp>
#include <member/native/int_member.hpp>
#include <util/finally.hpp>


using namespace bia::bvm;
using namespace bia::bytecode;

void bvm::execute(context& context, const bia::util::byte* first, const bia::util::byte* last)
{
	instruction_pointer ip{ first, last };
	member::member::test_type test_register{ 10 };
	auto& gc           = context.gc();
	auto token         = gc.register_thread(64);
	auto& stack        = token.stack();
	const auto finally = util::make_finally([&stack] {
		puts("right before exiting:");
		if (const auto ptr = dynamic_cast<member::native::int_member*>(stack.at(0).get())) {
			printf("it is an int: %d\n", ptr->test());
		}
	});
	gc::gcable<member::member> accumulator{ nullptr, nullptr };

	while (ip) {
		const auto op_code = ip.next_op_code();

		switch (op_code) {
		case oc_return_void: return;
		case oc_push: {
			token.set(stack.push(), static_cast<gc::object::base*>(accumulator.peek()));
			accumulator.start_monitor();

			break;
		}
		case oc_jump: {
			const auto offset = ip.read<std::int32_t>();

			ip += offset;

			break;
		}
		case oc_jump_true: {
			const auto offset = ip.read<std::int32_t>();

			if (test_register) {
				ip += offset;
			}

			break;
		}
		case oc_jump_false: {
			const auto offset = ip.read<std::int32_t>();

			if (!test_register) {
				ip += offset;
			}

			break;
		}
		case oc_test: {
			const auto index = ip.read<std::uint32_t>();
			const auto ptr   = static_cast<member::member*>(stack.at(index).get());

			if (!ptr) {
				throw;
			}

			test_register = ptr->test();

			break;
		}
		case oc_instantiate: {
			const auto constant = ip.read<std::int32_t>();

			accumulator = gc.construct<member::native::int_member>(constant).to<member::member>();

			break;
		}
		default: throw;
		}
	}
}
